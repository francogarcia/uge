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

namespace uge
{

    namespace lua
    {

        class ScriptEvent;
        typedef ScriptEvent* (*CreateEventForScriptFunctionType)(void);

#define REGISTER_SCRIPT_EVENT(eventClass, eventType) \
    ScriptEvent::RegisterEventTypeWithScript(#eventClass, eventType); \
    ScriptEvent::AddCreationFunction(eventType, &eventClass::CreateEventForScript)

#define EXPORT_FOR_SCRIPT_EVENT(eventClass) \
public: \
    static ScriptEvent* CreateEventForScript() \
    { \
        return new eventClass; \
    }

        class ScriptEvent : public BaseEventData
        {
        public:
            ScriptEvent();
            virtual ~ScriptEvent();

            LuaPlus::LuaObject GetEventData();
            bool SetEventData(LuaPlus::LuaObject eventData);

            static void RegisterEventTypeWithScript(const char* key, EventType type);
            static void AddCreationFunction(EventType type, CreateEventForScriptFunctionType pCreationFunctionPtr);
            static ScriptEvent* CreateEventFromScript(EventType type);

        protected:
            virtual void vBuildEventData();

            virtual bool vBuildEventFromScript();

        protected:
            LuaPlus::LuaObject m_EventData;

        private:
            typedef std::map<EventType, CreateEventForScriptFunctionType> CreationFunctions;
            static CreationFunctions s_CreationFunctions;

            bool m_bEventDataIsValid;
        };

    }

}
