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
 */

#pragma once

#include "Vector.h"

namespace uge
{
    class Plane
    {
    public:
        Plane();
        // Point and distance.
        Plane(const float fX, const float fY, const float fZ, const float fDistance);
        // Point and distance.
        Plane(const Vector3& vector, const float fDistance);
        // Point and distance.
        // w is used as the distance from the origin.
        Plane(const Vector4& vector);
        // Three points.
        Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3);

        void Normalize();

        // True if the plane is facing the same side of the point.
        bool IsInside(const Vector3& point) const;
        bool IsInside(const Vector3& point, const float fRadius) const;

    private:
        Vector3 m_Normal;
        float m_fOriginDistance;
    };
}
