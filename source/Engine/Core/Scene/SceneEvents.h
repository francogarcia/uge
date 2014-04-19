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
#include <Core/Events/IEventManager.h>

#include <Utilities/Math/Matrix.h>

#include "ISceneNode.h"

namespace uge
{

    class EvtData_Scene_Node_Attached : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType(void) const
        {
            return sk_EventType;
        }

        EvtData_Scene_Node_Attached(ActorID actorID, const Matrix4& transform)
            : m_ActorID(actorID), m_Transform(transform)
        {
            //
        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_ActorID;
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            in >> m_ActorID;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Scene_Node_Attached(m_ActorID, m_Transform));
        }

        virtual const char* vGetName(void) const override
        {
            return "EvtData_Scene_Node_Attached";
        }

        ActorID GetActorID(void) const
        {
            return m_ActorID;
        }

        Matrix4 GetTransform() const
        {
            return m_Transform;
        }

    private:
        ActorID m_ActorID;
        Matrix4 m_Transform;
    };

    class EvtData_Scene_Node_Removed : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        virtual const EventType& vGetEventType(void) const
        {
            return sk_EventType;
        }

        EvtData_Scene_Node_Removed(ActorID actorID)
            : m_ActorID(actorID)
        {

        }

        virtual void vSerialize(std::ostrstream& out) const override
        {
            out << m_ActorID;
        }

        virtual void vDeserialize(std::istrstream& in) override
        {
            in >> m_ActorID;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Scene_Node_Removed(m_ActorID));
        }

        virtual const char* vGetName(void) const override
        {
            return "EvtData_Scene_Node_Removed";
        }

        ActorID GetActorID(void) const
        {
            return m_ActorID;
        }

    private:
        ActorID m_ActorID;
    };

    class EvtData_Changed_Render_Component : public BaseEventData
    {
    public:
        static const EventType sk_EventType;

        EvtData_Changed_Render_Component(ActorID actorID)
            : m_ActorID(actorID)
        {

        }

        virtual const EventType& vGetEventType() const override
        {
            return sk_EventType;
        }

        virtual IEventDataSharedPointer vCopy() const override
        {
            return IEventDataSharedPointer(LIB_NEW EvtData_Changed_Render_Component(m_ActorID));
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
            return "EvtData_Changed_Render_Component";
        }

        ActorID GetActorID() const
        {
            return m_ActorID;
        }

    private:
        ActorID m_ActorID;
    };

}
