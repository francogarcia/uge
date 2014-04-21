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

// FIXME: implement this.
#include "ScriptEventListener.h"
#include "../GameCode4/GameCode.h"
#include <LuaPlus.h>

namespace uge
{

    ScriptEventListener::ScriptEventListener(LuaPlus::LuaObject explicitHandlerFunction)
        : m_HandlerFunction(explicitHandlerFunction)
    {
        assert(explicitHandlerFunction.IsFunction() && "Script listener *MUST* be a valid function!");
    }

    bool ScriptEventListener::HandleEvent(LuaPlus::ILuaable const& luaable)
    {
        if (false == luaable.VHasLuaEventData())
        {
            ILuaable& NCLuaable = const_cast< ILuaable& >(luaable);

            NCLuaable.VBuildLuaEventData();
        }

        LuaObject& eventDataObj = luaable.VGetLuaEventData();

        const bool bResult = VCallLuaFunction(eventDataObj);

        return bResult;
    }

    bool ScriptEventListener::VCallLuaFunction(LuaObject& eventData)
    {
        LuaFunction<bool> function(m_HandlerFunction);
        return function(eventData);
    }

    ScriptActorEventListener::ScriptActorEventListener(LuaObject explicitHandlerFunction, const ActorId actorID)
        : ScriptEventListener(explicitHandlerFunction)
        , m_SrcActorID(actorID)
    {
    }

    bool ScriptActorEventListener::VCallLuaFunction(LuaObject& eventData)
    {
        // Find our actor to pass in the actor script data context.

        // This is more sanity checking than anything, to ensure that the actor
        // still exists.
        ActorSharedPointer gameActor = g_pApp->m_pGame->VGetActor(m_SrcActorID);
        if (!gameActor)
        {
            assert(0 && "Attempted to call a script listener for an actor that couldn't be found!  Did you delete the actor without removing all listeners?");
            return false;
        }

        // Get ahold of the actor's script data.
        LuaState* pState = g_pApp->m_pLuaStateManager->GetGlobalState().Get();
        LuaObject globalActorTable = g_pApp->m_pLuaStateManager->GetGlobalActorTable();
        assert(globalActorTable.IsTable() && "Global actor table is NOT a table!");
        LuaObject actorData = globalActorTable[ m_SrcActorID ];

        // We pass in the event data IN ADDITION TO the actor's script data.
        LuaFunction<bool> function(m_HandlerFunction);
        return function(eventData, actorData);
    }

}
