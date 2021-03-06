/*
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

#pragma once

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>
#include <Core/Physics/PhysicsEvents.h>

namespace pg
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

    class EvtData_Player_Scored : public uge::BaseEventData
    {
    public:
        static const uge::EventType sk_EventType;

        explicit EvtData_Player_Scored(uge::ActorID id)
            : m_ActorID(id)
        {
            //
        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW EvtData_Player_Scored(m_ActorID));
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
            return "EvtData_Player_Scored";
        }

        uge::ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        uge::ActorID m_ActorID;
    };

    class EvtData_Ball_Wall_Collision : public uge::EvtData_PhysCollision
    {
    public:
        static const uge::EventType sk_EventType;

        EvtData_Ball_Wall_Collision(uge::ActorID actor1ID,
                                    uge::ActorID actor2ID,
                                    uge::Vector3 sumNormalForce,
                                    uge::Vector3 sumFrictionForce,
                                    uge::Vector3List collisionPoints)
            : EvtData_PhysCollision(actor1ID, actor2ID, sumNormalForce, sumFrictionForce, collisionPoints)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW EvtData_Ball_Wall_Collision(GetActorA(),
                                                                                    GetActorB(),
                                                                                    GetSumNormalForce(),
                                                                                    GetSumFrictionForce(),
                                                                                    GetCollisionPoints()));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            EvtData_PhysCollision::vSerialize(out);
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            EvtData_PhysCollision::vDeserialize(in);
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_Ball_Wall_Collision";
        }

    private:

    };

    class EvtData_Ball_Paddle_Collision : public uge::EvtData_PhysCollision
    {
    public:
        static const uge::EventType sk_EventType;

        EvtData_Ball_Paddle_Collision(uge::ActorID actor1ID,
                                      uge::ActorID actor2ID,
                                      uge::Vector3 sumNormalForce,
                                      uge::Vector3 sumFrictionForce,
                                      uge::Vector3List collisionPoints)
            : EvtData_PhysCollision(actor1ID, actor2ID, sumNormalForce, sumFrictionForce, collisionPoints)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW EvtData_Ball_Paddle_Collision(GetActorA(),
                                                                                      GetActorB(),
                                                                                      GetSumNormalForce(),
                                                                                      GetSumFrictionForce(),
                                                                                      GetCollisionPoints()));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            EvtData_PhysCollision::vSerialize(out);
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            EvtData_PhysCollision::vDeserialize(in);
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_Ball_Paddle_Collision";
        }
    };

    class EvtData_Paddle_Wall_Collision : public uge::EvtData_PhysCollision
    {
    public:
        static const uge::EventType sk_EventType;

        EvtData_Paddle_Wall_Collision(uge::ActorID actor1ID,
                                      uge::ActorID actor2ID,
                                      uge::Vector3 sumNormalForce,
                                      uge::Vector3 sumFrictionForce,
                                      uge::Vector3List collisionPoints)
            : EvtData_PhysCollision(actor1ID, actor2ID, sumNormalForce, sumFrictionForce, collisionPoints)
        {

        }

        virtual const uge::EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual uge::IEventDataSharedPointer vCopy() const override
        {
            return uge::IEventDataSharedPointer(LIB_NEW EvtData_Paddle_Wall_Collision(GetActorA(),
                                                                                      GetActorB(),
                                                                                      GetSumNormalForce(),
                                                                                      GetSumFrictionForce(),
                                                                                      GetCollisionPoints()));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            EvtData_PhysCollision::vSerialize(out);
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            EvtData_PhysCollision::vDeserialize(in);
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_Paddle_Wall_Collision";
        }

    private:

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

}
