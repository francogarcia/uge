/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

#include <Utilities/PatternTemplates.h>

#include "Event.h"

namespace uge
{

    typedef fastdelegate::FastDelegate1<IEventDataSharedPointer> EventListenerDelegate;
    // TODO: Add multithreaded support.

    extern GenericObjectFactory<IEventData, EventType> g_eventFactory;

#define REGISTER_EVENT(eventClass) g_eventFactory.Register<eventClass>(eventClass::sk_EventType)
#define CREATE_EVENT(eventType) g_eventFactory.Create(eventType)

    class IEventManager
    {
    public:
        enum : unsigned long
        {
            kINFINITE = 0xFFFFFFFF
        };

        explicit IEventManager(std::string name, bool bIsGlobal);
        virtual ~IEventManager();

        // Registers a delegate function that will get called when the event type is triggered.  Returns true if
        // successful, false if not.
        virtual bool vAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

        // Removes a delegate / event type pairing from the internal tables.  Returns false if the pairing was not found.
        virtual bool vRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

        // Fire off event NOW.  This bypasses the queue entirely and immediately calls all delegate functions registered
        // for the event.
        virtual bool vTriggerEvent(const IEventDataSharedPointer& pEvent) const = 0;

        // Fire off event.  This uses the queue and will call the delegate function on the next call to VTick(), assuming
        // there's enough time.
        virtual bool vQueueEvent(const IEventDataSharedPointer& pEvent) = 0;
        virtual bool vThreadSafeQueueEvent(const IEventDataSharedPointer& pEvent) = 0;

        // Find the next-available instance of the named event type and remove it from the processing queue.  This
        // may be done up to the point that it is actively being processed ...  e.g.: is safe to happen during event
        // processing itself.
        //
        // if allOfType is true, then all events of that type are cleared from the input queue.
        //
        // returns true if the event was found and removed, false otherwise
        virtual bool vAbortEvent(const EventType& type, bool bIsAllOfType = false) = 0;

        // Allow for processing of any queued messages, optionally specify a processing time limit so that the event
        // processing does not take too long. Note the danger of using this artificial limiter is that all messages
        // may not in fact get processed.
        //
        // returns true if all messages ready for processing were completed, false otherwise (e.g. timeout )
        virtual bool vUpdate(unsigned long maxMillis = IEventManager::kINFINITE) = 0;

        // Getter for the main global event manager.  This is the event manager that is used by the majority of the
        // engine, though you are free to define your own as long as you instantiate it with setAsGlobal set to false.
        // It is not valid to have more than one global event manager.
        static IEventManager* Get();

    private:

    };

}
