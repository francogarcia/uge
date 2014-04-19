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

#include "ScriptTask.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    const char* SCRIPT_TASK_NAME = "ScriptTask";

    ScriptTask::ScriptTask() : m_Frequency(0U), m_Time(0U)
    {
        LuaPlus::LuaState* pLuaState = LuaStateManager::Get()->GetLuaState();

        m_ScriptInitFunction.AssignNil(pLuaState);
        m_ScriptUpdateFunction.AssignNil(pLuaState);
        m_ScriptSuccessFunction.AssignNil(pLuaState);
        m_ScriptFailFunction.AssignNil(pLuaState);
        m_ScriptAbortFunction.AssignNil(pLuaState);

        pLuaState = nullptr;
    }

    bool ScriptTask::BuildCppDataFromScript(LuaPlus::LuaObject scriptClass, LuaPlus::LuaObject constructionData)
    {
        if (scriptClass.IsTable())
        {
            // OnInit()
            LuaPlus::LuaObject luaObject = scriptClass.GetByName("OnInit");
            if (luaObject.IsFunction())
            {
                m_ScriptInitFunction = luaObject;
            }

            // OnUpdate() is required to exist, as it's a pure virtual function.
            luaObject = scriptClass.GetByName("OnUpdate");
            if (luaObject.IsFunction())
            {
                m_ScriptUpdateFunction = luaObject;
            }
            else
            {
                LOG_ERROR("No OnUpdate() found in script process; type == " + std::string(luaObject.TypeName()));

                return false;
            }

            // OnSuccess()
            luaObject = scriptClass.GetByName("OnSuccess");
            if (luaObject.IsFunction())
            {
                m_ScriptSuccessFunction = luaObject;
            }

            // OnFail()
            luaObject = scriptClass.GetByName("OnFail");
            if (luaObject.IsFunction())
            {
                m_ScriptFailFunction = luaObject;
            }

            // OnAbort()
            luaObject = scriptClass.GetByName("OnAbort");
            if (luaObject.IsFunction())
            {
                m_ScriptAbortFunction = luaObject;
            }
        }
        else
        {
            LOG_ERROR("scriptClass is not a table in ScriptTask::BuildCppDataFromScript()");

            return false;
        }

        if (constructionData.IsTable())
        {
            for (LuaPlus::LuaTableIterator constructionDataIt(constructionData); constructionDataIt; constructionDataIt.Next())
            {
                const char* pDataKey = constructionDataIt.GetKey().GetString();
                LuaPlus::LuaObject dataValue = constructionDataIt.GetValue();

                if ((!strcmp(pDataKey, "frequency")) && (dataValue.IsInteger()))
                {
                    m_Frequency = dataValue.GetInteger();
                }
                else
                {
                    m_Self.SetObject(pDataKey, dataValue);
                }
            }
        }

        return true;
    }

    void ScriptTask::vOnInit()
    {
        Task::vOnInit();
        if (!m_ScriptInitFunction.IsNil())
        {
            LuaPlus::LuaFunction<void> func(m_ScriptInitFunction);
            func(m_Self);
        }

        // No update function so bail immediately.  We may want to consider calling Succeed() here so that the child
        // process is attached normally, but right now I'm assuming that the reason no OnUpdate() function was found
        // is due to a bug on the script side.  That means the child process may be dependent on this one.
        if (!m_ScriptUpdateFunction.IsFunction())
        {
            LOG_WARNING("No update function found");

            Fail();
        }
    }

    void ScriptTask::vOnUpdate(const unsigned long deltaMs)
    {
        m_Time += deltaMs;
        if (m_Time >= m_Frequency)
        {
            LuaPlus::LuaFunction<void> func(m_ScriptUpdateFunction);
            func(m_Self, m_Time);
            m_Time = 0;
        }
    }

    void ScriptTask::vOnSuccess()
    {
        if (!m_ScriptSuccessFunction.IsNil())
        {
            LuaPlus::LuaFunction<void> func(m_ScriptSuccessFunction);
            func(m_Self);
        }
    }

    void ScriptTask::vOnFail()
    {
        if (!m_ScriptFailFunction.IsNil())
        {
            LuaPlus::LuaFunction<void> func(m_ScriptFailFunction);
            func(m_Self);
        }
    }

    void ScriptTask::vOnAbort()
    {
        if (!m_ScriptAbortFunction.IsNil())
        {
            LuaPlus::LuaFunction<void> func(m_ScriptAbortFunction);
            func(m_Self);
        }
    }

    bool ScriptTask::ScriptIsAlive()
    {
        return IsAlive();
    }

    bool ScriptTask::ScriptIsDead()
    {
        return IsDead();
    }

    bool ScriptTask::ScriptIsPaused()
    {
        return IsPaused();
    }

    void ScriptTask::ScriptAttachChild(LuaPlus::LuaObject child)
    {
        if (child.IsTable())
        {
            LuaPlus::LuaObject obj = child.GetByName("__object");
            if (!obj.IsNil())
            {
                // Casting a raw ptr to a smart ptr is generally bad, but Lua has no concept of what a std::shared_ptr
                // is.  There's no easy way around it.
                std::shared_ptr<Task> pTask(static_cast<Task*>(obj.GetLightUserData()));
                assert(pTask);
                AttachChild(pTask);
            }
            else
            {
                LOG_ERROR("Attempting to attach child to ScriptTask with no valid __object");
            }
        }
        else
        {
            LOG_ERROR("Invalid object type passed into ScriptTask::ScriptAttachChild(); type = " + std::string(child.TypeName()));
        }
    }

    void ScriptTask::RegisterScriptClass()
    {
        LuaPlus::LuaObject metaTableObj = LuaStateManager::Get()->GetGlobalVars().CreateTable(SCRIPT_TASK_NAME);
        metaTableObj.SetObject("__index", metaTableObj);
        metaTableObj.SetObject("base", metaTableObj);  // base refers to the parent class; ie the metatable
        metaTableObj.SetBoolean("cpp", true);

        RegisterScriptClassFunctions(metaTableObj);
        metaTableObj.RegisterDirect("Create", &ScriptTask::CreateFromScript);
    }

    LuaPlus::LuaObject ScriptTask::CreateFromScript(LuaPlus::LuaObject self, LuaPlus::LuaObject constructionData, LuaPlus::LuaObject originalSubClass)
    {
        // Note: The self parameter is not use in this function, but it allows us to be consistent when calling
        // Create().  The Lua version of this function needs self.
        LOG_MSG("Script", std::string("Creating instance of ") + SCRIPT_TASK_NAME);
        ScriptTask* pObject = LIB_NEW ScriptTask;

        pObject->m_Self.AssignNewTable(LuaStateManager::Get()->GetLuaState());
        if (pObject->BuildCppDataFromScript(originalSubClass, constructionData))
        {
            LuaPlus::LuaObject metaTableObj = LuaStateManager::Get()->GetGlobalVars().Lookup(SCRIPT_TASK_NAME);
            assert(!metaTableObj.IsNil());

            pObject->m_Self.SetLightUserData("__object", pObject);
            pObject->m_Self.SetMetaTable(metaTableObj);
        }
        else
        {
            pObject->m_Self.AssignNil(LuaStateManager::Get()->GetLuaState());
            SAFE_DELETE(pObject);
        }

        return pObject->m_Self;
    }

    void ScriptTask::RegisterScriptClassFunctions(LuaPlus::LuaObject& metaTableObj)
    {
        metaTableObj.RegisterObjectDirect("Succeed", (Task*)0, &Task::Succeed);
        metaTableObj.RegisterObjectDirect("Fail", (Task*)0, &Task::Fail);
        metaTableObj.RegisterObjectDirect("Pause", (Task*)0, &Task::Pause);
        metaTableObj.RegisterObjectDirect("UnPause", (Task*)0, &Task::UnPause);
        metaTableObj.RegisterObjectDirect("IsAlive", (ScriptTask*)0, &ScriptTask::ScriptIsAlive);
        metaTableObj.RegisterObjectDirect("IsDead", (ScriptTask*)0, &ScriptTask::ScriptIsDead);
        metaTableObj.RegisterObjectDirect("IsPaused", (ScriptTask*)0, &ScriptTask::ScriptIsPaused);
        metaTableObj.RegisterObjectDirect("AttachChild", (ScriptTask*)0, &ScriptTask::ScriptAttachChild);
    }

}
