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
