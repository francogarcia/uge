/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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
  */

//========================================================================
// BaseScriptComponent.cpp - Component for exposing actors to Lua
//
// Part of the GameCode4 Application
//
// GameCode4 is the sample application that encapsulates much of the source code
// discussed in "Game Coding Complete - 4th Edition" by Mike McShaffry and David
// "Rez" Graham, published by Charles River Media.
// ISBN-10: 1133776574 | ISBN-13: 978-1133776574
//
// If this source code has found it's way to you, and you think it has helped you
// in any way, do the authors a favor and buy a new copy of the book - there are
// detailed explanations in it that compliment this code well. Buy a copy at Amazon.com
// by clicking here:
//    http://www.amazon.com/gp/product/1133776574/ref=olp_product_details?ie=UTF8&me=&seller=
//
// There's a companion web site at http://www.mcshaffry.com/GameCode/
//
// The source code is managed and maintained through Google Code:
//    http://code.google.com/p/gamecode4/
//
// (c) Copyright 2012 Michael L. McShaffry and David Graham
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser GPL v3
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
// http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
//
// You should have received a copy of the GNU Lesser GPL v3
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//========================================================================

#include "GameEngineStd.h"

#include "BaseLuaScriptComponent.h"

#include <Utilities/Debug/Logger.h>
#include <Core/Script/Lua/LuaStateManager.h>
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
        const char* BaseLuaScriptComponent::g_ComponentName = "BaseScriptComponent";

        BaseLuaScriptComponent::BaseLuaScriptComponent()
        {
            m_scriptObject.AssignNil(LuaStateManager::Get()->GetLuaState());
            m_scriptDestructor.AssignNil(LuaStateManager::Get()->GetLuaState());
        }

        BaseLuaScriptComponent::~BaseLuaScriptComponent()
        {
            // call the script destructor if there is one
            if (m_scriptDestructor.IsFunction())
            {
                LuaPlus::LuaFunction<void> func(m_scriptDestructor);
                func(m_scriptObject);
            }

            // clear out the script object
            m_scriptObject.AssignNil(LuaStateManager::Get()->GetLuaState());

            // if we were given a path for this script object, set it to nil
            if (!m_scriptObjectName.empty())
            {
                m_scriptObjectName += " = nil;";
                LuaStateManager::Get()->vExecuteString(m_scriptObjectName.c_str());
            }
        }

        bool BaseLuaScriptComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            LuaStateManager* pStateManager = LuaStateManager::Get();
            LOG_ASSERT(pStateManager && "LuaStateManager could not be created!");

            // load the <ScriptObject> tag and validate it
            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("ScriptObject");
            if (!xmlElement.IsGood())
            {
                LOG_ERROR("No <ScriptObject> tag in XML.  This won't be a very useful script component.");

                return true;  // technically it succeeded even though it won't be accessible
            }

            // read all the attributes
            std::string attributeValue;
            if (xmlElement.GetAttribute("var", &attributeValue))
            {
                m_scriptObjectName = attributeValue;
            }

            if (xmlElement.GetAttribute("constructor", &attributeValue))
            {
                m_constructorName = attributeValue;
            }

            if (xmlElement.GetAttribute("destructor", &attributeValue))
            {
                m_destructorName = attributeValue;
            }

            // Having a var attribute will export the instance of this object to that name.
            if (!m_scriptObjectName.empty())
            {
                m_scriptObject = pStateManager->CreatePath(m_scriptObjectName.c_str());

                if (!m_scriptObject.IsNil())
                {
                    CreateScriptObject();
                }
            }

            // The scriptConstructor attribute will also cause a Lua object to be created if one wasn't created in
            // the previous step.  The scriptConstructor string is treated as a function of the form f(scriptObject)
            // and is called.
            if (!m_constructorName.empty())
            {
                m_scriptConstructor = pStateManager->GetGlobalVars().Lookup(m_constructorName.c_str());
                if (m_scriptConstructor.IsFunction())
                {
                    // m_scriptObject could be nil if there was no scriptObject attribute.  If this is the case,
                    // the Lua object is created here.
                    if (m_scriptObject.IsNil())
                    {
                        m_scriptObject.AssignNewTable(pStateManager->GetLuaState());
                        CreateScriptObject();
                    }
                }
            }

            // The scriptDestructor attribute is treated as a function in the form of f(scriptObject) and is called
            // when the C++ ScriptObject instance is destroyed.
            if (!m_destructorName.empty())
            {
                m_scriptDestructor = pStateManager->GetGlobalVars().Lookup(m_destructorName.c_str());
            }

            // read the <ScriptData> tag
            xmlElement = pInitXMLData->GetFirstChildElement("ScriptData");
            if (xmlElement.IsGood())
            {
                if (m_scriptObject.IsNil())
                {
                    LOG_ERROR("m_scriptObject cannot be nil when ScriptData has been defined");

                    return false;
                }

                for (XMLAttribute xmlAttribute = xmlElement.GetFirstAttribute(); xmlAttribute.IsGood(); xmlAttribute = xmlAttribute.GetNextAttribute())
                {
                    m_scriptObject.SetString(xmlAttribute.GetName().c_str(), xmlAttribute.GetValue().c_str());
                }
            }

            return true;
        }

        void BaseLuaScriptComponent::vPostInit()
        {
            // call the script constructor if one exists
            if (m_scriptConstructor.IsFunction())
            {
                LuaPlus::LuaFunction<bool> func(m_scriptConstructor);
                func(m_scriptObject);
            }
        }

        void BaseLuaScriptComponent::CreateScriptObject()
        {
            LuaStateManager* pStateMgr = LuaStateManager::Get();
            LOG_ASSERT(pStateMgr);
            LOG_ASSERT(!m_scriptObject.IsNil());

            LuaPlus::LuaObject metaTableObj = pStateMgr->GetGlobalVars().Lookup(METATABLE_NAME);
            LOG_ASSERT(!metaTableObj.IsNil());

            LuaPlus::LuaObject boxedPtr = pStateMgr->GetLuaState()->BoxPointer(this);
            boxedPtr.SetMetaTable(metaTableObj);
            m_scriptObject.SetLightUserData("__object", this);
            m_scriptObject.SetMetaTable(metaTableObj);
        }

        void BaseLuaScriptComponent::RegisterScriptFunctions()
        {
            // create the metatable
            LuaPlus::LuaObject metaTableObj = LuaStateManager::Get()->GetGlobalVars().CreateTable(METATABLE_NAME);
            metaTableObj.SetObject("__index", metaTableObj);

            // transform component functions
            //metaTableObj.RegisterObjectDirect("GetActorId",		        (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::GetActorID);
            //metaTableObj.RegisterObjectDirect("GetPos",				    (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::GetPos);
            //metaTableObj.RegisterObjectDirect("SetPos",				    (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::SetPos);
            //metaTableObj.RegisterObjectDirect("GetLookAt",	            (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::GetLookAt);
            //metaTableObj.RegisterObjectDirect("GetYOrientationRadians", (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::GetYOrientationRadians);
            //metaTableObj.RegisterObjectDirect("RotateY",	            (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::RotateY);
            //metaTableObj.RegisterObjectDirect("Stop",	                (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::Stop);

            //metaTableObj.RegisterObjectDirect("SetPosition",	        (BaseLuaScriptComponent*)0, &BaseLuaScriptComponent::SetPosition);
        }

        void BaseLuaScriptComponent::UnregisterScriptFunctions()
        {
            LuaPlus::LuaObject metaTableObj = LuaStateManager::Get()->GetGlobalVars().Lookup(METATABLE_NAME);
            if (!metaTableObj.IsNil())
            {
                metaTableObj.AssignNil(LuaStateManager::Get()->GetLuaState());
            }
        }

        // FIXME if needed
        //LuaPlus::LuaObject BaseLuaScriptComponent::GetActorID()
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

        //LuaPlus::LuaObject BaseLuaScriptComponent::GetPos()
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
        //void BaseLuaScriptComponent::SetPos(LuaPlus::LuaObject newPos)
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
        //LuaPlus::LuaObject BaseLuaScriptComponent::GetLookAt() const
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
        //float BaseLuaScriptComponent::GetYOrientationRadians() const
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
        //void BaseLuaScriptComponent::RotateY(float angleRadians)
        //{
        //    shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(m_pOwner->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
        //    if (pPhysicalComponent)
        //        pPhysicalComponent->RotateY(angleRadians);
        //}
        //
        //
        //void BaseLuaScriptComponent::SetPosition(float x, float y, float z)
        //{
        //    shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(m_pOwner->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
        //    if (pPhysicalComponent)
        //        pPhysicalComponent->SetPosition(x, y, z);
        //}
        //
        //void BaseLuaScriptComponent::Stop()
        //{
        //    shared_ptr<PhysicsComponent> pPhysicalComponent = MakeStrongPtr(m_pOwner->GetComponent<PhysicsComponent>(PhysicsComponent::g_Name));
        //    if (pPhysicalComponent)
        //        pPhysicalComponent->Stop();
        //}

        const std::string BaseLuaScriptComponent::vGetName() const
        {
            return g_ComponentName;
        }

    }

}
