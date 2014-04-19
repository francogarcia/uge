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

#include "GameEngineStd.h"

#include "EventManager.h"

namespace uge
{

    EventManager::EventManager(std::string name, bool bIsGlobal) : IEventManager(name, bIsGlobal)
    {
        m_ActiveQueueNumber = 0;
    }

    EventManager::~EventManager()
    {

    }

    bool EventManager::vAddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
    {
        EventListenerList& eventListenerList = m_EventListeners[type];
        for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
        {
            if ((*it) == eventDelegate)
            {
                return false;
            }
        }

        eventListenerList.push_back(eventDelegate);

        return true;
    }

    bool EventManager::vRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
    {
        bool bStatus = false;

        auto findIt = m_EventListeners.find(type);
        if (findIt != m_EventListeners.end())
        {
            EventListenerList& listeners = findIt->second;
            for (auto it = listeners.begin(); it != listeners.end(); ++it)
            {
                if (eventDelegate == (*it))
                {
                    listeners.erase(it);
                    bStatus = true;
                    break;  // we don't need to continue because it should be impossible for the same delegate function to be registered for the same event more than once
                }
            }
        }

        return bStatus;
    }

    bool EventManager::vTriggerEvent(const IEventDataSharedPointer& pEvent) const
    {
        bool bProccessed = false;

        auto findIt = m_EventListeners.find(pEvent->vGetEventType());
        if (findIt != m_EventListeners.end())
        {
            const EventListenerList& eventListenerList = findIt->second;
            for (EventListenerList::const_iterator it = eventListenerList.begin();
                 it != eventListenerList.end();
                 ++it)
            {
                EventListenerDelegate listener = *it;
                listener(pEvent);
                bProccessed = true;
            }
        }

        return bProccessed;
    }

    bool EventManager::vQueueEvent(const IEventDataSharedPointer& pEvent)
    {
        assert((m_ActiveQueueNumber >= 0) && "Invalid queue!");
        assert((m_ActiveQueueNumber < TOTAL_EVENT_MANAGER_QUEUES) && "Invalid queue!");

        if (!pEvent)
        {
            return false;
        }

        auto findIt = m_EventListeners.find(pEvent->vGetEventType());
        if (findIt != m_EventListeners.end())
        {
            m_Queues[m_ActiveQueueNumber].push_back(pEvent);

            return true;
        }

        return false;
    }

    bool EventManager::vThreadSafeQueueEvent(const IEventDataSharedPointer& pEvent)
    {
        // TODO
        //m_RealtimeEventQueue.push(pEvent);

        return true;
    }

    bool EventManager::vAbortEvent(const EventType& type, bool bIsAllOfType)
    {
        assert((m_ActiveQueueNumber >= 0) && "Invalid queue!");
        assert((m_ActiveQueueNumber < TOTAL_EVENT_MANAGER_QUEUES) && "Invalid queue!");

        bool bSuccess = false;

        EventListenerMap::iterator findIt = m_EventListeners.begin();
        if (findIt != m_EventListeners.end())
        {
            EventQueue& eventQueue = m_Queues[m_ActiveQueueNumber];
            auto it = eventQueue.begin();
            while (it != eventQueue.end())
            {
                auto thisIt = it;
                ++it;

                if ((*thisIt)->vGetEventType() == type)
                {
                    eventQueue.erase(thisIt);
                    bSuccess = true;
                    if (!bIsAllOfType)
                    {
                        break;
                    }
                }
            }
        }

        return bSuccess;
    }

    bool EventManager::vUpdate(unsigned long maxMillis)
    {
        // FIXME: use unsigned long instead.
        unsigned long currMs = Time::GetTimeNowAsMilliseconds();
        unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ? (IEventManager::kINFINITE) : (currMs + maxMillis));

        //// This section added to handle events from other threads.  Check out Chapter 20.
        //IEventDataSharedPointer pRealtimeEvent;
        //while (m_realtimeEventQueue.try_pop(pRealtimeEvent))
        //{
        //	vQueueEvent(pRealtimeEvent);

        //	currMs = GetTickCount();
        //	if (maxMillis != IEventManager::kINFINITE)
        //	{
        //		if (currMs >= maxMs)
        //		{
        //			LOG_ERROR("A realtime process is spamming the event manager!");
        //		}
        //	}
        //}

        // swap active queues and clear the new queue after the swap
        int queueToProcess = m_ActiveQueueNumber;
        m_ActiveQueueNumber = (m_ActiveQueueNumber + 1) % TOTAL_EVENT_MANAGER_QUEUES;
        m_Queues[m_ActiveQueueNumber].clear();

        // Task the queue
        while (!m_Queues[queueToProcess].empty())
        {
            // pop the front of the queue
            IEventDataSharedPointer pEvent = m_Queues[queueToProcess].front();
            m_Queues[queueToProcess].pop_front();

            const EventType& eventType = pEvent->vGetEventType();

            // find all the delegate functions registered for this event
            auto findIt = m_EventListeners.find(eventType);
            if (findIt != m_EventListeners.end())
            {
                const EventListenerList& eventListeners = findIt->second;

                // call each listener
                for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
                {
                    EventListenerDelegate listener = (*it);
                    listener(pEvent);
                }
            }

            // check to see if time ran out
            currMs = Time::GetTimeNowAsMilliseconds();
            if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
            {
                break;
            }
        }

        // If we couldn't process all of the events, push the remaining events to the new active queue.
        // Note: To preserve sequencing, go back-to-front, inserting them at the head of the active queue
        bool bQueueFlushed = (m_Queues[queueToProcess].empty());
        if (!bQueueFlushed)
        {
            while (!m_Queues[queueToProcess].empty())
            {
                IEventDataSharedPointer pEvent = m_Queues[queueToProcess].back();
                m_Queues[queueToProcess].pop_back();
                m_Queues[m_ActiveQueueNumber].push_front(pEvent);
            }
        }

        return bQueueFlushed;
    }

}
