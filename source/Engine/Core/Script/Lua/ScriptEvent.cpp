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
#include "ScriptEvent.h"
#include "LuaStateManager.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    namespace lua
    {

        ScriptEvent::CreationFunctions ScriptEvent::s_CreationFunctions;

        ScriptEvent::ScriptEvent() : m_bEventDataIsValid(false)
        {

        }

        ScriptEvent::~ScriptEvent()
        {

        }

        LuaPlus::LuaObject ScriptEvent::GetEventData()
        {
            if (!m_bEventDataIsValid)
            {
                vBuildEventData();
                m_bEventDataIsValid = true;
            }

            return m_EventData;
        }

        bool ScriptEvent::SetEventData(LuaPlus::LuaObject eventData)
        {
            m_EventData = eventData;
            m_bEventDataIsValid = vBuildEventFromScript();

            return m_bEventDataIsValid;
        }

        void ScriptEvent::RegisterEventTypeWithScript(const char* pKey, EventType type)
        {
            LuaPlus::LuaObject eventTypeTable = LuaStateManager::Get()->GetGlobalVars().GetByName("EventType");
            if (eventTypeTable.IsNil())
            {
                eventTypeTable = LuaStateManager::Get()->GetGlobalVars().CreateTable("EventType");
            }

            LOG_ASSERT(eventTypeTable.IsTable() && "Event is not a table!");
            LOG_ASSERT(eventTypeTable[pKey].IsNil() && "Event already exists!");

            eventTypeTable.SetNumber(pKey, (double) type);
        }

        void ScriptEvent::AddCreationFunction(EventType type, CreateEventForScriptFunctionType pCreationFunctionPtr)
        {
            LOG_ASSERT((s_CreationFunctions.find(type) == s_CreationFunctions.end()) && "Event type was not registered!");
            LOG_ASSERT((pCreationFunctionPtr != nullptr) && "pCreationFunctionPtr is NULL!");

            s_CreationFunctions.insert(std::make_pair(type, pCreationFunctionPtr));
        }

        ScriptEvent* ScriptEvent::CreateEventFromScript(EventType type)
        {
            CreationFunctions::iterator findIt = s_CreationFunctions.find(type);
            if (findIt != s_CreationFunctions.end())
            {
                CreateEventForScriptFunctionType pFunctionPtr = findIt->second;

                return pFunctionPtr();
            }
            else
            {
                LOG_ERROR("Could not find event type");

                return nullptr;
            }
        }

        void ScriptEvent::vBuildEventData()
        {
            m_EventData.AssignNil(LuaStateManager::Get()->GetLuaState());
        }

        bool ScriptEvent::vBuildEventFromScript()
        {
            return true;
        }

    }

}
