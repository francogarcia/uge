/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>
#include <Core/Physics/PhysicsEvents.h>

namespace sg
{

    class AlienDestroyed : public uge::BaseEventData
    {
    public:
        static const uge::EventType sk_EventType;

        explicit AlienDestroyed(uge::ActorID actorID)
            : m_ActorID(actorID)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW AlienDestroyed(m_ActorID));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_ActorID;
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            in >> m_ActorID;
        }

        virtual const char* vGetName() const override
        {
            return "AlienDestroyed";
        }

        uge::ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        uge::ActorID m_ActorID;
    };

    class MoveActor : public uge::BaseEventData
    {
    public:
        /// Relative to the X-axis.
        enum class Direction : char
        {
            Left,
            Right
        };

        static const uge::EventType sk_EventType;

        explicit MoveActor(uge::ActorID actorID, MoveActor::Direction direction)
            : m_ActorID(actorID), m_Direction(direction)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW MoveActor(m_ActorID, m_Direction));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_ActorID << static_cast<char>(m_Direction);
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            char directionValue;

            in >> m_ActorID >> directionValue;
            
            m_Direction = static_cast<MoveActor::Direction>(directionValue);
        }

        virtual const char* vGetName() const override
        {
            return "MoveActor";
        }

        uge::ActorID GetActorID() const
        {
            return m_ActorID;
        }

        MoveActor::Direction GetDirection() const
        {
            return m_Direction;
        }

    private:
        uge::ActorID m_ActorID;
        MoveActor::Direction m_Direction;
    };

    class StopActor : public uge::BaseEventData
    {
    public:
        static const uge::EventType sk_EventType;

        explicit StopActor(uge::ActorID actorID)
            : m_ActorID(actorID)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW StopActor(m_ActorID));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_ActorID;
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            in >> m_ActorID;
        }

        virtual const char* vGetName() const override
        {
            return "StopActor";
        }

        uge::ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        uge::ActorID m_ActorID;
    };


    class FireProjectile : public uge::BaseEventData
    {
    public:

        enum class Type : char
        {
            Bullet,
            Bomb
        };

        static const uge::EventType sk_EventType;

        explicit FireProjectile(uge::ActorID actorID, FireProjectile::Type type)
            : m_ActorID(actorID), m_Type(type)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW FireProjectile(m_ActorID, m_Type));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_ActorID << static_cast<char>(m_Type);
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            char directionValue;

            in >> m_ActorID >> directionValue;
            
            m_Type = static_cast<FireProjectile::Type>(directionValue);
        }

        virtual const char* vGetName() const override
        {
            return "FireProjectile";
        }

        uge::ActorID GetActorID() const
        {
            return m_ActorID;
        }

        FireProjectile::Type GetType() const
        {
            return m_Type;
        }

    private:
        uge::ActorID m_ActorID;
        FireProjectile::Type m_Type;
    };
}
