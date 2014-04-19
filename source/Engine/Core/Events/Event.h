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

namespace uge
{

    class IEventData;

    typedef unsigned int EventType;
    typedef std::shared_ptr<IEventData> IEventDataSharedPointer;

    class IEventData
    {
    public:
        IEventData();

        virtual ~IEventData();

        virtual const EventType& vGetEventType() const = 0;
        virtual unsigned long vGetTimeStamp() const = 0;
        virtual void vSerialize(std::ostrstream& out) const = 0;
        virtual void vDeserialize(std::istrstream& in) = 0;
        virtual IEventDataSharedPointer vCopy() const = 0;
        virtual const char* vGetName() const = 0;
    };

    class BaseEventData : public IEventData
    {
    public:
        explicit BaseEventData(const unsigned long timeStamp = 0u);
        virtual ~BaseEventData();

        virtual const EventType& vGetEventType() const = 0;

        virtual unsigned long vGetTimeStamp() const override;

        virtual void vSerialize(std::ostrstream& out) const override;

        virtual void vDeserialize(std::istrstream& in) override;

        virtual IEventDataSharedPointer vCopy() const = 0;
        virtual const char* vGetName() const = 0;

    private:
        const unsigned long m_TimeStamp;
    };

}
