/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#include <Core/EntityComponent/Entity/ActorTypes.h>
#include <Core/Events/Event.h>
#include <Core/Task/TaskManager.h>

#include <Engine/GameLogic/GameState/BaseGameState.h>
#include <Engine/GameController/GameController.h>

#include "IGameView.h"
#include "SceneRendererManager.h"

namespace uge
{

    class HumanGameView : public IGameView
    {
    public:
        HumanGameView();
        ~HumanGameView();

        virtual bool vInit(IScene* pScene) override;
        virtual bool vDestroy() override;

        virtual GameViewID vGetID() const override;
        virtual GameViewType vGetType() const override;

        virtual void vOnAttach(GameViewID viewID, ActorID actorID) override;
        virtual void vOnRestore() override;
        virtual bool vOnUpdate(const unsigned long timeElapsed) override;
        virtual bool vOnRender(const unsigned long currentTime, const unsigned timeElapsed) override;

        virtual SceneRendererID vAddSceneRenderer(ISceneRendererSharedPointer pRenderer) override;
        virtual ISceneRendererSharedPointer vGetSceneRenderer(SceneRendererID rendererID) override;
        virtual void vRemoveSceneRenderer(SceneRendererID rendererID) override;

        virtual void vSetControlledActor(ActorID actorID, bool bSetCameraTarget = false);

        void TogglePaused(bool bIsPaused);
        bool IsPaused() const;

        ICameraNodeSharedPointer GetCamera() const;

    protected:
        virtual ICameraNodeSharedPointer vCreateCamera() = 0;
        virtual GameControllerSharedPointer vCreateController() = 0;

        virtual void vRegisterViewDelegates();
        virtual void vUnegisterViewDelegates();

    private:
        void GameStateDelegate(IEventDataSharedPointer pEventData);
        // TODO: add new render component delegate, etc.

        void RegisterAllDelegates();
        void UnregisterAllDelegates();

    protected:
        GameViewID m_GameViewID;
        ActorID m_ActorID;

        TaskManager* m_pTaskManager;

        IGameState* m_pGameState;

        SceneRendererManager m_SceneRenderManager;
        ICameraNodeSharedPointer m_pCamera;

        GameControllerSharedPointer m_pController;

        bool m_bIsPaused;
    };

}
