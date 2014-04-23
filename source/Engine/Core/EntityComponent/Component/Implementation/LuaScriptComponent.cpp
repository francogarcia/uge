/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE.
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "LuaScriptComponent.h"

#include <Core/Script/Lua/LuaStateManager.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>
#include <Utilities/Util.h>

// component interfaces
//#include "TransformComponent.h"
//#include "PhysicsComponent.h"
//#include "RenderComponentInterface.h"

namespace uge
{

    namespace Component
    {

        // This is the name of the metatable where all the function definitions exported to Lua will live.
        static const char* METATABLE_NAME = "BaseScriptComponentMetaTable";
        const char* LuaScriptComponent::g_ComponentName = "LuaScriptComponent";

        LuaScriptComponent::LuaScriptComponent()
        {
            m_ScriptObject.AssignNil(lua::LuaStateManager::Get()->GetLuaState());
            m_ScriptDestructor.AssignNil(lua::LuaStateManager::Get()->GetLuaState());
        }

        LuaScriptComponent::~LuaScriptComponent()
        {
            // call the script destructor if there is one
            if (m_ScriptDestructor.IsFunction())
            {
                LuaPlus::LuaFunction<void> func(m_ScriptDestructor);
                func(m_ScriptObject);
            }

            // clear out the script object
            m_ScriptObject.AssignNil(lua::LuaStateManager::Get()->GetLuaState());

            // if we were given a path for this script object, set it to nil
            if (!m_ScriptObjectName.empty())
            {
                m_ScriptObjectName += " = nil;";
                lua::LuaStateManager::Get()->vExecuteString(m_ScriptObjectName.c_str());
            }
        }

        bool LuaScriptComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            lua::LuaStateManager* pStateManager = lua::LuaStateManager::Get();
            LOG_ASSERT(pStateManager && "LuaStateManager have not been created!");

            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("ScriptResource");
            if (!xmlElement.IsGood())
            {
                LOG_WARNING("No resource for the script component!");
            }
            else
            {
                xmlElement.GetAttribute("resource", &m_ScriptResourceFileName);
                pStateManager->vExecuteFile(m_ScriptResourceFileName.c_str());
            }

            xmlElement = pInitXMLData->GetFirstChildElement("ScriptObject");
            if (!xmlElement.IsGood())
            {
                LOG_ERROR("No <ScriptObject> tag in XML");

                return false;
            }

            std::string attributeValue;
            if (xmlElement.GetAttribute("var", &attributeValue))
            {
                m_ScriptObjectName = attributeValue;
            }

            if (xmlElement.GetAttribute("constructor", &attributeValue))
            {
                m_ConstructorName = attributeValue;
            }

            if (xmlElement.GetAttribute("destructor", &attributeValue))
            {
                m_DestructorName = attributeValue;
            }

            // Having a var attribute will export the instance of this object to that name.
            if (!m_ScriptObjectName.empty())
            {
                m_ScriptObject = pStateManager->CreatePath(m_ScriptObjectName.c_str());

                if (!m_ScriptObject.IsNil())
                {
                    CreateScriptObject();
                }
            }

            // The 'constructor' attribute will also cause a Lua object to be created if one wasn't created in
            // the previous step.  The 'constructor' string is treated as a function of the form f(scriptObject)
            // and is called.
            if (!m_ConstructorName.empty())
            {
                m_ScriptConstructor = pStateManager->GetGlobalVars().Lookup(m_ConstructorName.c_str());
                if (m_ScriptConstructor.IsFunction())
                {
                    // m_ScriptObject could be nil if there was no scriptObject attribute.  If this is the case,
                    // the Lua object is created here.
                    if (m_ScriptObject.IsNil())
                    {
                        m_ScriptObject.AssignNewTable(pStateManager->GetLuaState());
                        CreateScriptObject();
                    }
                }
            }

            // The 'destructor' attribute is treated as a function in the form of f(scriptObject) and is called
            // when the C++ ScriptObject instance is destroyed.
            if (!m_DestructorName.empty())
            {
                m_ScriptDestructor = pStateManager->GetGlobalVars().Lookup(m_DestructorName.c_str());
            }

            // read the <ScriptData> tag
            xmlElement = pInitXMLData->GetFirstChildElement("ScriptData");
            if (xmlElement.IsGood())
            {
                if (m_ScriptObject.IsNil())
                {
                    LOG_ERROR("m_ScriptObject cannot be nil when ScriptData has been defined");

                    return false;
                }

                for (XMLElement xmlDataElement = xmlElement.GetFirstChildElement("Attribute");
                     xmlDataElement.IsGood(); xmlDataElement = xmlDataElement.GetNextSiblingElement())
                {
                    std::string type;
                    xmlDataElement.GetAttribute("type", &type);

                    std::string name;
                    xmlDataElement.GetAttribute("name", &name);

                    if (type == "string")
                    {
                        std::string value;
                        xmlDataElement.GetAttribute("value", &value);

                        m_ScriptObject.SetString(name.c_str(), value.c_str());
                    }
                    else if (type == "number")
                    {
                        double value;
                        xmlDataElement.GetDoubleAttribute("value", &value);

                        m_ScriptObject.SetNumber(name.c_str(), value);
                    }
                    else if (type == "boolean")
                    {
                        bool bValue;
                        xmlDataElement.GetBoolAttribute("value", &bValue);

                        m_ScriptObject.SetBoolean(name.c_str(), bValue);
                    }
                }
            }

            return true;
        }

        void LuaScriptComponent::vPostInit()
        {
            // call the script constructor if one exists
            if (m_ScriptConstructor.IsFunction())
            {
                LuaPlus::LuaFunction<bool> func(m_ScriptConstructor);
                func(m_ScriptObject);
            }
        }

        void LuaScriptComponent::vUpdate(const unsigned long dt)
        {

        }

        void LuaScriptComponent::vOnChange()
        {

        }

        void LuaScriptComponent::CreateScriptObject()
        {
            lua::LuaStateManager* pStateMgr = lua::LuaStateManager::Get();
            LOG_ASSERT(pStateMgr);
            LOG_ASSERT(!m_ScriptObject.IsNil());

            LuaPlus::LuaObject metaTableObj = pStateMgr->GetGlobalVars().Lookup(METATABLE_NAME);
            LOG_ASSERT(!metaTableObj.IsNil());

            LuaPlus::LuaObject boxedPtr = pStateMgr->GetLuaState()->BoxPointer(this);
            boxedPtr.SetMetaTable(metaTableObj);
            m_ScriptObject.SetLightUserData("__object", this);
            m_ScriptObject.SetMetaTable(metaTableObj);
        }

        void LuaScriptComponent::RegisterScriptFunctions()
        {
            // create the metatable
            LuaPlus::LuaObject metaTableObj = lua::LuaStateManager::Get()->GetGlobalVars().CreateTable(METATABLE_NAME);
            metaTableObj.SetObject("__index", metaTableObj);

            // transform component functions
            //metaTableObj.RegisterObjectDirect("GetActorId",		        (LuaScriptComponent*)0, &LuaScriptComponent::GetActorID);
            //metaTableObj.RegisterObjectDirect("GetPos",				    (LuaScriptComponent*)0, &LuaScriptComponent::GetPos);
            //metaTableObj.RegisterObjectDirect("SetPos",				    (LuaScriptComponent*)0, &LuaScriptComponent::SetPos);
            //metaTableObj.RegisterObjectDirect("GetLookAt",	            (LuaScriptComponent*)0, &LuaScriptComponent::GetLookAt);
            //metaTableObj.RegisterObjectDirect("GetYOrientationRadians", (LuaScriptComponent*)0, &LuaScriptComponent::GetYOrientationRadians);
            //metaTableObj.RegisterObjectDirect("RotateY",	            (LuaScriptComponent*)0, &LuaScriptComponent::RotateY);
            //metaTableObj.RegisterObjectDirect("Stop",	                (LuaScriptComponent*)0, &LuaScriptComponent::Stop);

            //metaTableObj.RegisterObjectDirect("SetPosition",	        (LuaScriptComponent*)0, &LuaScriptComponent::SetPosition);
        }

        void LuaScriptComponent::UnregisterScriptFunctions()
        {
            LuaPlus::LuaObject metaTableObj = lua::LuaStateManager::Get()->GetGlobalVars().Lookup(METATABLE_NAME);
            if (!metaTableObj.IsNil())
            {
                metaTableObj.AssignNil(lua::LuaStateManager::Get()->GetLuaState());
            }
        }

        // FIXME if needed
        //LuaPlus::LuaObject LuaScriptComponent::GetActorID()
        //{
        //    //GCC_LOG("ObjectSystem", "BaseScriptComponent::GetEntityId() return 0x" + ToStr(m_pOwner->GetId(), 16) + " on C++ side");
        //
        //    // [rez] Wtf??  Returning an unsigned int here will produce really odd results in Release mode (debug is
        //    // fine).  The number will sometimes get truncated, so 0xb1437643 might become 0xb1437600.  Even though the
        //    // C++ side is getting the right number, it gets mangled on the way out to Lua.  The somewhat hacky fix here
        //    // is to return a LuaPlus::LuaObject, which seems to work just fine.  I'm not sure if this will cause any
        //    // efficiency issues, but I'm guessing the LuaPlus internals do something like this anyway to marshal the
        //    // data back to Lua land, so it's probably okay.
        //    LuaPlus::LuaObject ret;
        //    ret.AssignInteger(LuaStateManager::Get()->GetLuaState(), m_pActorOwner->GetId());
        //    return ret;
        //
        //    //return m_pOwner->GetId();
        //}

        //LuaPlus::LuaObject LuaScriptComponent::GetPos()
        //{
        //    LuaPlus::LuaObject ret;
        //
        //    shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::g_Name));
        //    if (pTransformComponent)
        //        LuaStateManager::Get()->ConvertVec3ToTable(pTransformComponent->GetPosition(), ret);
        //    else
        //        ret.AssignNil(LuaStateManager::Get()->GetLuaState());
        //
        //    return ret;
        //}
        //
        //void LuaScriptComponent::SetPos(LuaPlus::LuaObject newPos)
        //{
        //    shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::g_Name));
        //    if (pTransformComponent)
        //    {
        //        Vec3 pos;
        //        LuaStateManager::Get()->ConvertTableToVec3(newPos, pos);
        //        pTransformComponent->SetPosition(pos);
        //    }
        //    else
        //    {
        //        GCC_ERROR("Attempting to call SetPos() on an actor with no physcial component; ActorId: " + ToStr(m_pOwner->GetId()));
        //    }
        //}
        //
        //
        //LuaPlus::LuaObject LuaScriptComponent::GetLookAt() const
        //{
        //    LuaPlus::LuaObject ret;
        //
        //    shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::g_Name));
        //    if (pTransformComponent)
        //        LuaStateManager::Get()->ConvertVec3ToTable(pTransformComponent->GetLookAt(), ret);
        //    else
        //        ret.AssignNil(LuaStateManager::Get()->GetLuaState());
        //
        //    return ret;
        //}
        //
        //float LuaScriptComponent::GetYOrientationRadians() const
        //{
        //    shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::g_Name));
        //    if (pTransformComponent)
        //    {
        //        return (GetYRotationFromVector(pTransformComponent->GetLookAt()));
        //    }
        //    else
        //    {
        //        GCC_ERROR("Attempting to call GetYOrientationRadians() on actor with no physical component");
        //        return 0;
        //    }
        //}
        //
        //void LuaScriptComponent::RotateY(float angleRadians)
        //{
        //    shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(m_pOwner->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
        //    if (pPhysicalComponent)
        //        pPhysicalComponent->RotateY(angleRadians);
        //}
        //
        //
        //void LuaScriptComponent::SetPosition(float x, float y, float z)
        //{
        //    shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(m_pOwner->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
        //    if (pPhysicalComponent)
        //        pPhysicalComponent->SetPosition(x, y, z);
        //}
        //
        //void LuaScriptComponent::Stop()
        //{
        //    shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(m_pOwner->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
        //    if (pPhysicalComponent)
        //        pPhysicalComponent->Stop();
        //}

        const std::string LuaScriptComponent::vGetName() const
        {
            return g_ComponentName;
        }

    }

}
