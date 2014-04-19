/*
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

#pragma once

#include "Plane.h"
#include "Vector.h"
#include "Matrix.h"

namespace uge
{
    class Frustum
    {
    public:
        enum Side
        {
            Left,
            Right,
            Bottom,
            Top,
            Near,
            Far,

            TotalSides
        };

        Frustum();
        ~Frustum();

        void Init(const float fFOV, const float fAspectRatio, const float fNearPlaneDistance, const float fFarPlaneDistance);
        virtual void vRender();

        bool IsInside(const Vector3& point) const;
        bool IsInside(const Vector3& point, const float fRadius) const;

        const Plane& GetPlaneSide(const Side side) const;

        void SetFOV(const float fFOV);
        float GetFOV() const;

        void SetAspectRatio(const float fAspectRatio);
        float GetAspectRatio() const;

        void SetNearPlaneDistance(const float fNearPlaneDistance);
        float GetNearPlaneDistance() const;

        void SetFarPlaneDistance(const float fFarPlaneDistance);
        float GetFarPlaneDistance() const;

        const Matrix4& GetProjectionMatrix() const;

    private:
        // In degrees.
        float m_fFOV;
        float m_fAspectRatio;
        float m_fNearPlaneDistance;
        float m_fFarPlaneDistance;

        Plane m_Planes[Side::TotalSides];
        Matrix4 m_FrustumMatrix;

        Matrix4 m_ProjectionMatrix;
    };
}
