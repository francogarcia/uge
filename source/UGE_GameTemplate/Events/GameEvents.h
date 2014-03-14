#pragma once

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>
#include <Core/Physics/PhysicsEvents.h>

namespace sg
{

class EvtData_Restart_Game : public uge::BaseEventData
{
public:
    static const uge::EventType sk_EventType;

    explicit EvtData_Restart_Game()
    {

    }

    virtual const uge::EventType& vGetEventType() const override
    {
        return sk_EventType;
    }

    virtual uge::IEventDataSharedPointer vCopy() const override
    {
        return uge::IEventDataSharedPointer(LIB_NEW EvtData_Restart_Game());
    }

    virtual void vSerialize(std::ostrstream& out) const override
    {

    }

    virtual void vDeserialize(std::istrstream& in) override
    {

    }

    virtual const char* vGetName() const override
    {
        return "EvtData_Restart_Game";
    }
};

}
