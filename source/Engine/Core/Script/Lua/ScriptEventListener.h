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

#pragma once

#include <Core/Events/IEventManager.h>

#include "LuaStateManager.h"

namespace uge
{

    class ScriptEventListener : public IEventListener
    {
    public:
        ScriptEventListener(LuaPlus::LuaObject explicitHandlerFunction);

        virtual ~ScriptEventListener()
        {
        }

        virtual char const* GetName(void)
        {
            return "Script Listener";
        }

        virtual bool HandleEvent(LuaPlus::ILuaTable const& event);

        const LuaPlus::LuaObject& GetHandlerFunction(void) const
        {
            return m_HandlerFunction;
        }

    protected:
        virtual bool VCallLuaFunction(LuaPlus::LuaObject& eventData);

        LuaPlus::LuaObject m_HandlerFunction;
    };

    class ScriptActorEventListener : public ScriptEventListener
    {
    public:
        ScriptActorEventListener(LuaPlus::LuaObject explicitHandlerFunction, const ActorId actorID);

        virtual ~ScriptActorEventListener()
        {
        }

        virtual char const* GetName(void)
        {
            return "Script Actor Listener";
        }

        ActorId GetActorID(void) const
        {
            return m_SrcActorID;
        }

    private:

        // This will pass the event data object as well as
        // look up our actor's specific script data to pass.
        virtual bool VCallLuaFunction(LuaPlus::LuaObject& eventData);

        // Our source actor.
        const ActorId m_SrcActorID;
    };

}
