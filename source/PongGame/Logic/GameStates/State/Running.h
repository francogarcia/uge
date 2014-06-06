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

#pragma once

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>
#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>

#include <Core/Events/IEventManager.h>
#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Engine/GameLogic/BaseGameLogic.h>
#include <Engine/GameLogic/GameState/BaseGameState.h>

#include "../../../Logic/Events/GameEvents.h"
#include "../../../Logic/GameLogic.h"

namespace pg
{

    namespace GameState
    {

        class Running : public uge::GameState::Running
        {
        public:
            Running();
            virtual ~Running();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

        private:
            bool ConfigureGamePhysics();

            bool CreateGameActors();
            uge::ActorSharedPointer CreateAndRegisterActor(const std::string& actorResourceFile, uge::XMLElement* pActorOverride = nullptr);
            uge::ActorSharedPointer CreateActor(const std::string& actorResourceFile, uge::XMLElement* pActorOverride = nullptr);

            void AddActorToPhysics(uge::ActorSharedPointer pActor);
            void RemoveActorFromPhysics(uge::ActorID actorID);

            void LoadProfile(const std::string& xmlResourceFilename);
            void TailorActorToProfile(uge::ActorSharedPointer pActor);

            void InitGameData();
            void StartGame();
            void StartPointMatch(const uge::Vector3& initialDirection);

            void RegisterEvents();
            void UnregisterEvents();

            void CollisionStarted(uge::IEventDataSharedPointer pEventData);
            void CollisionEnded(uge::IEventDataSharedPointer pEventData);

            void OnMoveActor(uge::IEventDataSharedPointer pEventData);
            void OnStopActor(uge::IEventDataSharedPointer pEventData);

            // Math and physics helpers.
            uge::Vector3 GetPosition(uge::ActorID actorID);
            void SetPosition(uge::ActorID actorID, const uge::Vector3& newPosition);
            void ApplyForce(uge::ActorID actorID, const uge::Vector3& direction, float fNewtons);
            void ApplyImpulse(uge::ActorID actorID, const uge::Vector3& direction, float fNewtons);
            void StopActor(uge::ActorID actorID);
            void SetMaxVelocity(uge::ActorID actorID);

            uge::Vector3 GetPosition(uge::ActorSharedPointer pActor);
            void SetPosition(uge::ActorSharedPointer pActor, const uge::Vector3& newPosition);
            void ApplyForce(uge::ActorSharedPointer pActor, const uge::Vector3& direction, float fNewtons);
            void ApplyImpulse(uge::ActorSharedPointer pActor, const uge::Vector3& direction, float fNewtons);
            void StopActor(uge::ActorSharedPointer pActor);
            void SetMaxVelocity(uge::ActorSharedPointer pActor);

        private:
            uge::ActorSharedPointer m_pPlayer;
            uge::ActorSharedPointer m_pOpponent;

            uge::ActorSharedPointer m_pBall;

            bool m_bPlaying;

            // Maps an actor's archetype to the resource that specializes it.
            std::map<std::string, std::string> m_ActorSpecializationResource;
        };

    }

}
