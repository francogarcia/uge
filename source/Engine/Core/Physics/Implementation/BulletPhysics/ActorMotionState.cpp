#include "GameEngineStd.h"

#include "ActorMotionState.h"

namespace uge
{
    ActorMotionState::ActorMotionState(const Matrix4& initialTransform)
        : m_WorldToPositionTransform(initialTransform)
    {

    }

    ActorMotionState::ActorMotionState(const Vector3& initialPosition, const Quaternion& initialRotation)
    {
        m_WorldToPositionTransform.MakeRotationMatrix(initialRotation);
        m_WorldToPositionTransform.SetPositionFromVector(initialPosition);
    }

    void ActorMotionState::getWorldTransform(btTransform& worldTransform) const
    {
        worldTransform = ToBulletMath(m_WorldToPositionTransform);
    }

    void ActorMotionState::setWorldTransform(const btTransform& worldTransform)
    {
        m_WorldToPositionTransform = ToMath(worldTransform);
    }
}
