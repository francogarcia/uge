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

#include <Utilities/Math/Frustum.h>
#include <Utilities/Math/Matrix.h>
#include <Utilities/Math/Vector.h>

#include "IScene.h"
#include "SceneNode.h"

namespace uge
{
    class CameraNode;
    typedef std::shared_ptr<CameraNode> CameraNodeSharedPointer;

    class CameraNode : public SceneNode, public ICameraNode
    {
    public:
        CameraNode(const Matrix4& transform, const Frustum& frustum);
        virtual ~CameraNode();

        virtual void vInit(IScene* pScene);

        virtual const Frustum& vGetFrustum() const override;

        // This method sets the camera's future target.
        // However, this change does not occur immediately.
        // To change the view transform, call vSetViewMatrix() afterwards.
        virtual void vSetTarget(ISceneNodeSharedPointer pTargetNode) override;
        virtual ISceneNodeSharedPointer vGetTarget() const override;
        // This method clear the camera's future target.
        // However, this change does not occur immediately.
        // To change the view transform, call vSetViewMatrix() afterwards.
        virtual void vClearTarget() override;

        virtual Matrix4 vGetWorldViewProjection(IScene* pScene) const override;
        // This method updates the view transforms and send an event to allow all renderers to update themselves.
        virtual bool vSetViewMatrix() override;

        virtual const Matrix4& vGetProjectionMatrix() const override;
        virtual const Matrix4& vGetViewMatrix() const override;

        // These methods are used together with the target.
        // The change does not occur immediately.
        // To change the view transform, call vSetViewMatrix() afterwards.
        virtual void vSetCameraOffset(const Vector4& cameraOffset) override;
        virtual void vSetCameraOrientation(const float kYaw, const float kPitch, const float kRoll) override;
        virtual void vSetCameraOrientation(const Quaternion& rotation) override;

    protected:
        Frustum m_Frustum;
        Matrix4 m_ProjectionMatrix;
        Matrix4 m_ViewMatrix;

        bool m_bIsActive;
        bool m_bIsDebugCamera;

        SceneNodeSharedPointer m_pTarget;
        Vector4 m_CameraTargetOffsetVector;
        Quaternion m_CameraOrientation;
    };
}
