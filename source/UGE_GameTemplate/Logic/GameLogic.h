#pragma once

#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>

#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Engine/GameLogic/BaseGameLogic.h>

#include "GameStateFactory.h"

namespace sg
{

class GameLogic : public uge::BaseGameLogic
{
public:
    GameLogic()
    {

    }

    ~GameLogic()
    {

    }

    virtual uge::GameStateFactory* vCreateGameStateFactory() override
    {
        return LIB_NEW sg::GameState::GameStateFactory;
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
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &sg::GameLogic::ActorCreatedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);
    }

    void vUnregisterGameDelegates() override
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &sg::GameLogic::ActorCreatedDelegate);
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

}
