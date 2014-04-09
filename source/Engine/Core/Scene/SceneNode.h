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
#include <Utilities/Math/MathStd.h>

#include "ISceneNode.h"
#include "SceneNodeProperties.h"

namespace uge
{

    class SceneNode;
    typedef std::shared_ptr<SceneNode> SceneNodeSharedPointer;

    class SceneNode : public ISceneNode
    {
        friend class Scene;

    public:
        SceneNode(ActorID actorID, ActorWeakPointer pActor, RenderPass renderPass, const Matrix4* pToWorld, const Matrix4* pFromWorld = nullptr);
        SceneNode(ActorID actorID, ActorWeakPointer pActor, RenderPass renderPass, const Matrix4& toWorld, const Matrix4& fromWorld);
        virtual ~SceneNode();

        virtual const SceneNodeProperties* const vGetNodeProperties() const override;

        virtual void vSetTransform(const Matrix4* pToWorld, const Matrix4* pFromWorld = nullptr) override;

        virtual bool vOnUpdate(IScene* pScene, const unsigned long timeElapsed) override;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) override;
        virtual bool vRemoveChild(ActorID actorID) override;

        const SceneNodeList& vGetChildren() const override;

        virtual ISceneNode* vGetParent() const override;

        virtual void vSetPosition(const Vector3& position);
        // Local position.
        const Vector3 GetPosition() const;
        const Quaternion GetRotation() const;

        // World position (relative to parents).
        Vector3 GetWorldPosition() const;
        Vector3 GetDirection() const;

        void SetRadius(const float fRadius);

        const Matrix4& GetWorldTransform() const
        {
            //return m_WorldTransform;
            return m_Properties.m_ToWorld;
        }

        const Matrix4& GetRenderTransform() const
        {
            //return m_WorldTransform;
            return m_Properties.m_WorldTransform;
        }

    private:
        void Init(ActorID actorID, ActorWeakPointer pActor, RenderPass renderPass, const Matrix4* pToWorld, const Matrix4* pFromWorld);

    protected:
        SceneNodeList m_Children;
        SceneNode* m_pParent;
        SceneNodeProperties m_Properties;
    };


    class RootSceneNode : public SceneNode
    {
    public:
        RootSceneNode();
        ~RootSceneNode();

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) override;
        virtual bool vRemoveChild(ActorID actorID) override;
    };

}
