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
