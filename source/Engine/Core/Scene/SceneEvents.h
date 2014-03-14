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
