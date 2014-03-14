#include "SpaceshipGameStd.h"

#include "GameStates.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Core/Physics/PhysicsEvents.h>

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

            pActor = CreateAndRegisterActor("data/game/actors/bullet.xml");
            if (pActor == uge::ActorSharedPointer())
            {
                return false;
            }

            pActor = CreateAndRegisterActor("data/game/actors/bomb.xml");
            if (pActor == uge::ActorSharedPointer())
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
                pGameLogic->vDestroyActor(actorID);

                std::shared_ptr<sg::AlienDestroyed> pEvent(LIB_NEW sg::AlienDestroyed(actorID));
                // Event will be triggered during the vUpdate() call.
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
        }

        void Running::CollisionStarted(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<uge::EvtData_PhysCollision> pData = std::static_pointer_cast<uge::EvtData_PhysCollision>(pEventData);

            printf("Actors %u and %u collided!\n", pData->GetActorA(), pData->GetActorB());
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
