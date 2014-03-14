#pragma once

#include <Utilities/Math/MathStd.h>
#include <Utilities/Math/Conversion/BulletMathConversion.h>

namespace uge
{
    struct ActorMotionState : public btMotionState
    {
    public:
        ActorMotionState(const Matrix4& initialTransform);
        ActorMotionState(const Vector3& initialPosition, const Quaternion& initialRotation);

    public:
        // Bullet Interface.
        virtual void getWorldTransform(btTransform& worldTransform) const override;

        virtual void setWorldTransform(const btTransform& worldTransform) override;

    public:
        Matrix4 m_WorldToPositionTransform;
    };
}
