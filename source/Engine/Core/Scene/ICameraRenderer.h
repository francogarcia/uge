/*
  * (c) Copyright 2014 Franco Eus�bio Garcia
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

#pragma once

#include "IScene.h"
#include "ISceneNode.h"

namespace uge
{
    class ICameraRenderer
    {
    public:
        ICameraRenderer();
        virtual ~ICameraRenderer();

        //virtual void vOnSetTarget(ISceneNodeSharedPointer pTargetNode) = 0;
        //virtual void vOnClearTarget() = 0;

        virtual bool vOnUpdate(ICameraNodeSharedPointer pCamera)  = 0;

        //virtual void vOnSetCameraOffset(const Vector4& cameraOffset) = 0;
    };
}
