#pragma once

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Entity/ActorFactory.h>

#include <Core/Events/IEventManager.h>

#include <Core/Task/TaskManager.h>

#include <Engine/GameView/GameView.h>

#include "IGameLogic.h"
#include "GameState/GameStateFactory.h"
#include "SceneManager/SceneManager.h"

namespace uge
{

    class BaseGameLogic : public IGameLogic
    {
    public:
        BaseGameLogic();

        ~BaseGameLogic();

        virtual bool vInit() override;

        virtual bool vDestroy() override;

        virtual bool vLoadGame(const std::string& levelResource) override;

        // Times in milliseconds.
        virtual void vOnUpdate(unsigned long currentTime, unsigned long timeElapsed) override;

        virtual void vChangeGameState(const std::string& gameStateName) override;
        IGameState* vGetGameState() const override;

        virtual ActorSharedPointer vCreateActor(const std::string& actorResource, XMLElement* pActorSpecificData = nullptr, const Matrix4* pInitialTransform = nullptr) override;
        virtual ActorWeakPointer vGetActor(const ActorID actorID) override;
        virtual void vDestroyActor(const ActorID actorID) override;

        // TODO: add translation
        virtual const Matrix4& GetActorTransform(const ActorID actorID);
        virtual void vMoveActor(const ActorID actorID, const Matrix4& transform) override;
        virtual void vModifyActor(const ActorID actorID, XMLElement* pActorSpecificData) override;

        virtual IPhysicsSharedPointer vGetPhysics() override;
        virtual void vEnablePhysicsDebug(ISceneRendererSharedPointer pRenderer);
        virtual void vDisablePhysicsDebug();

        //virtual void vAddView(IGameViewSharedPointer pView, ActorID actorID);
        //virtual void vRemoveView(IGameViewSharedPointer pView);

        void AttachTask(TaskSharedPointer pTask);

        const bool CanRunLua() const;

        ActorID GetLastActorID();

        virtual Scene* vGetScene();

        virtual void vSetPlayerProfileFileName(const std::string& profileFileName);

    protected:
        virtual ActorFactory* vCreateActorFactory();
        virtual GameStateFactory* vCreateGameStateFactory();
        virtual IPhysics* vCreatePhysics();

        virtual void vRegisterGameEvents();
        virtual void vUnregisterGameEvents();

        virtual void vRegisterGameDelegates();
        virtual void vUnregisterGameDelegates();

        virtual void vChangeState();

    public: // FIXME: this should be protected, not public!
        // This creates the scene node from the actor information and adds it to scene.
        virtual ISceneNodeSharedPointer vCreateAndAddSceneNode(ActorSharedPointer pActor);
        virtual bool vAddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode);
        virtual bool vRemoveSceneNode(ActorID actorID);

    private:
        // TODO: add delegates.
        void NewActorRequestedDelegate(IEventDataSharedPointer pEventData);
        //void ActorMovedDelegate(IEventDataSharedPointer pEventData);
        void ActorDestroyedDelegate(IEventDataSharedPointer pEventData);

    private:
        void RegisterEvents();
        void UnregisterEvents();

        void RegisterEngineScriptEvents();
        void UnregisterEngineScriptEvents();

        void RegisterDelegates();
        void UnregisterDelegates();

    public:
        // Internal use. These methods are only supposed to be called by game states.
        // TODO: make BaseGameLogic friend with GameState::Running and update there.
        TaskManager* GetTaskManager() const
        {
            return m_pTaskManager;
        }

    protected:
        GameStateFactory* m_pGameStateFactory;
        IGameState* m_pGameState;
        IGameState* m_pNextGameState;

        TaskManager* m_pTaskManager;

        ActorMap m_Actors;
        ActorFactory* m_pActorFactory;
        ActorID m_LastActorID;

        IPhysicsSharedPointer m_pPhysics;

        //IGameViewList m_GameViews;
        SceneManager m_SceneManager;

        // Player profile settings.
        std::string m_PlayerProfileFileName;

        unsigned long m_LifeTime;
    };

}
