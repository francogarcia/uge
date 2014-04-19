/*
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
