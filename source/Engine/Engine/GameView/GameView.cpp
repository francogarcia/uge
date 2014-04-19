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
 */

#include "GameEngineStd.h"

#include "GameView.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Events/IEventManager.h>
#include <Core/Events/DefaultEvents.h>

namespace uge
{

    HumanGameView::HumanGameView() : m_ActorID(Actor::NULL_ACTOR_ID),
        m_pGameState(nullptr), m_GameViewID(IGameView::NULL_GAME_VIEW_ID),
        m_pTaskManager(nullptr), m_bIsPaused(false)
    {

    }

    HumanGameView::~HumanGameView()
    {

    }

    bool HumanGameView::vInit(IScene* const pScene)
    {
        // FIXME: handle this.
        //m_pGameState = LIB_NEW GameStateInitializing;
        m_bIsPaused = false;

        m_pTaskManager = LIB_NEW TaskManager;

        RegisterAllDelegates();

        if (!m_SceneRenderManager.Init(pScene))
        {
            return false;
        }

        m_pCamera = vCreateCamera();
        assert(m_pCamera != nullptr && "Invalid camera!");
        m_SceneRenderManager.AddCamera(m_pCamera);

        m_pController = vCreateController();
        assert(m_pController != nullptr && "Invalid controller!");
        m_pController->vInit();

        return true;
    }

    bool HumanGameView::vDestroy()
    {
        UnregisterAllDelegates();

        if (!m_SceneRenderManager.Destroy())
        {
            return false;
        }

        SAFE_DELETE(m_pTaskManager);

        m_pController->vDestroy();
        m_pController.reset();

        m_pCamera.reset();

        return true;
    }

    GameViewID HumanGameView::vGetID() const
    {
        return m_GameViewID;
    }

    GameViewType HumanGameView::vGetType() const
    {
        return GameViewType::HumanView;
    }

    void HumanGameView::vOnAttach(GameViewID viewID, ActorID actorID)
    {
        m_GameViewID = viewID;
        
        vSetControlledActor(actorID, false);
    }

    void HumanGameView::vOnRestore()
    {

    }

    bool HumanGameView::vOnUpdate(const unsigned long timeElapsed)
    {
        unsigned long timeElapsedMs = timeElapsed * 1000u;
        m_pTaskManager->UpdateTasks(timeElapsed);

        if (!m_SceneRenderManager.Update(timeElapsed))
        {
            return false;
        }

        m_pController->vUpdate(timeElapsed);

        return true;
    }

    bool HumanGameView::vOnRender(const unsigned long currentTime, const unsigned timeElapsed)
    {
        if (!m_SceneRenderManager.Render())
        {
            return false;
        }

        return true;
    }

    SceneRendererID HumanGameView::vAddSceneRenderer(ISceneRendererSharedPointer pRenderer)
    {
        return m_SceneRenderManager.AddSceneRenderer(pRenderer);
    }

    ISceneRendererSharedPointer HumanGameView::vGetSceneRenderer(SceneRendererID rendererID)
    {
        return m_SceneRenderManager.GetSceneRenderer(rendererID);
    }

    void HumanGameView::vRemoveSceneRenderer(SceneRendererID rendererID)
    {
        m_SceneRenderManager.RemoveSceneRenderer(rendererID);
    }

    void HumanGameView::vSetControlledActor(ActorID actorID, bool bSetCameraTarget)
    {
        m_ActorID = actorID;
        if (m_pController != nullptr)
        {
            m_pController->SetControlledActorID(actorID);
        }

        if (bSetCameraTarget)
        {
            ISceneNodeSharedPointer pActorNode = m_SceneRenderManager.GetSceneNode(actorID);
            m_pCamera->vSetTarget(pActorNode);
        }
    }

    void HumanGameView::TogglePaused(bool bIsPaused)
    {
        m_bIsPaused = bIsPaused;
        if (m_bIsPaused)
        {
            // Pause all sounds and graphics
        }
        else
        {
            // Resume all sounds and graphics
        }
    }

    bool HumanGameView::IsPaused() const
    {
        return m_bIsPaused;
    }

    ICameraNodeSharedPointer HumanGameView::GetCamera() const
    {
        return m_pCamera;
    }

    //void HumanGameView::vCreateCamera()
    //{
    //    // TODO: refactor this.

    //    uge::Frustum viewFrustum;
    //    float fAspectRatio = 800.0 / 600.0f;
    //    viewFrustum.Init(45.0f, fAspectRatio, 5.0f, 100.0f); // fov, aspect ratio, near plane, far plane
    //    uge::Matrix4 cameraInitialTransform;
    //    cameraInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, 200.f));

    //    m_pCamera.reset(LIB_NEW uge::CameraNode(cameraInitialTransform, viewFrustum));
    //    m_SceneRenderManager.AddCamera(m_pCamera);
    //}

    void HumanGameView::vRegisterViewDelegates()
    {

    }

    void HumanGameView::vUnegisterViewDelegates()
    {

    }

    void HumanGameView::GameStateDelegate(IEventDataSharedPointer pEventData)
    {

    }

    void HumanGameView::RegisterAllDelegates()
    {
        IEventManager* pGlobalEventManager = IEventManager::Get();
        //pGlobalEventManager->vAddListener(fastdelegate::MakeDelegate(this, &HumanGameView::GameStateDelegate), EvtData_GameState::sk_EventType);

        vRegisterViewDelegates();
    }

    void HumanGameView::UnregisterAllDelegates()
    {
        IEventManager* pGlobalEventManager = IEventManager::Get();
        //pGlobalEventManager->vRemoveListener(fastdelegate::MakeDelegate(this, &HumanGameView::GameStateDelegate), EvtData_GameState::sk_EventType);

        vUnegisterViewDelegates();
    }

}
