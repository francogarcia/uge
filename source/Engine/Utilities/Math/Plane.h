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
