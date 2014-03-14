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