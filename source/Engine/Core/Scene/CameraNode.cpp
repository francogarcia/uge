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

#include "GameEngineStd.h"

#include "CameraNode.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/IRenderableComponent.h>

#include "ISceneRenderer.h"
#include "Scene.h"

namespace uge
{

    CameraNode::CameraNode(const Matrix4& transform, const Frustum& frustum)
        : SceneNode(Actor::NULL_ACTOR_ID, ActorWeakPointer(), RenderPass::Camera, &transform),
          m_Frustum(frustum),
          m_bIsActive(false), m_bIsDebugCamera(false),
          m_pTarget(SceneNodeSharedPointer()),
          m_CameraTargetOffsetVector(0.0f, 1.0f, -10.0f, 0.0f),
          m_CameraOrientation(0.0f, 0.0f, 0.0f, 1.0f)
    {

    }

    CameraNode::~CameraNode()
    {

    }

    void CameraNode::vInit(IScene* pScene)
    {
        m_ProjectionMatrix = m_Frustum.GetProjectionMatrix();
        m_ViewMatrix = m_ProjectionMatrix;
    }

    const Frustum& CameraNode::vGetFrustum() const
    {
        return m_Frustum;
    }

    void CameraNode::vSetTarget(ISceneNodeSharedPointer pTargetNode)
    {
        m_pTarget = std::dynamic_pointer_cast<SceneNode>(pTargetNode);
    }

    ISceneNodeSharedPointer CameraNode::vGetTarget() const
    {
        return std::dynamic_pointer_cast<ISceneNode>(m_pTarget);
    }

    void CameraNode::vClearTarget()
    {
        m_pTarget.reset();
    }

    Matrix4 CameraNode::vGetWorldViewProjection(IScene* pScene) const
    {
        Matrix4 worldTransform = pScene->vGetTopMatrix();
        Matrix4 viewMatrix = vGetNodeProperties()->GetFromWorld();

        Matrix4 worldViewMatrix = worldTransform * viewMatrix;
        Matrix4 worldProjectMatrix = worldViewMatrix * m_ProjectionMatrix;

        return worldProjectMatrix;
    }

    bool CameraNode::vSetViewMatrix()
    {
        if (m_pTarget)
        {
            //Matrix4 worldTransform = m_pTarget->vGetNodeProperties()->GetToWorld();
            //Vector4 at = m_CameraTargetOffsetVector;
            //Vector4 atWorldTransform = worldTransform.XForm(at);

            //Vector3 newPosition = worldTransform.GetPositionVector() + Vector3(atWorldTransform);
            //worldTransform.SetPositionFromVector(newPosition);
            //vSetTransform(&worldTransform);

            Matrix4 worldTransform = m_pTarget->vGetNodeProperties()->GetToWorld();
            Matrix4 at;
            at.MakeTranslationMatrix(m_CameraTargetOffsetVector);
            at.Rotate(m_CameraOrientation);

            Matrix4 atWorldTransform =  worldTransform * at;
            vSetTransform(&atWorldTransform);
        }

        m_ViewMatrix = vGetNodeProperties()->GetFromWorld();

        // TODO: Send event to allow scene renderers to update their cameras.
        // The view matrix will be sent.

        return true;
    }

    const Matrix4& CameraNode::vGetProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    const Matrix4& CameraNode::vGetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    void CameraNode::vSetCameraOffset(const Vector4& cameraOffset)
    {
        m_CameraTargetOffsetVector = cameraOffset;
    }

    void CameraNode::vSetCameraOrientation(const float kYaw, const float kPitch, const float kRoll)
    {
        m_CameraOrientation.MakeQuaternion(Vector3(kPitch,
                                                   kYaw,
                                                   kRoll));
    }

    void CameraNode::vSetCameraOrientation(const Quaternion& rotation)
    {
        m_CameraOrientation = rotation;
    }

}
