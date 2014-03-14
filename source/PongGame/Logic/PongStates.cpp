#include "PongGameStd.h"

#include "PongStates.h"

namespace PongState
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

        m_pGameLogic->vChangeGameState(uge::GameState::Running::g_Name);

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

    Running::Running()
        : m_Paddle1ID(uge::Actor::NULL_ACTOR_ID),
          m_Paddle2ID(uge::Actor::NULL_ACTOR_ID)
    {

    }

    Running::~Running()
    {

    }

    bool Running::vInit(uge::BaseGameLogic* pGameLogic)
    {
        std::cout << "[Running] Game is running!" << std::endl;

        uge::GameState::BaseGameState::vInit(pGameLogic);

        RegisterDelegates();

        uge::IPhysicsSharedPointer pPhysics = pGameLogic->vGetPhysics();
        pPhysics->vSetGravity(uge::Vector3(0.0f, 0.0f, 0.0f));

        // Paddles
        m_pPaddle1 = pGameLogic->vCreateActor("data/game/entity/paddle-player1.xml", nullptr);
        AddToActorNameToIDMap(m_pPaddle1);
        m_Paddle1ID = m_pPaddle1->GetActorID();
        pPhysics->vAddActor(m_pPaddle1);

        m_pPaddle2 = pGameLogic->vCreateActor("data/game/entity/paddle-player2.xml", nullptr);
        AddToActorNameToIDMap(m_pPaddle2);
        m_Paddle2ID = m_pPaddle2->GetActorID();
        pPhysics->vAddActor(m_pPaddle2);

        // Ball
        m_pBall = pGameLogic->vCreateActor("data/game/entity/ball.xml", nullptr);
        AddToActorNameToIDMap(m_pBall);
        m_BallID = m_pBall->GetActorID();
        pPhysics->vAddActor(m_pBall);

        // Field
        m_pLeftWall = pGameLogic->vCreateActor("data/game/entity/wall-left.xml", nullptr);
        AddToActorNameToIDMap(m_pLeftWall);
        m_LeftWallID = m_pLeftWall->GetActorID();
        pPhysics->vAddActor(m_pLeftWall);

        m_pRightWall = pGameLogic->vCreateActor("data/game/entity/wall-right.xml", nullptr);
        AddToActorNameToIDMap(m_pRightWall);
        m_RightWallID = m_pRightWall->GetActorID();
        pPhysics->vAddActor(m_pRightWall);

        m_pTopWall = pGameLogic->vCreateActor("data/game/entity/wall-top.xml", nullptr);
        AddToActorNameToIDMap(m_pTopWall);
        m_TopWallID = m_pTopWall->GetActorID();
        pPhysics->vAddActor(m_pTopWall);

        m_pBottomWall = pGameLogic->vCreateActor("data/game/entity/wall-bottom.xml", nullptr);
        AddToActorNameToIDMap(m_pBottomWall);
        m_BottomWallID = m_pBottomWall->GetActorID();
        pPhysics->vAddActor(m_pBottomWall);

        uge::ActorSharedPointer pPlane = pGameLogic->vCreateActor("data/game/entity/plane.xml", nullptr);
        AddToActorNameToIDMap(pPlane);
        m_PlaneID = pPlane->GetActorID();
        pPhysics->vAddActor(pPlane);

        // Initial movement.
        ApplyForce(m_pBall, uge::Vector3(1.0f, 0.0f, 1.0f), 10.0f); // Initial impulse.

        // Reset initial game score.
        m_Paddle1Score = 0u;
        m_Paddle2Score = 0u;

        // Events
        std::shared_ptr<uge::EvtData_Set_Controlled_Actor> pEvent(LIB_NEW uge::EvtData_Set_Controlled_Actor(m_Paddle1ID));
        uge::IEventManager::Get()->vQueueEvent(pEvent);

        return true;
    }

    bool Running::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        // Overrides the presentation data using the chosen profile.
        LoadProfile(xmlResourceFilename);

        // FIXME: can be done within a loop.
        // Add actors to the scene.
        m_pGameLogic->vCreateAndAddSceneNode(m_pBall);
        m_pGameLogic->vCreateAndAddSceneNode(m_pPaddle1);
        m_pGameLogic->vCreateAndAddSceneNode(m_pPaddle2);
        m_pGameLogic->vCreateAndAddSceneNode(m_pLeftWall);
        m_pGameLogic->vCreateAndAddSceneNode(m_pRightWall);
        m_pGameLogic->vCreateAndAddSceneNode(m_pTopWall);
        m_pGameLogic->vCreateAndAddSceneNode(m_pBottomWall);
        //m_pGameLogic->vCreateAndAddSceneNode(pPlane);

        return true;
    }

    bool Running::vDestroy()
    {
        UnregisterDelegates();

        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool Running::vOnUpdate(unsigned long timeElapsed)
    {
        bool bSuccess = uge::GameState::Running::vOnUpdate(timeElapsed);

        SetMaxVelocity(m_pBall);

        return bSuccess;
    }

    bool Running::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    void Running::AddToActorNameToIDMap(uge::ActorSharedPointer pActor)
    {
        m_ActorNameToID[pActor->GetActorType()] = pActor->GetActorID();
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

            entityResource.CloseFile();
        }

        entityListFile.CloseFile();
    }

    uge::Vector3 Running::GetPosition(uge::ActorID actorID)
    {
        return GetPosition(m_pGameLogic->vGetActor(actorID).lock());
    }

    void Running::SetPosition(uge::ActorID actorID, uge::Vector3& newPosition)
    {
        SetPosition(m_pGameLogic->vGetActor(actorID).lock(), newPosition);
    }

    void Running::ApplyForce(uge::ActorID actorID, uge::Vector3& direction, float fNewtons)
    {
        return ApplyForce(m_pGameLogic->vGetActor(actorID).lock(), direction, fNewtons);
    }

    void Running::ApplyImpulse(uge::ActorID actorID, uge::Vector3& direction, float fNewtons)
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

    void Running::SetPosition(uge::ActorSharedPointer pActor, uge::Vector3& newPosition)
    {
        uge::Component::TransformableComponentSharedPointer pActorTransformComponent =
            pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        pActorTransformComponent->SetPosition(uge::Vector3(0.0f, 0.0f, 0.0f));

        m_pGameLogic->vMoveActor(pActor->GetActorID(), pActorTransformComponent->GetTransform());
    }

    void Running::ApplyForce(uge::ActorSharedPointer pActor, uge::Vector3& direction, float fNewtons)
    {
        uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
            pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();
        pActorPhysicsComponent->vApplyForce(direction, fNewtons);
    }

    void Running::ApplyImpulse(uge::ActorSharedPointer pActor, uge::Vector3& direction, float fNewtons)
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

    void Running::HandleBallCollision(uge::ActorID collisionActorID, const CollisionInfo& info)
    {
        if (collisionActorID == m_Paddle1ID || collisionActorID == m_Paddle2ID)
        {
            HandleBallPaddleCollision(collisionActorID, info);
        }
        else
        {
            HandleBallWallCollision(collisionActorID, info);
        }
    }

    void Running::HandleBallWallCollision(uge::ActorID collisionActorID, const CollisionInfo& info)
    {
        if (collisionActorID == m_LeftWallID || collisionActorID == m_RightWallID)
        {
            HandleGoal(collisionActorID, info);
        }
        else
        {
            HandleRebound(collisionActorID, info);
        }
    }

    void Running::HandleGoal(uge::ActorID collisionActorID, const CollisionInfo& info)
    {
        if (collisionActorID == m_LeftWallID)
        {
            ++m_Paddle2Score;
            //std::cout << "Player 2 scored! Total: " << m_Paddle2Score << std::endl;

            SetPosition(m_pBall, uge::Vector3(0.0f, 0.0f, 0.0f));
            StopActor(m_pBall);
            ApplyForce(m_pBall, uge::Vector3(1.0f, 0.0f, 1.0f), -400.0f);
        }
        else
        {
            ++m_Paddle1Score;

            SetPosition(m_pBall, uge::Vector3(0.0f, 0.0f, 0.0f));
            StopActor(m_pBall);
            ApplyForce(m_pBall, uge::Vector3(1.0f, 0.0f, 1.0f), 400.0f);
        }

        std::shared_ptr<EvtData_Player_Scored> pScoredEvent(LIB_NEW EvtData_Player_Scored(collisionActorID));
        uge::IEventManager::Get()->vQueueEvent(pScoredEvent);

        std::shared_ptr<EvtData_Restart_Game> pRestartEvent(LIB_NEW EvtData_Restart_Game);
        uge::IEventManager::Get()->vQueueEvent(pRestartEvent);
    }

    void Running::HandleRebound(uge::ActorID collisionActorID, const CollisionInfo& info)
    {
        std::shared_ptr<EvtData_Ball_Wall_Collision> pEvent(LIB_NEW EvtData_Ball_Wall_Collision(m_BallID,
                                                                                                collisionActorID,
                                                                                                info.sumNormalForce,
                                                                                                info.sumFrictionForce,
                                                                                                info.collisionPoints));
        uge::IEventManager::Get()->vQueueEvent(pEvent);
    }

    void Running::HandlePaddleWallCollision(uge::ActorID actorA, uge::ActorID actorB, const CollisionInfo& info)
    {
        uge::ActorID paddleID;
        uge::ActorID wallID;
        if (actorA == m_Paddle1ID)
        {
            paddleID = m_Paddle1ID;
            wallID = actorB;
        }
        else if (actorB == m_Paddle1ID)
        {
            paddleID = m_Paddle1ID;
            wallID = actorA;
        }
        else if (actorA == m_Paddle2ID)
        {
            paddleID = m_Paddle2ID;
            wallID = actorB;
        }
        else if (actorB == m_Paddle2ID)
        {
            paddleID = m_Paddle2ID;
            wallID = actorA;
        }

        StopActor(paddleID);

        std::shared_ptr<EvtData_Paddle_Wall_Collision> pEvent(LIB_NEW EvtData_Paddle_Wall_Collision(paddleID,
                                                                                                    wallID,
                                                                                                    info.sumNormalForce,
                                                                                                    info.sumFrictionForce,
                                                                                                    info.collisionPoints));
        uge::IEventManager::Get()->vQueueEvent(pEvent);
    }

    void Running::HandleBallPaddleCollision(uge::ActorID collisionActorID, const CollisionInfo& info)
    {
        // Dispatch paddle collision event
        if (collisionActorID == m_Paddle1ID)
        {
            //ApplyForce(m_pBall, uge::Vector3(1.0f, 0.0f, 1.0f), 1000.0f);
        }
        else
        {
            //ApplyForce(m_pBall, uge::Vector3(-1.0f, 0.0f, -1.0f), 1000.0f);
        }

        std::shared_ptr<EvtData_Ball_Paddle_Collision> pEvent(LIB_NEW EvtData_Ball_Paddle_Collision(m_BallID,
                                                                                                    collisionActorID,
                                                                                                    info.sumNormalForce,
                                                                                                    info.sumFrictionForce,
                                                                                                    info.collisionPoints));
        uge::IEventManager::Get()->vQueueEvent(pEvent);
    }

    void Running::RegisterDelegates()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionStartedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &Running::PaddleStartedMovingDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Move_Paddle::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &Running::PaddleStoppedMovingDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Stop_Paddle::sk_EventType);
    }

    void Running::UnregisterDelegates()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &Running::CollisionStartedDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &Running::PaddleStartedMovingDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, EvtData_Move_Paddle::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &Running::PaddleStoppedMovingDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, EvtData_Stop_Paddle::sk_EventType);
    }

    void Running::PaddleStartedMovingDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Move_Paddle> pData = std::static_pointer_cast<EvtData_Move_Paddle>(pEventData);

        uge::ActorID actorID = pData->GetActorID();
        std::string direction = pData->GetDirection();
        if (actorID == m_Paddle1ID)
        {
            if (direction == "Up")
            {
                ApplyForce(m_pPaddle1, uge::Vector3(0.0f, 0.0f, 1.0f), 10.0f);
                SetMaxVelocity(m_pPaddle1);
            }
            else
            {
                ApplyForce(m_pPaddle1, uge::Vector3(0.0f, 0.0f, -1.0f), 10.0f);
                SetMaxVelocity(m_pPaddle1);
            }
        }
        else
        {
            if (direction == "Up")
            {
                ApplyForce(m_pPaddle2, uge::Vector3(0.0f, 0.0f, 1.0f), 10.0f);
                SetMaxVelocity(m_pPaddle2);
            }
            else
            {
                ApplyForce(m_pPaddle2, uge::Vector3(0.0f, 0.0f, -1.0f), 10.0f);
                SetMaxVelocity(m_pPaddle2);
            }
            // This is only possible when using a kinematic physics body.
            //uge::Component::TransformableComponentSharedPointer pActorTransformComponent =
            //    m_pPaddle2->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            //uge::Matrix4 actorTransform = pActorTransformComponent->GetTransform();

            //if (direction == "Up")
            //{
            //    actorTransform.Translate(uge::Vector3(0.0f, 0.0f, 5.0f));
            //}
            //else
            //{
            //    actorTransform.Translate(uge::Vector3(0.0f, 0.0f, -5.0f));
            //}

            //m_pGameLogic->vMoveActor(actorID, actorTransform);
        }
    }

    void Running::PaddleStoppedMovingDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Stop_Paddle> pData = std::static_pointer_cast<EvtData_Stop_Paddle>(pEventData);

        uge::ActorID actorID = pData->GetActorID();
        if (actorID == m_Paddle1ID)
        {
            StopActor(m_pPaddle1);
        }
        else
        {
            StopActor(m_pPaddle2);
        }
    }

    void Running::CollisionStartedDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_PhysCollision> pData = std::static_pointer_cast<uge::EvtData_PhysCollision>(pEventData);

        uge::ActorID actorA = pData->GetActorA();
        uge::ActorID actorB = pData->GetActorB();

        //std::cout << actorA << " collided with " << actorB << "!\n";

        CollisionInfo info;
        info.collisionPoints = pData->GetCollisionPoints();
        info.sumFrictionForce = pData->GetSumFrictionForce();
        info.sumNormalForce =  pData->GetSumNormalForce();

        // Check if one of the actors is the ball.
        if (actorA == m_BallID)
        {
            // Bullet does not always insert a contact point, so we add the ball's position.
            if (info.collisionPoints.size() == 0)
            {
                info.collisionPoints.push_back(GetPosition(m_pBall));
            }

            HandleBallCollision(actorB, info);
        }
        else if (actorB == m_BallID)
        {
            // Bullet does not always insert a contact point, so we add the ball's position.
            if (info.collisionPoints.size() == 0)
            {
                info.collisionPoints.push_back(GetPosition(m_pBall));
            }

            HandleBallCollision(actorA, info);
        }
        else
        {
            // The collision happened between a paddle and a wall.

            // Bullet does not always insert a contact point, so we add the ball's position.
            if (info.collisionPoints.size() == 0)
            {
                info.collisionPoints.push_back(GetPosition(actorA));
            }

            HandlePaddleWallCollision(actorA, actorB, info);
        }
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

    const char* HiScores::g_Name = "HiScores";

    HiScores::HiScores()
    {

    }

    HiScores::~HiScores()
    {

    }

    bool HiScores::vInit(uge::BaseGameLogic* pGameLogic)
    {
        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool HiScores::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool HiScores::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool HiScores::vOnUpdate(unsigned long timeElapsed)
    {
        return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
    }

    bool HiScores::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string HiScores::vGetName() const
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
        return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
    }

    bool NewGame::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string NewGame::vGetName() const
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
