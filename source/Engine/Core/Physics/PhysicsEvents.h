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
#include <Core/Events/IEventManager.h>
#include <Utilities/Math/MathStd.h>

namespace uge
{

    class EvtData_PhysTrigger_Enter : public BaseEventData
    {
        int m_TriggerID;
        ActorID m_ActorID;

    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        EvtData_PhysTrigger_Enter()
            : m_TriggerID(-1),
              m_ActorID(Actor::NULL_ACTOR_ID)
        {

        }

        explicit EvtData_PhysTrigger_Enter(int triggerID, ActorID actorID)
            : m_TriggerID(triggerID),
              m_ActorID(actorID)
        {


        }

        IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_PhysTrigger_Enter(m_TriggerID, m_ActorID));
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_PhysTrigger_Enter";
        }

        int GetTriggerID() const
        {
            return m_TriggerID;
        }

        ActorID GetOtherActorID() const
        {
            return m_ActorID;
        }
    };

    class EvtData_PhysTrigger_Leave : public BaseEventData
    {
        int m_TriggerID;
        ActorID m_ActorID;

    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        EvtData_PhysTrigger_Leave()
            : m_TriggerID(-1),
              m_ActorID(Actor::NULL_ACTOR_ID)
        {

        }
        explicit EvtData_PhysTrigger_Leave(int triggerID, ActorID other)
            : m_TriggerID(triggerID),
              m_ActorID(other)
        {

        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_PhysTrigger_Leave(m_TriggerID, m_ActorID));
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_PhysTrigger_Leave";
        }

        int GetTriggerID() const
        {
            return m_TriggerID;
        }

        ActorID GetOtherActor() const
        {
            return m_ActorID;
        }
    };

    class EvtData_PhysCollision : public /*ScriptEvent*/ BaseEventData
    {
        ActorID m_ActorA;
        ActorID m_ActorB;
        Vector3 m_SumNormalForce;
        Vector3 m_SumFrictionForce;
        std::list<Vector3> m_CollisionPoints;

    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        EvtData_PhysCollision()
            : m_ActorA(Actor::NULL_ACTOR_ID),
              m_ActorB(Actor::NULL_ACTOR_ID),
              m_SumNormalForce(0.0f, 0.0f, 0.0f),
              m_SumFrictionForce(0.0f, 0.0f, 0.0f)
        {

        }

        explicit EvtData_PhysCollision(ActorID actorA,
                                       ActorID actorB,
                                       Vector3 sumNormalForce,
                                       Vector3 sumFrictionForce,
                                       Vector3List collisionPoints)
            : m_ActorA(actorA),
              m_ActorB(actorB),
              m_SumNormalForce(sumNormalForce),
              m_SumFrictionForce(sumFrictionForce),
              m_CollisionPoints(collisionPoints)
        {


        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_PhysCollision(m_ActorA, m_ActorB, m_SumNormalForce, m_SumFrictionForce, m_CollisionPoints));
        }

        virtual const char* vGetName() const
        {
            return "EvtData_PhysCollision";
        }

        ActorID GetActorA() const
        {
            return m_ActorA;
        }

        ActorID GetActorB() const
        {
            return m_ActorB;
        }

        const Vector3& GetSumNormalForce() const
        {
            return m_SumNormalForce;
        }

        const Vector3& GetSumFrictionForce() const
        {
            return m_SumFrictionForce;
        }

        const Vector3List& GetCollisionPoints() const
        {
            return m_CollisionPoints;
        }

        //void EvtData_PhysCollision::vBuildEventData(void)
        //{
        //    m_eventData.AssignNewTable(LuaStateManager::Get()->GetLuaState());
        //    m_eventData.SetInteger("actorA", m_ActorA);
        //    m_eventData.SetInteger("actorB", m_ActorB);
        //}
    };


    class EvtData_PhysSeparation : public BaseEventData
    {
        ActorID m_ActorA;
        ActorID m_ActorB;

    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        EvtData_PhysSeparation()
            : m_ActorA(Actor::NULL_ACTOR_ID),
              m_ActorB(Actor::NULL_ACTOR_ID)
        {

        }

        explicit EvtData_PhysSeparation(ActorID actorA, ActorID actorB)
            : m_ActorA(actorA),
              m_ActorB(actorB)
        {

        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_PhysSeparation(m_ActorA, m_ActorB));
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_PhysSeparation";
        }

        ActorID GetActorA() const
        {
            return m_ActorA;
        }

        ActorID GetActorB() const
        {
            return m_ActorB;
        }
    };

}
