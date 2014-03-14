//========================================================================
// ScriptEvent.cpp
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
#include "ScriptEvent.h"
#include "LuaStateManager.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    ScriptEvent::CreationFunctions ScriptEvent::s_CreationFunctions;

    ScriptEvent::ScriptEvent() : m_bEventDataIsValid(false)
    {

    }

    ScriptEvent::~ScriptEvent()
    {

    }

    //---------------------------------------------------------------------------------------------------------------------
    // Returns the event data after building it (if necessary)
    //---------------------------------------------------------------------------------------------------------------------
    LuaPlus::LuaObject ScriptEvent::GetEventData()
    {
        if (!m_bEventDataIsValid)
        {
            vBuildEventData();
            m_bEventDataIsValid = true;
        }

        return m_EventData;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // This function is called when an event is sent from the script.  It sets the m_EventData member and calls
    // VBuildEventFromScript().
    //---------------------------------------------------------------------------------------------------------------------
    bool ScriptEvent::SetEventData(LuaPlus::LuaObject eventData)
    {
        m_EventData = eventData;
        m_bEventDataIsValid = vBuildEventFromScript();

        return m_bEventDataIsValid;
    }

    //---------------------------------------------------------------------------------------------------------------------
    // This function is called to register an event type with the script to link them.  The simplest way to do this is
    // with the REGISTER_SCRIPT_EVENT() macro, which calls this function.
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptEvent::RegisterEventTypeWithScript(const char* key, EventType type)
    {
        // get or create the EventType table
        LuaPlus::LuaObject eventTypeTable = LuaStateManager::Get()->GetGlobalVars().GetByName("EventType");
        if (eventTypeTable.IsNil())
        {
            eventTypeTable = LuaStateManager::Get()->GetGlobalVars().CreateTable("EventType");
        }

        // error checking
        LOG_ASSERT(eventTypeTable.IsTable() && "Event is not a table!");
        LOG_ASSERT(eventTypeTable[key].IsNil() && "Event is nil!");

        // add the entry
        eventTypeTable.SetNumber(key, (double) type);
    }

    //---------------------------------------------------------------------------------------------------------------------
    // This function is called to map an event creation function pointer with the event type.  This allows an event to be
    // created by only knowing its type.  This is required to allow scripts to trigger the instantiation and queueing of
    // events.
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptEvent::AddCreationFunction(EventType type, CreateEventForScriptFunctionType pCreationFunctionPtr)
    {
        LOG_ASSERT((s_CreationFunctions.find(type) == s_CreationFunctions.end()) && "Event type was not registered!");
        LOG_ASSERT((pCreationFunctionPtr != nullptr) && "pCreationFunctionPtr is NULL!");

        s_CreationFunctions.insert(std::make_pair(type, pCreationFunctionPtr));
    }

    //---------------------------------------------------------------------------------------------------------------------
    //
    //---------------------------------------------------------------------------------------------------------------------
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

    //---------------------------------------------------------------------------------------------------------------------
    // Default implementation for vBuildEventData() sets the event data to nil.
    //---------------------------------------------------------------------------------------------------------------------
    void ScriptEvent::vBuildEventData()
    {
        m_EventData.AssignNil(LuaStateManager::Get()->GetLuaState());
    }

    bool ScriptEvent::vBuildEventFromScript()
    {
        return true;
    }

}
