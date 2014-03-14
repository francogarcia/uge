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
