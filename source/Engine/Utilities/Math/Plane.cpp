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

#include "Plane.h"

namespace uge
{

    Plane::Plane()
        : m_Normal(0.0f, 0.0f, 0.0f), m_fOriginDistance(0.0f)
    {

    }

    Plane::Plane(const float fX, const float fY, const float fZ, const float fDistance)
        : m_Normal(fX, fY, fZ), m_fOriginDistance(fDistance)
    {
        
    }

    Plane::Plane(const Vector3& vector, const float fDistance)
        : m_Normal(vector.x, vector.y, vector.z), m_fOriginDistance(fDistance)
    {

    }

    Plane::Plane(const Vector4& vector)
        : m_Normal(vector.x, vector.y, vector.z), m_fOriginDistance(vector.w)
    {

    }

    Plane::Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3)
        : m_Normal(0.0f, 0.0f, 0.0f), m_fOriginDistance(0.0f)
    {
        Vector3 direction1(point1 - point2);
        Vector3 direction2(point3 - point2);

        m_Normal = direction1.CrossProduct(direction2);
        m_Normal.Normalize();

        m_fOriginDistance = m_Normal.DotProduct(direction2);
    }

    void Plane::Normalize()
    {
        float fInvLength = 1.0f / m_Normal.Length();

        m_Normal *= fInvLength;
        m_fOriginDistance *= fInvLength;
    }

    bool Plane::IsInside(const Vector3& point) const
    {
        float fDistance = m_fOriginDistance + m_Normal.DotProduct(point);

        return (fDistance >= 0.0f);
    }

    bool Plane::IsInside(const Vector3& point, const float fRadius) const
    {
        float fDistance = m_fOriginDistance + m_Normal.DotProduct(point);

        return (fDistance >= (-fRadius));
    }

}
