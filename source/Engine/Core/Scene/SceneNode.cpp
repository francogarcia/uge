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

#include "GameEngineStd.h"

#include "SceneNode.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include "IScene.h"

namespace uge
{
    SceneNode::SceneNode(ActorID actorID, ActorWeakPointer pActor, RenderPass renderPass, const Matrix4* pToWorld, const Matrix4* pFromWorld)
        : m_pParent(nullptr)
    {
        Init(actorID, pActor, renderPass, pToWorld, pFromWorld);
    }

    SceneNode::SceneNode(ActorID actorID, ActorWeakPointer pActor, RenderPass renderPass, const Matrix4& toWorld, const Matrix4& fromWorld)
        : m_pParent(nullptr)
    {
        Init(actorID, pActor, renderPass, &toWorld, &fromWorld);
    }

    SceneNode::~SceneNode()
    {
        m_Children.clear();
        m_pParent = nullptr;
    }

    const SceneNodeProperties* const SceneNode::vGetNodeProperties() const
    {
        return &m_Properties;
    }

    void SceneNode::vSetTransform(const Matrix4* pToWorld, const Matrix4* pFromWorld)
    {
        m_Properties.m_ToWorld = *pToWorld;
        if (pFromWorld == nullptr)
        {
            m_Properties.m_FromWorld = m_Properties.m_ToWorld.GetInversed();
        }
        else
        {
            m_Properties.m_FromWorld = *pFromWorld;
        }
    }

    bool SceneNode::vOnUpdate(IScene* pScene, const unsigned long timeElapsed)
    {
        // Update the node's position.
        ActorID actorID = m_Properties.GetActorID();
        if (actorID != Actor::NULL_ACTOR_ID)
        {
            ActorSharedPointer pActor = m_Properties.GetActor().lock();
            assert(pActor != nullptr && "Actor is no longer in the scene!");

            // Get transformation component, set new position, scale and rotation.
            Component::TransformableComponentSharedPointer pActorTransformComponent =
                pActor->GetComponent<Component::TransformableComponent>(Component::TransformableComponent::g_ComponentName).lock();
            vSetTransform(&pActorTransformComponent->GetTransform());
        }

        // Calculate world position from local position.
        pScene->vPushSetMatrix(m_Properties.m_ToWorld);

        // Update transformable component here.
        m_Properties.m_WorldTransform = pScene->vGetTopMatrix();

        // Update the children nodes.
        for (auto& childSceneNode : m_Children)
        {
            childSceneNode->vOnUpdate(pScene, timeElapsed);
        }

        pScene->vPopMatrix();

        return true;
    }

    bool SceneNode::vAddChild(ISceneNodeSharedPointer pChildNode)
    {
        assert(pChildNode != nullptr);

        m_Children.push_back(pChildNode);

        SceneNodeSharedPointer pSharedChildNode = std::static_pointer_cast<SceneNode>(pChildNode);
        pSharedChildNode->m_pParent = this;

        Vector3 childPosition = pSharedChildNode->vGetNodeProperties()->GetToWorld().GetPositionVector();
        float fRadius = childPosition.length() + pSharedChildNode->vGetNodeProperties()->GetRadius();
        if (fRadius > m_Properties.m_fRadius)
        {
            m_Properties.m_fRadius = fRadius;
        }

        return true;
    }

    bool SceneNode::vRemoveChild(ActorID actorID)
    {
        SceneNodeList::iterator end = m_Children.end();
        for (SceneNodeList::iterator childSceneNodeIterator = m_Children.begin();
             childSceneNodeIterator != end; ++childSceneNodeIterator)
        {
            const SceneNodeProperties* pProperties = (*childSceneNodeIterator)->vGetNodeProperties();
            ActorID nodeActorID = pProperties->GetActorID();
            if (nodeActorID != Actor::NULL_ACTOR_ID && actorID == nodeActorID)
            {
                SceneNodeSharedPointer pChildSceneNode = std::dynamic_pointer_cast<SceneNode>(*childSceneNodeIterator);
                pChildSceneNode->m_pParent = nullptr;

                childSceneNodeIterator = m_Children.erase(childSceneNodeIterator);

                return true;
            }
        }

        return false;
    }

    const SceneNodeList& SceneNode::vGetChildren() const
    {
        return m_Children;
    }

    ISceneNode* SceneNode::vGetParent() const
    {
        return m_pParent;
    }

    void SceneNode::vSetPosition(const Vector3& position)
    {
        m_Properties.m_ToWorld.SetPositionFromVector(position);
    }

    const Vector3 SceneNode::GetPosition() const
    {
        return m_Properties.m_ToWorld.GetPositionVector();
    }

    const Quaternion SceneNode::GetRotation() const
    {
        return m_Properties.m_ToWorld.GetRotationQuaternion();
    }

    Vector3 SceneNode::GetWorldPosition() const
    {
        Vector3 worldPosition = GetPosition();
        if (m_pParent != nullptr)
        {
            worldPosition += m_pParent->GetWorldPosition();
        }

        return worldPosition;
    }

    Vector3 SceneNode::GetDirection() const
    {
        return m_Properties.m_ToWorld.GetDirectionVector();
    }

    void SceneNode::SetRadius(const float fRadius)
    {
        m_Properties.m_fRadius = fRadius;
    }

    void SceneNode::Init(ActorID actorID, ActorWeakPointer pActor, RenderPass renderPass, const Matrix4* pToWorld, const Matrix4* pFromWorld)
    {
        m_Properties.m_ActorID = actorID;

        if (actorID != Actor::NULL_ACTOR_ID)
        {
            ActorSharedPointer pSharedActor = pActor.lock();

            m_Properties.m_pActor = pActor;
            m_Properties.m_Name = pSharedActor->GetActorType();
            m_Properties.m_RenderPass = renderPass;
        }
        else
        {
            // The node has a special meaning.
            m_Properties.m_RenderPass = renderPass;
            switch (renderPass)
            {
                case RenderPass::Actor:
                {
                    m_Properties.m_Name = "ActorNodeGroup";

                    break;
                }

                case RenderPass::Static:
                {
                    m_Properties.m_Name = "StaticNodeGroup";

                    break;
                }

                case RenderPass::Sky:
                {
                    m_Properties.m_Name = "SkyNodeGroup";

                    break;
                }

                case RenderPass::NotRendered:
                {
                    m_Properties.m_Name = "NotRenderedNodeGroup";

                    break;
                }

                case RenderPass::Root:
                {
                    m_Properties.m_Name = "RootSceneNode";

                    break;
                }

                case RenderPass::Camera:
                {
                    m_Properties.m_Name = "CameraSceneNode";

                    break;
                }
            }
        }

        vSetTransform(pToWorld, pFromWorld);
        // TODO: get this from physics component.
        SetRadius(0.0f);
    }

    // Root Node.
    RootSceneNode::RootSceneNode()
        : SceneNode(Actor::NULL_ACTOR_ID, ActorWeakPointer(),
                    RenderPass::Root, &Matrix4::g_Identity)
    {
        m_Children.reserve(static_cast<size_t>(RenderPass::RenderPassCount));

        // Children are indexed by the render pass value.

        ISceneNodeSharedPointer pStaticRenderGroup(LIB_NEW SceneNode(Actor::NULL_ACTOR_ID,
                                                                     ActorWeakPointer(), RenderPass::Static, &Matrix4::g_Identity));
        m_Children.push_back(pStaticRenderGroup);

        ISceneNodeSharedPointer pActorRenderGroup(LIB_NEW SceneNode(Actor::NULL_ACTOR_ID,
                                                                    ActorWeakPointer(), RenderPass::Actor, &Matrix4::g_Identity));
        m_Children.push_back(pActorRenderGroup);

        ISceneNodeSharedPointer pSkyRenderGroup(LIB_NEW SceneNode(Actor::NULL_ACTOR_ID,
                                                                  ActorWeakPointer(), RenderPass::Sky, &Matrix4::g_Identity));
        m_Children.push_back(pSkyRenderGroup);

        ISceneNodeSharedPointer pInvisibleRenderGroup(LIB_NEW SceneNode(Actor::NULL_ACTOR_ID,
                                                                        ActorWeakPointer(), RenderPass::NotRendered, &Matrix4::g_Identity));
        m_Children.push_back(pInvisibleRenderGroup);
    }

    RootSceneNode::~RootSceneNode()
    {

    }

    bool RootSceneNode::vAddChild(ISceneNodeSharedPointer pChildNode)
    {
        RenderPass renderPass = pChildNode->vGetNodeProperties()->GetRenderPass();
        size_t renderPassValue = static_cast<size_t>(renderPass);
        if (renderPassValue >= m_Children.size() || !m_Children[renderPassValue])
        {
            assert(0 && "Invalid render pass!");

            return false;
        }

        return m_Children[renderPassValue]->vAddChild(pChildNode);
    }

    bool RootSceneNode::vRemoveChild(ActorID actorID)
    {
        bool bChildRemoved = false;

        size_t firstRenderPassValue = static_cast<size_t>(RenderPass::RenderPass0);
        size_t totalRenderPassValue = static_cast<size_t>(RenderPass::RenderPassCount);
        for (size_t renderPassValue = firstRenderPassValue; renderPassValue < totalRenderPassValue; ++renderPassValue)
        {
            if (m_Children[renderPassValue]->vRemoveChild(actorID))
            {
                bChildRemoved = true;
            }
        }

        return bChildRemoved;
    }
}
