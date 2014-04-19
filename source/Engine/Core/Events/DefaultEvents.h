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

#pragma once

#include <Core/EntityComponent/Entity/Actor.h>
#include <Utilities/Math/MathStd.h>

#include "IEventManager.h"

namespace uge
{

    // TODO: add more default events when relevant systems are added (c.f. GCC, p. 325).
    // FIXME: refactor EvtData prefix into a namespace (Event, for instance).
    // namespace Event
    // {
    //
    // }

    class EvtData_New_Actor : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        explicit EvtData_New_Actor(ActorID actorID)
            : m_ActorID(actorID)
        {
            //
        }

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_New_Actor(m_ActorID));
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
            return "EvtData_New_Actor";
        }

        ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        ActorID m_ActorID;
    };

    //---------------------------------------------------------------------------------------------------------------------
    // class EvtData_Request_New_Actor
    // This event is sent by a server asking Client proxy logics to create new actors from their local resources.
    // It can be sent from script or via code.
    // This event is also sent from the server game logic to client logics AFTER it has created a new actor. The logics will allow follow suit to stay in sync.
    //---------------------------------------------------------------------------------------------------------------------
    class EvtData_Request_New_Actor : public BaseEventData
    {
        std::string m_actorResource;
        bool m_hasInitialTransform;
        Matrix4 m_initialTransform;

    public:
        static const EventType sk_EventType;

        explicit EvtData_Request_New_Actor(const std::string& actorResource, const Matrix4* initialTransform = nullptr)
            : m_actorResource(actorResource)
        {
            m_actorResource = actorResource;
            if (initialTransform)
            {
                m_hasInitialTransform = true;
                m_initialTransform = *initialTransform;
            }
            else
            {
                m_hasInitialTransform = false;
            }
        }

        virtual const EventType& vGetEventType(void) const override
        {
            return sk_EventType;
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            //in >> m_actorResource;
            //in >> m_hasInitialTransform;
            //if (m_hasInitialTransform)
            //{
            //    for (int i = 0; i < 4; ++i)
            //    {
            //        for (int j = 0; j < 4; ++j)
            //        {
            //            in >> m_initialTransform.m[i][j];
            //        }
            //    }
            //}
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Request_New_Actor(m_actorResource, (m_hasInitialTransform) ? &m_initialTransform : nullptr));
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            //out << m_actorResource << " ";
            //out << m_hasInitialTransform << " ";
            //if (m_hasInitialTransform)
            //{
            //    for (int i = 0; i < 4; ++i)
            //    {
            //        for (int j = 0; j < 4; ++j)
            //        {
            //            out << m_initialTransform.m[i][j] << " ";
            //        }
            //    }
            //}
        }

        virtual const char* vGetName(void) const
        {
            return "EvtData_Request_New_Actor";
        }

        const std::string& GetActorResource(void) const
        {
            return m_actorResource;
        }

        const Matrix4* GetInitialTransform(void) const
        {
            return (m_hasInitialTransform) ? &m_initialTransform : nullptr;
        }
    };


    //---------------------------------------------------------------------------------------------------------------------
    // EvtData_Destroy_Actor - sent when actors are destroyed
    //---------------------------------------------------------------------------------------------------------------------
    class EvtData_Destroy_Actor : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        explicit EvtData_Destroy_Actor(ActorID actorID = Actor::NULL_ACTOR_ID)
            : m_ActorID(actorID)
        {
            //
        }

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Destroy_Actor(m_ActorID));
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
            return "EvtData_Destroy_Actor";
        }

        ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        ActorID m_ActorID;
    };


    //---------------------------------------------------------------------------------------------------------------------
    // EvtData_Request_Start_Game - this is sent by the authoritative game logic to all views so they will load a game level.
    //---------------------------------------------------------------------------------------------------------------------
    class EvtData_Request_Start_Game : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        EvtData_Request_Start_Game()
        {

        }

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Request_Start_Game());
        }

        virtual const char* vGetName() const override
        {
            return "EvtData_Request_Start_Game";
        }
    };

    class EvtData_Move_Actor : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType(void) const
        {
            return sk_EventType;
        }

        EvtData_Move_Actor(void) : m_ActorID(Actor::NULL_ACTOR_ID)
        {

        }

        EvtData_Move_Actor(ActorID id, const Matrix4& matrix)
            : m_ActorID(id), m_Transform(matrix)
        {
            //
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            //out << m_ActorID << " ";
            //for (int i=0; i<4; ++i)
            //{
            //    for (int j=0; j<4; ++j)
            //    {
            //        out << m_Transform.m[i][j] << " ";
            //    }
            //}
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            //in >> m_ActorID;
            //for (int i=0; i<4; ++i)
            //{
            //    for (int j=0; j<4; ++j)
            //    {
            //        in >> m_Transform.m[i][j];
            //    }
            //}
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Move_Actor(m_ActorID, m_Transform));
        }

        virtual const char* vGetName(void) const override
        {
            return "EvtData_Move_Actor";
        }

        ActorID GetActorID(void) const
        {
            return m_ActorID;
        }

        const Matrix4& GetTransform(void) const
        {
            return m_Transform;
        }

    private:
        ActorID m_ActorID;
        Matrix4 m_Transform;
    };

    class EvtData_Set_Controlled_Actor : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        explicit EvtData_Set_Controlled_Actor(ActorID actorID)
            : m_ActorID(actorID)
        {
            //
        }

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Set_Controlled_Actor(m_ActorID));
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
            return "EvtData_Set_Controlled_Actor";
        }

        ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        ActorID m_ActorID;
    };

}
