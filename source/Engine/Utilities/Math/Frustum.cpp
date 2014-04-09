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

#include "Frustum.h"

#include "MathUtil.h"

namespace uge
{
    Frustum::Frustum()
        : m_fFOV(uge::PI / 4.0f), m_fAspectRatio(1.0f),
          m_fNearPlaneDistance(1.0f), m_fFarPlaneDistance(1000.0f)
    {

    }

    Frustum::~Frustum()
    {

    }

    void Frustum::Init(const float fFOV, const float fAspectRatio, const float fNearPlaneDistance, const float fFarPlaneDistance)
    {
        m_fFOV = fFOV;
        m_fAspectRatio = fAspectRatio;
        m_fNearPlaneDistance = fNearPlaneDistance;
        m_fFarPlaneDistance = fFarPlaneDistance;

        float fTanHalfFOV = uge::Tg(m_fFOV / 2.0f);
        //Vector3 nearRight = m_fNearPlaneDistance * fTanHalfFOV * m_fAspectRatio * Vector3::g_Right;
        //Vector3 farRight = m_fFarPlaneDistance * fTanHalfFOV * m_fAspectRatio * Vector3::g_Right;
        //Vector3 nearUp = m_fNearPlaneDistance * fTanHalfFOV * Vector3::g_Up;
        //Vector3 farUp = m_fFarPlaneDistance * fTanHalfFOV * Vector3::g_Up;

        // Near right.
        float fLeft = m_fNearPlaneDistance * fTanHalfFOV * m_fAspectRatio * Vector3::g_Right.x;
        // Far right.
        float fRight = m_fFarPlaneDistance * fTanHalfFOV * m_fAspectRatio * Vector3::g_Right.x;
        // Near up.
        float fBottom = m_fNearPlaneDistance * fTanHalfFOV * Vector3::g_Up.y;
        // Far up.
        float fTop = m_fFarPlaneDistance * fTanHalfFOV * Vector3::g_Up.y;

        m_FrustumMatrix = Matrix4(glm::frustum(fLeft, fRight, fBottom, fTop, fNearPlaneDistance, fFarPlaneDistance));
        m_Planes[Side::Left] = Plane(m_FrustumMatrix.GetRowVector(3) + m_FrustumMatrix.GetRowVector(0));
        m_Planes[Side::Right] = Plane(m_FrustumMatrix.GetRowVector(3) - m_FrustumMatrix.GetRowVector(0));
        m_Planes[Side::Top] = Plane(m_FrustumMatrix.GetRowVector(3) - m_FrustumMatrix.GetRowVector(1));
        m_Planes[Side::Bottom] = Plane(m_FrustumMatrix.GetRowVector(3) + m_FrustumMatrix.GetRowVector(1));
        m_Planes[Side::Near] = Plane(m_FrustumMatrix.GetRowVector(3) + m_FrustumMatrix.GetRowVector(2));
        m_Planes[Side::Far] = Plane(m_FrustumMatrix.GetRowVector(3) - m_FrustumMatrix.GetRowVector(2));

        for (unsigned int planeIndex = 0; planeIndex < Side::TotalSides; ++planeIndex)
        {
            m_Planes[planeIndex].Normalize();
        }

        m_ProjectionMatrix = Matrix4(glm::perspective(m_fFOV, m_fAspectRatio, m_fNearPlaneDistance, m_fFarPlaneDistance));
    }

    void Frustum::vRender()
    {
        
    }

    bool Frustum::IsInside(const Vector3& point) const
    {
        for (unsigned int planeIndex = 0; planeIndex < Side::TotalSides; ++planeIndex)
        {
            if (!m_Planes[planeIndex].IsInside(point))
            {
                return false;
            }
        }

        return true;
    }

    bool Frustum::IsInside(const Vector3& point, const float fRadius) const
    {
        for (unsigned int planeIndex = 0; planeIndex < Side::TotalSides; ++planeIndex)
        {
            if (!m_Planes[planeIndex].IsInside(point, fRadius))
            {
                return false;
            }
        }

        return true;
    }

    const Plane& Frustum::GetPlaneSide(const Side side) const
    {
        return m_Planes[side];
    }

    void Frustum::SetFOV(const float fFOV)
    {
        assert(fFOV > 0.0f && "Invalid value for the field of view!");

        Init(fFOV, m_fAspectRatio, m_fNearPlaneDistance, m_fFarPlaneDistance);
    }

    float Frustum::GetFOV() const
    {
        return m_fFOV;
    }

    void Frustum::SetAspectRatio(const float fAspectRatio)
    {
        assert(fAspectRatio > 0.0f && "Invalid value for the aspect ratio!");

        Init(m_fFOV, fAspectRatio, m_fNearPlaneDistance, m_fFarPlaneDistance);
    }

    float Frustum::GetAspectRatio() const
    {
        return m_fAspectRatio;
    }

    void Frustum::SetNearPlaneDistance(const float fNearPlaneDistance)
    {
        assert(fNearPlaneDistance > 0.0f && "Invalid value for the near plane distance!");

        Init(m_fFOV, m_fAspectRatio, fNearPlaneDistance, m_fFarPlaneDistance);
    }

    float Frustum::GetNearPlaneDistance() const
    {
        return m_fNearPlaneDistance;
    }

    void Frustum::SetFarPlaneDistance(const float fFarPlaneDistance)
    {
        assert(fFarPlaneDistance > 0.0f && "Invalid value for the far plane distance!");

        Init(m_fFOV, m_fAspectRatio, m_fNearPlaneDistance, fFarPlaneDistance);
    }

    float Frustum::GetFarPlaneDistance() const
    {
        return m_fFarPlaneDistance;
    }

    const Matrix4& Frustum::GetProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }
}
