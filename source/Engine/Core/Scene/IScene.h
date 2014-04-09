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

#pragma once

#include "ISceneNode.h"
#include "ISceneRenderer.h"

namespace uge
{
    class IScene
    {
    public:
        IScene();
        virtual ~IScene();

        virtual bool vOnUpdate(const unsigned long timeElapsed) = 0;

        virtual ISceneNodeSharedPointer vGetRootSceneNode() const = 0;

        virtual bool vAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;
        virtual ISceneNodeSharedPointer vFindActor(ActorID actorID) = 0;
        virtual bool vRemoveChild(ActorID actorID) = 0;

        virtual void vPushSetMatrix(const Matrix4& toWorld) = 0;
        virtual void vPopMatrix() = 0;
        virtual const Matrix4& vGetTopMatrix() const = 0;
    };

}
