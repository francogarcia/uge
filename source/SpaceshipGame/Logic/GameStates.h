#pragma once

#include <Core/EntityComponent/Component/TransformableComponent.h>
#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>

#include <Core/Events/IEventManager.h>
#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Engine/GameLogic/BaseGameLogic.h>
#include <Engine/GameLogic/GameState/BaseGameState.h>

#include "../Logic/Events/GameEvents.h"

namespace sg
{

    namespace GameState
    {

        class Initializing : public uge::GameState::Initializing
        {
            friend class uge::BaseGameLogic;

        public:
            Initializing();
            virtual ~Initializing();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;
        };

        class SplashScreen : public uge::GameState::BaseGameState
        {
            friend class uge::BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            SplashScreen();
            virtual ~SplashScreen();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

        class MainMenu : public uge::GameState::BaseGameState
        {
            friend class uge::BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            MainMenu();
            virtual ~MainMenu();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

        class NewGame : public uge::GameState::BaseGameState
        {
            friend class uge::BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            NewGame();
            virtual ~NewGame();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

        class Running : public uge::GameState::Running
        {
            friend class uge::BaseGameLogic;

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

            void MoveEnemies();
            void MakeEnemiesAttack();
            void RemoveDestroyedActors();

            void HandleProjectileCollision(uge::ActorSharedPointer pTarget, uge::ActorSharedPointer pProjectile);

            void RegisterEvents();
            void UnregisterEvents();

            void CollisionStarted(uge::IEventDataSharedPointer pEventData);
            void CollisionEnded(uge::IEventDataSharedPointer pEventData);

            void AlienDestroyed(uge::IEventDataSharedPointer pEventData);

            void MoveActor(uge::IEventDataSharedPointer pEventData);
            void StopActor(uge::IEventDataSharedPointer pEventData);

            void FireProjectile(uge::IEventDataSharedPointer pEventData);

        private:
            uge::ActorSharedPointer m_pSpaceship;

            // This should be a multi-map if using an actor's resource as archetype.
            std::map<std::string, uge::ActorID> m_ActorNameToID;
        };

        class Paused : public uge::GameState::BaseGameState
        {
            friend class uge::BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            Paused();
            virtual ~Paused();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

        class GameOver : public uge::GameState::BaseGameState
        {
            friend class uge::BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            GameOver();
            virtual ~GameOver();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

        class Exiting : public uge::GameState::BaseGameState
        {
            friend class uge::BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            Exiting();
            virtual ~Exiting();

            virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

    }

}
