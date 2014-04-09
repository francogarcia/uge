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

#include "YSECamera.h"

#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>

#include <Utilities/Math/Conversion/YSEMathConversion.h>

namespace uge
{
    YSECamera::YSECamera()
        : ICameraRenderer()
    {

    }

    YSECamera::~YSECamera()
    {

    }

    bool YSECamera::vOnUpdate(ICameraNodeSharedPointer pICameraNode)
    {
        UpdateTransform(pICameraNode);

        return true;
    }

    void YSECamera::Init(ICameraNodeSharedPointer pICameraNode)
    {
        UpdateTransform(pICameraNode);
    }

    void YSECamera::UpdateTransform(ICameraNodeSharedPointer pICameraNode)
    {
        std::shared_ptr<CameraNode> pCameraNode = std::dynamic_pointer_cast<CameraNode>(pICameraNode);

        const Vector3& position = pCameraNode->GetPosition();
        const Vector3& forwardVector = pCameraNode->GetDirection();
        const Vector3& upVector = Vector3::g_Up;

        YSE::Listener.pos(ToYSEMath(position));
        YSE::Listener.orn(ToYSEMath(forwardVector),
                          ToYSEMath(upVector));
        //YSE::Listener.vel();
    }
}
