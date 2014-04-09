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

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Physics/IPhysics.h>

#include <Utilities/Math/Matrix.h>

#include "GameState/IGameState.h"

namespace uge
{

    class IGameLogic
    {
    public:
        IGameLogic();

        virtual ~IGameLogic();

        virtual bool vInit() = 0;
        virtual bool vDestroy() = 0;

        virtual bool vLoadGame(const std::string& levelResource) = 0;

        // Time in nanoseconds.
        virtual void vOnUpdate(unsigned long currentTime, unsigned long timeElapsed) = 0;
        
        virtual void vChangeGameState(const std::string& gameStateName) = 0;
        virtual IGameState* vGetGameState() const = 0;

        virtual ActorSharedPointer vCreateActor(const std::string& actorResource, XMLElement* pActorSpecificData = nullptr, const Matrix4* pInitialTransform = nullptr) = 0;
        virtual ActorWeakPointer vGetActor(const ActorID actorID) = 0;
        virtual void vDestroyActor(const ActorID actorID) = 0;

        virtual void vMoveActor(const ActorID actorID, const Matrix4& transform) = 0;
        virtual void vModifyActor(const ActorID actorID, XMLElement* pActorSpecificData) = 0;

        virtual IPhysicsSharedPointer vGetPhysics() = 0;
    };

}
