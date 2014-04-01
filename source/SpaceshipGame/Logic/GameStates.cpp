#include "SpaceshipGameStd.h"

#include "GameStates.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Core/Physics/PhysicsEvents.h>

#include "Components/DamageInflictingComponent.h"
#include "Components/DamageSoakingComponent.h"
#include "Components/HealthComponent.h"

#include "Events/GameEvents.h"

#include "GameLogic.h"

namespace sg
{

    namespace GameState
    {

        Initializing::Initializing()
        {

        }

        Initializing::~Initializing()
        {

        }

        bool Initializing::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[Initializing] Initializing the game!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool Initializing::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Initializing::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool Initializing::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(SplashScreen::g_Name);

            return bSuccess;
        }

        bool Initializing::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        SplashScreen::SplashScreen()
        {

        }

        SplashScreen::~SplashScreen()
        {

        }

        const char* SplashScreen::g_Name = "SplashScreen";

        bool SplashScreen::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[SplashScreen] Splash screen!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool SplashScreen::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool SplashScreen::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool SplashScreen::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(MainMenu::g_Name);

            return bSuccess;
        }

        bool SplashScreen::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string SplashScreen::vGetName() const
        {
            return g_Name;
        }

        const char* MainMenu::g_Name = "MainMenu";

        MainMenu::MainMenu()
        {

        }

        MainMenu::~MainMenu()
        {

        }

        bool MainMenu::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[MainMenu] Main menu!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool MainMenu::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool MainMenu::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool MainMenu::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(NewGame::g_Name);

            return bSuccess;
        }

        bool MainMenu::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string MainMenu::vGetName() const
        {
            return g_Name;
        }


        const char* NewGame::g_Name = "NewGame";

        NewGame::NewGame()
        {

        }

        NewGame::~NewGame()
        {

        }

        bool NewGame::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[NewGame] NewGame!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool NewGame::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool NewGame::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool NewGame::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(uge::GameState::Running::g_Name);

            return bSuccess;
        }

        bool NewGame::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string NewGame::vGetName() const
        {
            return g_Name;
        }

        static const std::string g_kActorTypeAlien = "Alien";
        static const std::string g_kActorTypeBomb = "Bomb";
        static const std::string g_kActorTypeBullet = "Bullet";
        static const std::string g_kActorTypeSpaceship = "Spaceship";

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

            return true;
        }

        bool Running::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            // Overrides the presentation data using the chosen profile.
            LoadProfile(xmlResourceFilename);

            // Add actors to the scene.
            sg::GameLogic* pGameLogic = dynamic_cast<sg::GameLogic*>(m_pGameLogic);
            for (const auto& actorIt : pGameLogic->m_Actors)
            {
                uge::ActorSharedPointer pActor = actorIt.second;

                pGameLogic->vCreateAndAddSceneNode(pActor);
            }

            std::shared_ptr<uge::EvtData_Set_Controlled_Actor> pEvent(LIB_NEW uge::EvtData_Set_Controlled_Actor(m_pSpaceship->GetActorID()));
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

            RemoveDestroyedActors();
            MoveEnemies();
            MakeEnemiesAttack();

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
            m_pSpaceship = CreateAndRegisterActor("data/game/actors/spaceship.xml");
            if (m_pSpaceship == uge::ActorSharedPointer())
            {
                return false;
            }

            uge::ActorSharedPointer pActor;

            uge::XMLFile aliens;
            aliens.OpenFile("data/game/actors/aliens.xml", uge::File::FileMode::FileReadOnly);
            uge::XMLElement xmlRoot = aliens.GetRootElement();
            for (uge::XMLElement xmlElement = xmlRoot.GetFirstChildElement("Actor");
                 xmlElement.IsGood();
                 xmlElement = xmlElement.GetNextSiblingElement())
            {
                pActor = CreateAndRegisterActor("data/game/actors/alien.xml", &xmlElement);
                if (pActor == uge::ActorSharedPointer())
                {
                    return false;
                }
            }
            aliens.CloseFile();

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

            m_ActorNameToID[pActor->GetActorType()] = pActor->GetActorID();

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

            uge::XMLElement entityListRoot = entityListFile.GetRootElement();
            for (uge::XMLElement entityElement = entityListRoot.GetFirstChildElement();
                 entityElement.IsGood();
                 entityElement = entityElement.GetNextSiblingElement())
            {
                std::string entityName;
                entityElement.GetAttribute("name", &entityName);

                std::string entityResourceFileName;
                entityElement.GetAttribute("resource", &entityResourceFileName);

                uge::XMLFile entityResource;
                entityResource.OpenFile(entityResourceFileName, uge::File::FileMode::FileReadOnly);

                uge::ActorID actorID = m_ActorNameToID[entityName];
                m_pGameLogic->vModifyActor(actorID, &entityResource.GetRootElement());
                uge::ActorSharedPointer pActor = m_pGameLogic->vGetActor(actorID).lock();
                pActor->PostInit();

                // Re-add the actor to the physics simulation (its transform or shape
                // might have changed).
                RemoveActorFromPhysics(actorID);
                AddActorToPhysics(pActor);

                entityResource.CloseFile();
            }

            entityListFile.CloseFile();
        }

        void Running::MoveEnemies()
        {
            // Move the enemies in a random sense with probability kProbabilityToMove.
            sg::GameLogic* pGameLogic = dynamic_cast<sg::GameLogic*>(m_pGameLogic);
            for (const auto& actorIt : pGameLogic->m_Actors)
            {
                uge::ActorID actorID = actorIt.first;
                uge::ActorSharedPointer pActor = actorIt.second;
                if (pActor->GetActorType() != g_kActorTypeAlien)
                {
                    continue;
                }

                const unsigned int kProbabilityToMove = 5u;
                const unsigned int kProbabilityToStop = 70u;
                if (std::rand() % 100 > kProbabilityToMove)
                {
                    continue;
                }
                else if (std::rand() % 100 > kProbabilityToStop)
                {
                    uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
                    pPhysics->vStopActor(actorID);

                    continue;
                }

                MoveActor::Direction direction = (std::rand() % 2) ?
                                                 MoveActor::Direction::Left : MoveActor::Direction::Right;
                std::shared_ptr<sg::MoveActor> pEvent(LIB_NEW sg::MoveActor(actorID, direction));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }
        }

        void Running::MakeEnemiesAttack()
        {
            // Make enemies attack with probability kProbabilityToAttack.
            sg::GameLogic* pGameLogic = dynamic_cast<sg::GameLogic*>(m_pGameLogic);
            for (const auto& actorIt : pGameLogic->m_Actors)
            {
                uge::ActorID actorID = actorIt.first;
                uge::ActorSharedPointer pActor = actorIt.second;
                if (pActor->GetActorType() != g_kActorTypeAlien)
                {
                    continue;
                }

                const unsigned int kProbabilityToAttack = 5u;
                if (std::rand() % 1000 > kProbabilityToAttack)
                {
                    continue;
                }

                const unsigned int kProbabilityToUseBomb = 5u;
                FireProjectile::Type type;
                if (std::rand() % 1000 > kProbabilityToUseBomb)
                {
                    type = FireProjectile::Type::Bomb;
                }
                else
                {
                    type = FireProjectile::Type::Bullet;
                }

                std::shared_ptr<sg::FireProjectile> pEvent(LIB_NEW sg::FireProjectile(actorID, type));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }
        }

        void Running::RemoveDestroyedActors()
        {
            std::vector<uge::ActorID> destroyedActorIDs;

            sg::GameLogic* pGameLogic = dynamic_cast<sg::GameLogic*>(m_pGameLogic);
            for (const auto& actorIt : pGameLogic->m_Actors)
            {
                uge::ActorID actorID = actorIt.first;
                uge::ActorSharedPointer pActor = actorIt.second;
                std::weak_ptr<Component::HealthComponent> pComponent = pActor->GetComponent<sg::Component::HealthComponent>(sg::Component::HealthComponent::g_ComponentName);

                // Check if the actor has a HealthComponent.
                if (!pComponent.expired())
                {
                    Component::HealthComponentSharedPointer pSharedComponent = pComponent.lock();
                    if (pSharedComponent->GetHealthPoints() <= 0)
                    {
                        destroyedActorIDs.push_back(actorID);
                    }
                }
            }

            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            for (uge::ActorID actorID : destroyedActorIDs)
            {
                pPhysics->vRemoveActor(actorID);
                pGameLogic->vRemoveSceneNode(actorID);
                pGameLogic->vDestroyActor(actorID);

                std::shared_ptr<sg::AlienDestroyed> pEvent(LIB_NEW sg::AlienDestroyed(actorID));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }
        }

        void Running::RegisterEvents()
        {
            // Creating and registering the event handlers.
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionStarted);
            uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionEnded);
            uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysSeparation::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::AlienDestroyed);
            uge::IEventManager::Get()->vAddListener(functionDelegate, sg::AlienDestroyed::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::MoveActor);
            uge::IEventManager::Get()->vAddListener(functionDelegate, sg::MoveActor::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::StopActor);
            uge::IEventManager::Get()->vAddListener(functionDelegate, sg::StopActor::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::FireProjectile);
            uge::IEventManager::Get()->vAddListener(functionDelegate, sg::FireProjectile::sk_EventType);
        }

        void Running::UnregisterEvents()
        {
            // Removing the delegates.
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionStarted);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionEnded);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysSeparation::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::AlienDestroyed);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, sg::AlienDestroyed::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::MoveActor);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, sg::MoveActor::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::StopActor);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, sg::StopActor::sk_EventType);

            functionDelegate = fastdelegate::MakeDelegate(this, &Running::FireProjectile);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, sg::FireProjectile::sk_EventType);
        }

        void Running::CollisionStarted(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<uge::EvtData_PhysCollision> pData = std::static_pointer_cast<uge::EvtData_PhysCollision>(pEventData);

            printf("Actors %u and %u collided!\n", pData->GetActorA(), pData->GetActorB());

            uge::ActorID actorA = pData->GetActorA();
            uge::ActorID actorB = pData->GetActorB();

            uge::ActorSharedPointer pActorA = m_pGameLogic->vGetActor(actorA).lock();
            uge::ActorSharedPointer pActorB = m_pGameLogic->vGetActor(actorB).lock();

            const std::string actorTypeA = pActorA->GetActorType();
            const std::string actorTypeB = pActorB->GetActorType();
            if (actorTypeA == g_kActorTypeBomb || actorTypeA == g_kActorTypeBullet)
            {
                if (actorTypeB == g_kActorTypeAlien)
                {
                    HandleProjectileCollision(pActorB, pActorA);
                }
                else if (actorTypeB == g_kActorTypeSpaceship)
                {
                    HandleProjectileCollision(pActorB, pActorA);
                }
            }
            else if (actorTypeB == g_kActorTypeBomb || actorTypeB == g_kActorTypeBullet)
            {
                if (actorTypeA == g_kActorTypeAlien)
                {
                    HandleProjectileCollision(pActorA, pActorB);
                }
                else if (actorTypeA == g_kActorTypeSpaceship)
                {
                    HandleProjectileCollision(pActorA, pActorB);
                }
            }
        }

        void Running::HandleProjectileCollision(uge::ActorSharedPointer pTarget, uge::ActorSharedPointer pProjectile)
        {
            // All projectiles should have a DamageInflictingComponent.
            sg::Component::DamageInflictingComponentSharedPointer pDamageComponent =
                pProjectile->GetComponent<sg::Component::DamageInflictingComponent>(sg::Component::DamageInflictingComponent::g_ComponentName).lock();
            int totalDamage = pDamageComponent->GetDamageOutput();

            // A DamageSoaking is optional, so we have to check before converting to a shared pointer (lock()).
            sg::Component::DamageSoakingComponentWeakPointer pWeakSoakingComponent =
                pTarget->GetComponent<sg::Component::DamageSoakingComponent>(sg::Component::DamageSoakingComponent::g_ComponentName);
            if (!pWeakSoakingComponent.expired())
            {
                sg::Component::DamageSoakingComponentSharedPointer pSoakingComponent = pWeakSoakingComponent.lock();
                int shieldProtection = pSoakingComponent->GetCurrentProtection();
                if (shieldProtection > 0)
                {
                    pSoakingComponent->DecrementProtection(totalDamage);
                    totalDamage -= shieldProtection;

                    printf("The shield reduced the damage by: %d!\n", pDamageComponent->GetDamageOutput() - shieldProtection);
                }
            }

            // All targets should have a HealthComponent.
            sg::Component::HealthComponentSharedPointer pTargetHeathComponent =
                pTarget->GetComponent<sg::Component::HealthComponent>(sg::Component::HealthComponent::g_ComponentName).lock();
            if (totalDamage > 0)
            {
                pTargetHeathComponent->DecrementHealthPoints(totalDamage);

                printf("The actor took %d points of damage!\n", totalDamage);
            }

            // Stop the actor that was hit.
            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vStopActor(pTarget->GetActorID());

            // Remove the projectile from the game.
            const uge::ActorID projectileID = pProjectile->GetActorID();
            pPhysics->vRemoveActor(projectileID);
            m_pGameLogic->vRemoveSceneNode(projectileID);
            m_pGameLogic->vDestroyActor(projectileID);
        }

        void Running::CollisionEnded(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<uge::EvtData_PhysSeparation> pData = std::static_pointer_cast<uge::EvtData_PhysSeparation>(pEventData);

            printf("Actors %u and %u stopped colliding!\n", pData->GetActorA(), pData->GetActorB());
        }

        void Running::AlienDestroyed(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<sg::AlienDestroyed> pData = std::static_pointer_cast<sg::AlienDestroyed>(pEventData);

            printf("Alien with ID %u was destroyed!\n", pData->GetActorID());
        }

        void Running::MoveActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<sg::MoveActor> pData = std::static_pointer_cast<sg::MoveActor>(pEventData);

            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();

            MoveActor::Direction direction = pData->GetDirection();
            if (direction == MoveActor::Direction::Left)
            {
                pPhysics->vApplyForce(pData->GetActorID(), uge::Vector3(1.0f, 0.0f, 0.0f), 1.0f);
            }
            else
            {
                pPhysics->vApplyForce(pData->GetActorID(), uge::Vector3(-1.0f, 0.0f, 0.0f), 1.0f);
            }

            uge::ActorSharedPointer pActor = m_pGameLogic->vGetActor(pData->GetActorID()).lock();
            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();

            float fMaxVelocityMagnitude = pActorPhysicsComponent->vGetMaxVelocity();
            uge::Vector3 velocity = pActorPhysicsComponent->vGetVelocity();
            float fCurrentVelocityMagnitude = velocity.Length();

            velocity *= (fMaxVelocityMagnitude / fCurrentVelocityMagnitude);

            pActorPhysicsComponent->vSetVelocity(velocity);
        }

        void Running::StopActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<sg::StopActor> pData = std::static_pointer_cast<sg::StopActor>(pEventData);

            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vStopActor(pData->GetActorID());
        }

        void Running::FireProjectile(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<sg::FireProjectile> pData = std::static_pointer_cast<sg::FireProjectile>(pEventData);

            // Create the desired projectile.
            std::string actorResourceFile("");
            if (pData->GetType() == FireProjectile::Type::Bullet)
            {
                actorResourceFile = "data/game/actors/bullet.xml";
            }
            else
            {
                actorResourceFile = "data/game/actors/bomb.xml";
            }

            uge::ActorSharedPointer pActorProjectile = CreateActor(actorResourceFile);
            assert(pActorProjectile != uge::ActorSharedPointer());

            // Set position.
            uge::ActorSharedPointer pActorOwner = m_pGameLogic->vGetActor(pData->GetActorID()).lock();
            uge::Component::TransformableComponentSharedPointer pOwnerTransformableComponent =
                pActorOwner->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            const uge::Vector3& ownerPosition = pOwnerTransformableComponent->GetPosition();
            const uge::Vector3& ownerRotation = pOwnerTransformableComponent->GetRotationVector();
            const uge::Vector3& ownerScale = pOwnerTransformableComponent->GetScale();

            uge::Vector3 projectilePosition = ownerPosition;
            projectilePosition.z -= (2.0f * ownerScale.z); // Account for half size (center).

            uge::Vector3 projectileRotation = ownerRotation;
            projectileRotation.z += (100.0f * ownerScale.z); // Force a straight shot.
            uge::Vector3 direction = projectileRotation;
            direction.z *= -1.0f; // Reverse the vector's sense.

            uge::Component::TransformableComponentSharedPointer pProjectileTransformableComponent =
                pActorProjectile->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            pProjectileTransformableComponent->SetRotation(projectileRotation);
            pProjectileTransformableComponent->SetPosition(projectilePosition);

            // Add the actor to the physics simulation.
            AddActorToPhysics(pActorProjectile);
            m_ActorNameToID[pActorProjectile->GetActorType()] = pActorProjectile->GetActorID();

            // Add the actor to the scene.
            m_pGameLogic->vCreateAndAddSceneNode(pActorProjectile);

            // Set velocity and apply the initial impulse.
            uge::IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            pPhysics->vApplyForce(pActorProjectile->GetActorID(), direction.GetNormalized(), 1.0f);

            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActorProjectile->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();

            float fMaxVelocityMagnitude = pActorPhysicsComponent->vGetMaxVelocity();
            uge::Vector3 velocity = pActorPhysicsComponent->vGetVelocity();
            float fCurrentVelocityMagnitude = velocity.Length();

            velocity *= (fMaxVelocityMagnitude / fCurrentVelocityMagnitude);
            pActorPhysicsComponent->vSetVelocity(velocity);
        }

        const char* Paused::g_Name = "Paused";

        Paused::Paused()
        {

        }

        Paused::~Paused()
        {

        }

        bool Paused::vInit(uge::BaseGameLogic* pGameLogic)
        {
            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool Paused::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Paused::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool Paused::vOnUpdate(unsigned long timeElapsed)
        {
            return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
        }

        bool Paused::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string Paused::vGetName() const
        {
            return g_Name;
        }

        const char* GameOver::g_Name = "GameOver";

        GameOver::GameOver()
        {

        }

        GameOver::~GameOver()
        {

        }

        bool GameOver::vInit(uge::BaseGameLogic* pGameLogic)
        {
            m_pGameLogic = pGameLogic;

            return true;
        }

        bool GameOver::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool GameOver::vDestroy()
        {
            return true;
        }

        bool GameOver::vOnUpdate(unsigned long timeElapsed)
        {
            return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
        }

        bool GameOver::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string GameOver::vGetName() const
        {
            return g_Name;
        }

        const char* Exiting::g_Name = "Exiting";

        Exiting::Exiting()
        {

        }

        Exiting::~Exiting()
        {

        }

        bool Exiting::vInit(uge::BaseGameLogic* pGameLogic)
        {
            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool Exiting::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Exiting::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool Exiting::vOnUpdate(unsigned long timeElapsed)
        {
            return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
        }

        bool Exiting::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string Exiting::vGetName() const
        {
            return g_Name;
        }

    }

}
