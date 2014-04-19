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
