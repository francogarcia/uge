#pragma once

#include <Core/Events/Event.h>

#include "GameCommandTypes.h"

namespace uge
{
    // FIXME: add this to the event section.
    /**
     *  Can be overloaded.
     */
    class EvtData_Command_Performed : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        EvtData_Command_Performed(GameCommandID commandID)
            : m_CommandID(commandID)
        {

        }

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Command_Performed(m_CommandID));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_CommandID;
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            in >> m_CommandID;
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_Command_Performed";
        }

        GameCommandID GetCommandID() const
        {
            return m_CommandID;
        }

    private:
        GameCommandID m_CommandID;
    };
}
