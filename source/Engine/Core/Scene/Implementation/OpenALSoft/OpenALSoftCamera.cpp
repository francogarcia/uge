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

#include "OpenALSoftCamera.h"

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>

#include <cTinyOAL.h>
#include <../TinyOAL/openAL/al.h>
#include <../TinyOAL/openAL/loadoal.h>

namespace uge
{
    OpenALSoftCamera::OpenALSoftCamera()
        : ICameraRenderer()
    {

    }

    OpenALSoftCamera::~OpenALSoftCamera()
    {

    }

    bool OpenALSoftCamera::vOnUpdate(ICameraNodeSharedPointer pICameraNode)
    {
        UpdateTransform(pICameraNode);

        return true;
    }

    void OpenALSoftCamera::Init(ICameraNodeSharedPointer pICameraNode)
    {
        UpdateTransform(pICameraNode);
    }

    void OpenALSoftCamera::UpdateTransform(ICameraNodeSharedPointer pICameraNode)
    {
        std::shared_ptr<CameraNode> pCameraNode = std::dynamic_pointer_cast<CameraNode>(pICameraNode);

        const Vector3& position = pCameraNode->GetPosition();
        const Quaternion& orientation = pCameraNode->GetRotation();
        const Vector3& forwardVector = pCameraNode->GetDirection();
        //const Vector3& upVector = Vector3::g_Up;
        const Vector3& upVector = Vector3::g_Up;

        //// Listener at position, facing the forward vector, at up vector meters.
        //alListener3f(AL_POSITION, position.x, position.y, position.z);
        //if (alGetError() != AL_NO_ERROR)
        //{
        //    assert(0 && "Error setting the listener position!");
        //}

        ////alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        //float fOrientation[6] =
        //{
        //    forwardVector.x, forwardVector.y, forwardVector.z,
        //    upVector.x, upVector.y, upVector.z
        //};
        //alListenerfv(AL_ORIENTATION, fOrientation);
        //if (alGetError() != AL_NO_ERROR)
        //{
        //    assert(0 && "Error setting the listener orientation!");
        //}

        //alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

        // Listener at position, facing the forward vector, at up vector meters.
        TinyOAL::cTinyOAL::Instance()->oalFuncs->alListener3f(AL_POSITION, position.x, position.y, position.z);

        float fOrientation[6] =
        {
            forwardVector.x, forwardVector.y, forwardVector.z,
            upVector.x, upVector.y, upVector.z
        };
        TinyOAL::cTinyOAL::Instance()->oalFuncs->alListenerfv(AL_ORIENTATION, fOrientation);
    }
}
