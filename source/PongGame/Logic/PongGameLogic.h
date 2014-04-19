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

#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>

#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Engine/GameLogic/BaseGameLogic.h>

#include "Logic/PongGameStateFactory.h"

class PongGameLogic : public uge::BaseGameLogic
{
public:
    PongGameLogic()
    {

    }

    ~PongGameLogic()
    {

    }

    virtual uge::GameStateFactory* vCreateGameStateFactory() override
    {
        return LIB_NEW PongState::PongGameStateFactory;
    }

    virtual uge::IPhysics* vCreatePhysics() override
    {
        // GAME PHYSICS
#ifdef UGE_ENABLE_PHYSICS
        uge::IPhysics* pPhysics = LIB_NEW uge::BulletPhysics;
#else
        uge::IPhysics* pPhysics = LIB_NEW uge::NullPhysics;
#endif

        assert(pPhysics != nullptr);

        bool bSuccess = pPhysics->vInit();
        pPhysics->vSetGravity(uge::Vector3(0.0f, -0.5f, 0.0f));

        return pPhysics;
    }

    void vRegisterGameDelegates() override
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &PongGameLogic::ActorCreatedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);
    }

    void vUnregisterGameDelegates() override
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &PongGameLogic::ActorCreatedDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);
    }

protected:
    void ActorCreatedDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_New_Actor> pData = std::static_pointer_cast<uge::EvtData_New_Actor>(pEventData);

        //std::cout << "Actor " << pData->GetActorID() << " was created!" << std::endl;
        uge::ActorSharedPointer pActor = vGetActor(pData->GetActorID()).lock();

        std::cout << pActor->GetActorType() << " was created!" << std::endl;
    }

private:

};
