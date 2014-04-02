#include "GameEngineStd.h"

#include "BaseGameLogic.h"

#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

#include "GameState/BaseGameState.h"

namespace uge
{

    BaseGameLogic::BaseGameLogic()
        : m_pGameState(nullptr), m_pNextGameState(nullptr),
          m_pActorFactory(nullptr), m_pGameStateFactory(nullptr),
          m_pTaskManager(nullptr), m_LifeTime(0u),
          m_LastActorID(Actor::NULL_ACTOR_ID)
    {

    }

    BaseGameLogic::~BaseGameLogic()
    {
        if (m_pGameState != nullptr)
        {
            vDestroy();
        }
    }

    // Must be called by child.
    bool BaseGameLogic::vInit()
    {
        RegisterEvents();
        RegisterDelegates();

        m_LifeTime = 0u;
        m_LastActorID = Actor::NULL_ACTOR_ID;

        m_pActorFactory = vCreateActorFactory();

        m_pPhysics.reset(vCreatePhysics());

        m_pTaskManager = LIB_NEW TaskManager;

        if (!m_SceneManager.Init())
        {
            return false;
        }

        // TODO / FIXME : handle return values.
        m_pGameStateFactory = vCreateGameStateFactory();
        m_pGameStateFactory->Init();
        assert(m_pGameStateFactory != nullptr && "Invalid game state factory!");
        
        m_pNextGameState = nullptr;
        m_pGameState = m_pGameStateFactory->CreateGameState(GameState::Initializing::g_Name);
        m_pGameState->vInit(this);
        m_PlayerProfileFileName = "";
        m_pGameState->vTailorToProfile(m_PlayerProfileFileName);

        return true;
    }

    // Must be called by child.
    bool BaseGameLogic::vDestroy()
    {
        if (!m_SceneManager.Destroy())
        {
            return false;
        }

        SAFE_DELETE(m_pActorFactory);
        SAFE_DELETE(m_pGameStateFactory);
        SAFE_DELETE(m_pTaskManager);

        m_pGameState->vDestroy();
        m_pGameState = nullptr;
        m_pNextGameState = nullptr;

        for (auto& actorIt : m_Actors)
        {
            actorIt.second->Destroy();
        }
        m_Actors.clear();

        // If debug drawer is enabled, physics must be deleted before the render systems.
        if (!m_pPhysics->vDestroy())
        {
            return false;
        }
        m_pPhysics.reset();

        //while (!m_GameViews.empty())
        //{
        //    m_GameViews.pop_front();
        //}

        UnregisterDelegates();
        UnregisterEvents();

        return true;
    }

    bool BaseGameLogic::vLoadGame(const std::string& levelResource)
    {
        // TODO : implement this.

        return false;
    }

    void BaseGameLogic::vOnUpdate(unsigned long currentTime, unsigned long timeElapsed)
    {
        // Convert from nano to milliseconds.
        unsigned long timeElapsedMs = timeElapsed * 1000;
        m_LifeTime += timeElapsed;

        m_pGameState->vOnUpdate(timeElapsed);
        if (m_pNextGameState != nullptr)
        {
            vChangeState();
        }

        //// Update all views.
        //for (auto&   viewIt : m_GameViews)
        //{
        //    viewIt->vOnUpdate(timeElapsed);
        //}

        // Update the scene.
        // FIXME : maybe this should happen before the game state update?
        if (!m_SceneManager.Update(timeElapsed))
        {
            assert(0 && "Error updating the game scene!");
        }

        // Update all actors.
        // FIXME: this is not needed.
        for (auto& actorIt : m_Actors)
        {
            actorIt.second->Update(timeElapsed);
        }
    }

    void BaseGameLogic::vChangeGameState(const std::string& gameStateName)
    {
        IGameState* pNewState = m_pGameStateFactory->CreateGameState(gameStateName);
        assert(pNewState != nullptr && "Invalid new state!");

        m_pNextGameState = pNewState;
    }

    IGameState* BaseGameLogic::vGetGameState() const
    {
        return m_pGameState;
    }

    ActorFactory* BaseGameLogic::vCreateActorFactory()
    {
        return LIB_NEW ActorFactory;
    }

    GameStateFactory* BaseGameLogic::vCreateGameStateFactory()
    {
        return LIB_NEW GameStateFactory;
    }

    IPhysics* BaseGameLogic::vCreatePhysics()
    {
        return LIB_NEW NullPhysics;
    }

    void BaseGameLogic::vSetPlayerProfileFileName(const std::string& profileFileName)
    {
        m_PlayerProfileFileName = profileFileName;
    }

    ActorSharedPointer BaseGameLogic::vCreateActor(const std::string& actorResource, XMLElement* pActorSpecificData, const Matrix4* pInitialTransform)
    {
        assert((m_pActorFactory != nullptr) && "Actor factory was not initialized!");
        assert((actorResource != "") && "Invalid resource file!");

        // TODO: use the optional initial transform.
        ActorSharedPointer pActor = m_pActorFactory->CreateActor(actorResource, pActorSpecificData);
        if (pActor)
        {
            m_LastActorID = pActor->GetActorID();
            m_Actors.insert(std::make_pair(m_LastActorID, pActor));
            if (m_pGameState->vGetName() == GameState::Running::g_Name)
            {
                IEventDataSharedPointer pNewActorEventData(LIB_NEW EvtData_New_Actor(m_LastActorID));
                IEventManager::Get()->vTriggerEvent(pNewActorEventData);
            }

            return pActor;
        }
        else
        {
            LOG_ERROR("The actor could not be created!");

            return ActorSharedPointer();
        }
    }

    void BaseGameLogic::vDestroyActor(const ActorID actorID)
    {
        assert((actorID != Actor::NULL_ACTOR_ID) && "Invalid actor id!");

        // This allows other systems to do handle the actor removal whilst it is still available.
        IEventDataSharedPointer pDestroyActorEventData(LIB_NEW EvtData_Destroy_Actor(actorID));
        IEventManager::Get()->vTriggerEvent(pDestroyActorEventData);

        auto findIt = m_Actors.find(actorID);
        if (findIt != m_Actors.end())
        {
            findIt->second->Destroy();
            m_Actors.erase(findIt);
        }
        else
        {
            LOG_ERROR("Actor was not found!");
        }
    }

    ActorWeakPointer BaseGameLogic::vGetActor(const ActorID actorID)
    {
        assert((actorID != Actor::NULL_ACTOR_ID) && "Invalid actor id!");

        auto findIt = m_Actors.find(actorID);
        if (findIt != m_Actors.end())
        {
            return findIt->second;
        }
        else
        {
            LOG_WARNING("Actor " + UIntToString(actorID) + " was not found!");

            return ActorWeakPointer();
        }
    }

    const Matrix4& BaseGameLogic::GetActorTransform(const ActorID actorID)
    {
        ActorSharedPointer pActor = vGetActor(actorID).lock();
        Component::TransformableComponentSharedPointer pTransformComponent =
            pActor->GetComponent<Component::TransformableComponent>(Component::TransformableComponent::g_ComponentName).lock();
        assert(pTransformComponent != nullptr && "Actor does not have a transform component!");

        return pTransformComponent->GetTransform();
    }

    void BaseGameLogic::vMoveActor(const ActorID actorID, const Matrix4& transform)
    {
        ActorSharedPointer pActor = vGetActor(actorID).lock();
        Component::TransformableComponentSharedPointer pTransformComponent =
            pActor->GetComponent<Component::TransformableComponent>(Component::TransformableComponent::g_ComponentName).lock();
        assert(pTransformComponent != nullptr && "Actor does not have a transform component!");

        pTransformComponent->SetTransform(transform);

        // Update to the physics system as well (this will trigger a event).
        m_pPhysics->vSetTransform(actorID, transform);
    }

    void BaseGameLogic::vModifyActor(const ActorID actorID, XMLElement* pActorSpecificData)
    {
        assert((m_pActorFactory != nullptr) && "Actor factory was not initialized!");
        assert((pActorSpecificData != nullptr) && "Invalid actor's data!");

        auto findIt = m_Actors.find(actorID);
        if (findIt != m_Actors.end())
        {
            m_pActorFactory->ModifyActor(findIt->second, pActorSpecificData);
        }
    }

    IPhysicsSharedPointer BaseGameLogic::vGetPhysics()
    {
        return m_pPhysics;
    }

    void BaseGameLogic::vEnablePhysicsDebug(ISceneRendererSharedPointer pRenderer)
    {
        m_pPhysics->vEnableDebug(pRenderer);
    }

    void BaseGameLogic::vDisablePhysicsDebug()
    {
        m_pPhysics->vDisableDebug();
    }

    //void BaseGameLogic::vAddView(IGameViewSharedPointer pView, ActorID actorID)
    //{
    //    assert((pView != nullptr) && "Invalid game view!");

    //    m_GameViews.push_back(pView);

    //    GameViewID viewID = m_GameViews.size();
    //    pView->vOnAttach(viewID, actorID);
    //    pView->vOnRestore();
    //}

    //void BaseGameLogic::vRemoveView(IGameViewSharedPointer pView)
    //{
    //    assert((pView != nullptr) && "Invalid game view!");

    //    m_GameViews.remove(pView);
    //}

    void BaseGameLogic::AttachTask(TaskSharedPointer pTask)
    {
        assert((m_pTaskManager != nullptr) &&  "Task Manager wasn't initialized yet!");
        assert((pTask != nullptr) && "Invalid task!");

        m_pTaskManager->AttachTask(pTask);
    }

    void BaseGameLogic::RegisterEvents()
    {
        RegisterEngineScriptEvents();
    }

    void BaseGameLogic::UnregisterEvents()
    {
        UnregisterEngineScriptEvents();
    }

    void BaseGameLogic::RegisterEngineScriptEvents()
    {
        //REGISTER_SCRIPT_EVENT(EvtData_Request_Destroy_Actor, EvtData_Request_Destroy_Actor::sk_EventType);
        //REGISTER_SCRIPT_EVENT(EvtData_PhysCollision, EvtData_PhysCollision::sk_EventType);
        //REGISTER_SCRIPT_EVENT(EvtData_PlaySound, EvtData_PlaySound::sk_EventType);
    }

    void BaseGameLogic::UnregisterEngineScriptEvents()
    {
        //REGISTER_SCRIPT_EVENT(EvtData_Request_Destroy_Actor, EvtData_Request_Destroy_Actor::sk_EventType);
        //REGISTER_SCRIPT_EVENT(EvtData_PhysCollision, EvtData_PhysCollision::sk_EventType);
        //REGISTER_SCRIPT_EVENT(EvtData_PlaySound, EvtData_PlaySound::sk_EventType);
    }

    void BaseGameLogic::RegisterDelegates()
    {
        vRegisterGameDelegates();
    }

    void BaseGameLogic::UnregisterDelegates()
    {
        vUnregisterGameDelegates();
    }

    const bool BaseGameLogic::CanRunLua() const
    {
        return (m_pGameState->vGetName() != GameState::Running::g_Name);
    }

    ActorID BaseGameLogic::GetLastActorID()
    {
        return m_LastActorID;
    }

    Scene* BaseGameLogic::vGetScene()
    {
        return m_SceneManager.GetScene();
    }

    void BaseGameLogic::vRegisterGameEvents()
    {

    }

    void BaseGameLogic::vUnregisterGameEvents()
    {

    }

    void BaseGameLogic::vRegisterGameDelegates()
    {

    }

    void BaseGameLogic::vUnregisterGameDelegates()
    {

    }

    void BaseGameLogic::vChangeState()
    {
        // TODO / FIXME : handle return values.
        m_pGameState->vDestroy();

        m_pGameState = m_pNextGameState;
        m_pGameState->vInit(this);
        m_pGameState->vTailorToProfile(m_PlayerProfileFileName);

        m_pNextGameState = nullptr;
    }

    ISceneNodeSharedPointer BaseGameLogic::vCreateAndAddSceneNode(ActorSharedPointer pActor)
    {
        return m_SceneManager.CreateAndAddSceneNode(pActor);
    }

    bool BaseGameLogic::vAddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        return m_SceneManager.AddSceneNode(actorID, pSceneNode);
    }

    bool BaseGameLogic::vRemoveSceneNode(ActorID actorID)
    {
        return m_SceneManager.RemoveSceneNode(actorID);
    }

    void BaseGameLogic::NewActorRequestedDelegate(IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Request_New_Actor> pData = std::static_pointer_cast<EvtData_Request_New_Actor>(pEventData);
        ActorSharedPointer pActor = vCreateActor(pData->GetActorResource());

        if (!pActor)
        {
            LOG_ERROR("Could not create the actor!");
        }

        std::shared_ptr<EvtData_New_Actor> pNewActorEvent(LIB_NEW EvtData_New_Actor(pActor->GetActorID()));
        IEventManager::Get()->vQueueEvent(pNewActorEvent);
    }

    //void BaseGameLogic::ActorMovedDelegate(IEventDataSharedPointer pEventData)
    //{
    //    std::shared_ptr<EvtData_Move_Actor> pData = std::static_pointer_cast<EvtData_Move_Actor>(pEventData);
    //    vMoveActor(pData->GetActorID(), pData->GetTransform());
    //}

    void BaseGameLogic::ActorDestroyedDelegate(IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Destroy_Actor> pData = std::static_pointer_cast<EvtData_Destroy_Actor>(pEventData);
        vDestroyActor(pData->GetActorID());
    }

}
