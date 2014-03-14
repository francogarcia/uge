#include <stdio.h>

#include <Core/Events/Event.h>
#include <Core/Events/EventManager.h>

#include <Utilities/System/Clock.h>
#include <Utilities/System/Time.h>

class Event : public uge::BaseEventData
{
public:
    static const uge::EventType sk_EventType;

    explicit Event(unsigned int value)
        : m_Value(value)
    {

    }

    virtual const uge::EventType& vGetEventType() const override
    {
        return sk_EventType;
    }

    virtual uge::IEventDataSharedPointer vCopy() const override
    {
        return uge::IEventDataSharedPointer(LIB_NEW Event(m_Value));
    }

    virtual void vSerialize(std::ostrstream& out) const override
    {
        out << m_Value;
    }

    virtual void vDeserialize(std::istrstream& in) override
    {
        in >> m_Value;
    }

    virtual const char* vGetName() const override
    {
        return "Event";
    }

    unsigned int GetValue() const
    {
        return m_Value;
    }

private:
    unsigned int m_Value;
};

const uge::EventType Event::sk_EventType(0xbd131e2d);

class EventClass
{
public:
    EventClass()
    {

    }

    ~EventClass()
    {

    }

    void EventHandlerMethod(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<Event> pData = std::static_pointer_cast<Event>(pEventData);

        printf("[EventClass:EventHandlerMethod()] Event received! Value =  %u.\n", pData->GetValue());
    }
};

void EventHandlerFunction(uge::IEventDataSharedPointer pEventData)
{
    std::shared_ptr<Event> pData = std::static_pointer_cast<Event>(pEventData);

    printf("[EventHandlerFunction()] Event received! Value =  %u.\n", pData->GetValue());
}

void RandomlyCreateEvent()
{
    const unsigned int kChance = 10;
    const unsigned int kJackPot = 100;

    unsigned int value = rand() % 100 + 1;
    if (value < kChance)
    {
        std::shared_ptr<Event> pNewActorEvent(LIB_NEW Event(value));
        // Event will be triggered during the vUpdate() call.
        uge::IEventManager::Get()->vQueueEvent(pNewActorEvent);
    }
    else if (value == kJackPot)
    {
        std::shared_ptr<Event> pNewActorEvent(LIB_NEW Event(value));
        // Event will be triggered now, before the vUpdate() call.
        uge::IEventManager::Get()->vTriggerEvent(pNewActorEvent);
    }
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    // Create the event manager.
    uge::IEventManager* pEventManager = new uge::EventManager("Global Event Manager", true);

    // Creating and registering the event handlers.
    uge::EventListenerDelegate functionDelegate = fastdelegate::FastDelegate1<uge::IEventDataSharedPointer>(EventHandlerFunction);
    uge::IEventManager::Get()->vAddListener(functionDelegate, Event::sk_EventType);

    EventClass eventClass;
    functionDelegate = fastdelegate::MakeDelegate(&eventClass, &EventClass::EventHandlerMethod);
    uge::IEventManager::Get()->vAddListener(functionDelegate, Event::sk_EventType);

    // Running.
    const unsigned long kMaxTimeToUpdate = 10u;
    const unsigned long kTimeToRun = 10000u; // In milliseconds.
    unsigned long timeElapsed = 0u;

    uge::Time::TimePoint lastTime = uge::Time::GetTime();
    while (timeElapsed < kTimeToRun)
    {
        uge::Time::TimePoint currentTime = uge::Time::GetTime();
        unsigned long timeDelta = uge::Time::GetDeltaAsMilliseconds(currentTime, lastTime);

        RandomlyCreateEvent();

        pEventManager->vUpdate(kMaxTimeToUpdate);

        lastTime = currentTime;
        timeElapsed += timeDelta;
    }

    printf("\nTime elapsed: %u.\n", timeElapsed);

    // Unregistering the event handlers.
    functionDelegate = fastdelegate::FastDelegate1<uge::IEventDataSharedPointer>(EventHandlerFunction);
    uge::IEventManager::Get()->vRemoveListener(functionDelegate, Event::sk_EventType);

    functionDelegate = fastdelegate::MakeDelegate(&eventClass, &EventClass::EventHandlerMethod);
    uge::IEventManager::Get()->vRemoveListener(functionDelegate, Event::sk_EventType);

    // Delete the event manager.
    SAFE_DELETE(pEventManager);

    return 0;
}
