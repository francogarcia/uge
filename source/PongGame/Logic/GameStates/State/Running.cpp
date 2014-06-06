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
* Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA  02110-1301, USA.
*/

#include "PongGameStd.h"

#include "Running.h"

#include <Utilities/Debug/Logger.h>

namespace pg
{

    namespace GameState
    {

        Running::Running()
        {

        }

        Running::~Running()
        {

        }

        bool Running::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[Running] Game is running!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            RegisterEvents();

            ConfigureGamePhysics();

            if (!CreateGameActors())
            {
                return false;
            }

            InitGameData();

            return true;
        }

        bool Running::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            // Overrides the presentation data using the chosen profile.
            LoadProfile(xmlResourceFilename);

            // Specialize all the actors currently in the game according to the
            // profile's definition.
            pg::GameLogic* pGameLogic = dynamic_cast<pg::GameLogic*>(m_pGameLogic);
            for (const auto& actorIt : pGameLogic->m_Actors)
            {
                uge::ActorID actorID = actorIt.first;
                uge::ActorSharedPointer pActor = actorIt.second;

                TailorActorToProfile(pActor);

                // Add the actor the game scene.
                pGameLogic->vCreateAndAddSceneNode(pActor);
            }

            // Lets the game view attach the player's controlled actor.
            std::shared_ptr<uge::EvtData_Set_Controlled_Actor> pEvent(LIB_NEW uge::EvtData_Set_Controlled_Actor(m_pPlayer->GetActorID()));
            uge::IEventManager::Get()->vQueueEvent(pEvent);

            return true;
        }

        bool Running::vDestroy()
        {
            UnregisterEvents();

            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool Running::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::Running::vOnUpdate(timeElapsed);

            if (!m_bPlaying)
            {
                StartGame();
            }

            return bSuccess;
        }

        bool Running::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        bool Running::ConfigureGamePhysics()
        {
            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vSetGravity(uge::Vector3(0.0f, 0.0f, 0.0f));

            return true;
        }

        bool Running::CreateGameActors()
        {
            m_pPlayer = CreateAndRegisterActor("data/game/actors/paddle-player1.xml");
            if (m_pPlayer == uge::ActorSharedPointer())
            {
                return false;
            }

            m_pOpponent = CreateAndRegisterActor("data/game/actors/paddle-player2.xml");
            if (m_pOpponent == uge::ActorSharedPointer())
            {
                return false;
            }

            m_pBall = CreateAndRegisterActor("data/game/actors/ball.xml");
            if (m_pBall == uge::ActorSharedPointer())
            {
                return false;
            }

            return true;
        }

        uge::ActorSharedPointer Running::CreateAndRegisterActor(const std::string& actorResourceFile,
                                                                uge::XMLElement* pActorOverride)
        {
            // Create an actor.
            uge::ActorSharedPointer pActor = CreateActor(actorResourceFile,
                                                         pActorOverride);
            if (pActor == uge::ActorSharedPointer())
            {
                return uge::ActorSharedPointer();
            }

            // XXX: refactor here to RegisterActor()
            // Add the actor to the physics simulation.
            AddActorToPhysics(pActor);

            return pActor;
        }

        uge::ActorSharedPointer Running::CreateActor(const std::string& actorResourceFile,
                                                     uge::XMLElement* pActorOverride)
        {
            return m_pGameLogic->vCreateActor(actorResourceFile, pActorOverride);
        }

        void Running::AddActorToPhysics(uge::ActorSharedPointer pActor)
        {
            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vAddActor(pActor);
        }

        void Running::RemoveActorFromPhysics(uge::ActorID actorID)
        {
            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vRemoveActor(actorID);
        }

        void Running::LoadProfile(const std::string& xmlResourceFilename)
        {
            uge::XMLFile entityListFile;
            entityListFile.OpenFile(xmlResourceFilename, uge::File::FileMode::FileReadOnly);

            // Register each of the actor's specialization resource.
            uge::XMLElement entityListRoot = entityListFile.GetRootElement();
            for (uge::XMLElement entityElement = entityListRoot.GetFirstChildElement();
                 entityElement.IsGood();
                 entityElement = entityElement.GetNextSiblingElement())
            {
                std::string entityName;
                entityElement.GetAttribute("name", &entityName);

                std::string entityResourceFileName;
                entityElement.GetAttribute("resource", &entityResourceFileName);

                m_ActorSpecializationResource[entityName] = entityResourceFileName;
            }

            entityListFile.CloseFile();
        }

        void Running::TailorActorToProfile(uge::ActorSharedPointer pActor)
        {
            uge::ActorID actorID = pActor->GetActorID();

            std::string entityResourceFileName = m_ActorSpecializationResource[pActor->GetActorType()];
            if (entityResourceFileName == "")
            {
                LOG_WARNING("Actor type " + pActor->GetActorType() + " is missing a specialization.");

                return;
            }

            uge::XMLFile entityResource;
            entityResource.OpenFile(entityResourceFileName, uge::File::FileMode::FileReadOnly);

            m_pGameLogic->vModifyActor(actorID, &entityResource.GetRootElement());
            pActor->PostInit();

            // Re-add the actor to the physics simulation (its transform or shape
            // might have changed).
            RemoveActorFromPhysics(actorID);
            AddActorToPhysics(pActor);

            entityResource.CloseFile();
        }

        void Running::RegisterEvents()
        {
            // Creating and registering the event handlers.
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionStarted);
            uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionEnded);
            uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysSeparation::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::OnMoveActor);
            uge::IEventManager::Get()->vAddListener(functionDelegate, pg::MoveActor::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::OnStopActor);
            uge::IEventManager::Get()->vAddListener(functionDelegate, pg::StopActor::sk_EventType);
        }

        void Running::UnregisterEvents()
        {
            // Removing the delegates.
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionStarted);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionEnded);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysSeparation::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::OnMoveActor);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, pg::MoveActor::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::OnStopActor);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, pg::StopActor::sk_EventType);
        }

        void Running::CollisionStarted(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<uge::EvtData_PhysCollision> pData = std::static_pointer_cast<uge::EvtData_PhysCollision>(pEventData);

            printf("Actors %u and %u collided!\n", pData->GetActorA(), pData->GetActorB());

            uge::ActorID actorA = pData->GetActorA();
            uge::ActorID actorB = pData->GetActorB();

            if (m_pGameLogic->vGetActor(actorA).expired() ||
                m_pGameLogic->vGetActor(actorB).expired())
            {
                // Projectile hit more than an enemy. Destroy only the first.
                return;
            }

            uge::ActorSharedPointer pActorA = m_pGameLogic->vGetActor(actorA).lock();
            uge::ActorSharedPointer pActorB = m_pGameLogic->vGetActor(actorB).lock();

            const std::string actorTypeA = pActorA->GetActorType();
            const std::string actorTypeB = pActorB->GetActorType();
        }

        void Running::CollisionEnded(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<uge::EvtData_PhysSeparation> pData = std::static_pointer_cast<uge::EvtData_PhysSeparation>(pEventData);

            printf("Actors %u and %u stopped colliding!\n", pData->GetActorA(), pData->GetActorB());
        }

        void Running::OnMoveActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<pg::MoveActor> pData = std::static_pointer_cast<pg::MoveActor>(pEventData);

            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();

            MoveActor::Direction direction = pData->GetDirection();
            const float kfMagnitude = 100.0f;
            if (direction == MoveActor::Direction::Left)
            {
                pPhysics->vApplyForce(pData->GetActorID(), uge::Vector3(0.0f, 0.0f, -1.0f), kfMagnitude);
            }
            else
            {
                pPhysics->vApplyForce(pData->GetActorID(), uge::Vector3(0.0f, 0.0f, 1.0f), kfMagnitude);
            }

            uge::ActorSharedPointer pActor = m_pGameLogic->vGetActor(pData->GetActorID()).lock();
            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();

            uge::Vector3 velocity = pActorPhysicsComponent->vGetVelocity();
            float fCurrentVelocityMagnitude = velocity.Length();
            if (fCurrentVelocityMagnitude != 0.0f)
            {
                float fMaxVelocityMagnitude = pActorPhysicsComponent->vGetMaxVelocity();
                velocity *= (fMaxVelocityMagnitude / fCurrentVelocityMagnitude);

                pActorPhysicsComponent->vSetVelocity(velocity);
            }
        }

        void Running::OnStopActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<pg::StopActor> pData = std::static_pointer_cast<pg::StopActor>(pEventData);

            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vStopActor(pData->GetActorID());
        }

        uge::Vector3 Running::GetPosition(uge::ActorID actorID)
        {
            return GetPosition(m_pGameLogic->vGetActor(actorID).lock());
        }

        void Running::SetPosition(uge::ActorID actorID, const uge::Vector3& newPosition)
        {
            SetPosition(m_pGameLogic->vGetActor(actorID).lock(), newPosition);
        }

        void Running::ApplyForce(uge::ActorID actorID, const uge::Vector3& direction, float fNewtons)
        {
            return ApplyForce(m_pGameLogic->vGetActor(actorID).lock(), direction, fNewtons);
        }

        void Running::ApplyImpulse(uge::ActorID actorID, const uge::Vector3& direction, float fNewtons)
        {
            return ApplyImpulse(m_pGameLogic->vGetActor(actorID).lock(), direction, fNewtons);
        }

        void Running::StopActor(uge::ActorID actorID)
        {
            StopActor(m_pGameLogic->vGetActor(actorID).lock());
        }

        void Running::SetMaxVelocity(uge::ActorID actorID)
        {
            SetMaxVelocity(m_pGameLogic->vGetActor(actorID).lock());
        }

        uge::Vector3 Running::GetPosition(uge::ActorSharedPointer pActor)
        {
            uge::Component::TransformableComponentSharedPointer pActorTransformComponent =
                pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();

            return pActorTransformComponent->GetPosition();
        }

        void Running::SetPosition(uge::ActorSharedPointer pActor, const uge::Vector3& newPosition)
        {
            uge::Component::TransformableComponentSharedPointer pActorTransformComponent =
                pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            pActorTransformComponent->SetPosition(uge::Vector3(0.0f, 0.0f, 0.0f));

            m_pGameLogic->vMoveActor(pActor->GetActorID(), pActorTransformComponent->GetTransform());
        }

        void Running::ApplyForce(uge::ActorSharedPointer pActor, const uge::Vector3& direction, float fNewtons)
        {
            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();
            pActorPhysicsComponent->vApplyForce(direction, fNewtons);
        }

        void Running::ApplyImpulse(uge::ActorSharedPointer pActor, const uge::Vector3& direction, float fNewtons)
        {
            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();
            pActorPhysicsComponent->vApplyTorque(direction, fNewtons);
        }

        void Running::StopActor(uge::ActorSharedPointer pActor)
        {
            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();
            pActorPhysicsComponent->vStop();
        }

        void Running::SetMaxVelocity(uge::ActorSharedPointer pActor)
        {
            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();

            float fMaxVelocityMagnitude = pActorPhysicsComponent->vGetMaxVelocity();
            uge::Vector3 velocity = pActorPhysicsComponent->vGetVelocity();
            float fCurrentVelocityMagnitude = velocity.Length();

            velocity *= (fMaxVelocityMagnitude / fCurrentVelocityMagnitude);

            pActorPhysicsComponent->vSetVelocity(velocity);
        }

        void Running::InitGameData()
        {
            m_bPlaying = false;
        }

        void Running::StartGame()
        {
            uge::Vector3 initialDirection(1.0f, 0.0f, 0.0f);
            if (std::rand() % 2 == 1)
            {
                initialDirection.x = -1.0f;
            }

            StartPointMatch(initialDirection);
        }

        void Running::StartPointMatch(const uge::Vector3& initialDirection)
        {
            SetPosition(m_pBall, uge::Vector3(0.0f, 0.0f, 0.0f));
            ApplyForce(m_pBall, initialDirection, 400.0f);

            m_bPlaying = true;
        }

    }

}
