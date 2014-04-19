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
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include "IEventManager.h"

#include <Utilities/System/Time.h>

namespace uge
{

    class EventManager : public IEventManager
    {
    public:
        explicit EventManager(std::string name, bool bIsGlobal);
        virtual ~EventManager();

        virtual bool vAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;

        virtual bool vRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) override;

        virtual bool vTriggerEvent(const IEventDataSharedPointer& pEvent) const override;

        virtual bool vQueueEvent(const IEventDataSharedPointer& pEvent) override;
        virtual bool vThreadSafeQueueEvent(const IEventDataSharedPointer& pEvent) override;

        virtual bool vAbortEvent(const EventType& type, bool bIsAllOfType = false) override;

        virtual bool vUpdate(unsigned long maxMillis = IEventManager::kINFINITE) override;

    private:
        static const unsigned int TOTAL_EVENT_MANAGER_QUEUES = 2;

        typedef std::list<EventListenerDelegate> EventListenerList;
        typedef std::map<EventType, EventListenerList> EventListenerMap;
        typedef std::list<IEventDataSharedPointer> EventQueue;

        EventListenerMap m_EventListeners;
        EventQueue m_Queues[TOTAL_EVENT_MANAGER_QUEUES];
        int m_ActiveQueueNumber;  // index of actively processing queue; events enque to the opposing queue

        // TODO: Implement a multi threaded queue.
        //ThreadSafeEventQueue m_RealtimeEventQueue;
    };

}
