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

#include "SceneRendererManager.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

namespace uge
{
    SceneRendererManager::SceneRendererManager() : m_pScene(nullptr), m_TotalSceneRenderers(0U)
    {


    }

    SceneRendererManager::~SceneRendererManager()
    {

    }

    bool SceneRendererManager::Init(IScene* pScene)
    {
        m_pScene = dynamic_cast<Scene*>(pScene);
        assert(m_pScene && "Invalid scene!");

        RegisterEvents();

        return true;
    }

    bool SceneRendererManager::Destroy()
    {
        UnregisterEvents();

        m_SceneRenderers.empty();
        m_TotalSceneRenderers = 0U;

        m_pCamera.reset();

        m_pScene = nullptr;

        return true;
    }

    bool SceneRendererManager::Update(const unsigned long timeElapsed)
    {
        m_pCamera->vSetViewMatrix();
        for (auto& sceneRenderer : m_SceneRenderers)
        {
            ISceneRendererSharedPointer pSceneRenderer = sceneRenderer.second;
            // Set the camera - needed if it is moving.
            pSceneRenderer->vOnUpdateCamera(m_pCamera);

            if (!pSceneRenderer->vOnUpdate(timeElapsed))
            {
                return false;
            }
        }

        return true;
    }

    bool SceneRendererManager::Render()
    {
        bool bContinue = true;
        for (auto& sceneRenderer : m_SceneRenderers)
        {
            bContinue &= sceneRenderer.second->vOnRender();
        }

        return bContinue;
    }

    SceneRendererID SceneRendererManager::AddSceneRenderer(ISceneRendererSharedPointer pSceneRenderer)
    {
        ++m_TotalSceneRenderers;
        m_SceneRenderers.insert(std::make_pair(m_TotalSceneRenderers, pSceneRenderer));

        pSceneRenderer->CreateScene(m_pScene);

        if (m_pCamera != nullptr)
        {
            pSceneRenderer->vOnSetCamera(m_pCamera);
        }
        else
        {
            //assert(0 && "Camera was not created yet!");
        }

        return m_TotalSceneRenderers;
    }

    ISceneRendererSharedPointer SceneRendererManager::GetSceneRenderer(SceneRendererID sceneRendererID)
    {
        ISceneRendererMap::iterator findIt = m_SceneRenderers.find(sceneRendererID);
        assert((findIt != m_SceneRenderers.end()) && "Scene renderer not found!");

        return findIt->second;
    }

    void SceneRendererManager::RemoveSceneRenderer(SceneRendererID sceneRendererID)
    {
        assert(sceneRendererID <= m_TotalSceneRenderers && "Invalid scene renderer ID!");

        m_SceneRenderers.erase(sceneRendererID);
        --m_TotalSceneRenderers;
    }

    // Currently, only one camera is supported.
    void SceneRendererManager::AddCamera(ICameraNodeSharedPointer pCamera)
    {
        m_pCamera = std::dynamic_pointer_cast<CameraNode>(pCamera);
        m_pCamera->vInit(m_pScene);

        // Register camera to renderers.
        for (auto& sceneRenderer : m_SceneRenderers)
        {
            sceneRenderer.second->vOnSetCamera(m_pCamera);
        }
    }

    // Currently, only one camera is supported.
    ICameraNodeSharedPointer SceneRendererManager::AddCamera(float fFieldOfView,
                                                             float fAspectRatio,
                                                             float fNearPlaneDistance,
                                                             float fFarPlaneDistance,
                                                             const Vector3& cameraPosition)
    {
        Frustum viewFrustum;
        viewFrustum.Init(fFieldOfView, fAspectRatio, fNearPlaneDistance, fFarPlaneDistance);

        Matrix4 cameraInitialTransform;
        cameraInitialTransform.MakeTranslationMatrix(cameraPosition);

        // Register the camera to all the renderers.
        ICameraNodeSharedPointer pCamera(LIB_NEW CameraNode(cameraInitialTransform, viewFrustum));
        AddCamera(pCamera);

        return pCamera;
    }

    // Currently, only one camera is supported.
    void SceneRendererManager::RemoveCamera(CameraNodeSharedPointer pCamera)
    {
        // FIXME: change this when more than one camera is supported.
        m_pCamera = nullptr;
    }

    bool SceneRendererManager::OnAddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        for (auto& sceneRenderer : m_SceneRenderers)
        {
            if (!sceneRenderer.second->vOnAddChild(actorID, pSceneNode))
            {
                assert(0 && "Error adding the scene node to a scene renderer!");

                return false;
            }
        }

        return true;
    }

    bool SceneRendererManager::OnRemoveSceneNode(ActorID actorID)
    {
        ISceneNodeSharedPointer pSceneNode = m_pScene->vFindActor(actorID);
        assert(pSceneNode != nullptr && "The scene not was not found!");

        bool bSuccess = true;

        for (auto& sceneRenderer : m_SceneRenderers)
        {
            bSuccess &= sceneRenderer.second->vOnRemoveChild(actorID, pSceneNode);
            assert(bSuccess && "Error removing the scene node from a scene renderer!");
        }

        return bSuccess;
    }

    ISceneNodeSharedPointer SceneRendererManager::GetSceneNode(ActorID actorID)
    {
        return m_pScene->vFindActor(actorID);
    }

    void SceneRendererManager::RegisterEvents()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &SceneRendererManager::SceneNodeAttachedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_Scene_Node_Attached::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &SceneRendererManager::SceneNodeRemovedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_Scene_Node_Removed::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &SceneRendererManager::RenderComponentChangedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_Changed_Render_Component::sk_EventType);
    }

    void SceneRendererManager::UnregisterEvents()
    {

    }

    void SceneRendererManager::SceneNodeAttachedDelegate(IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Scene_Node_Attached> pData = std::static_pointer_cast<EvtData_Scene_Node_Attached>(pEventData);

        ActorID actorID = pData->GetActorID();
        ISceneNodeSharedPointer pSceneNode = GetSceneNode(actorID);

        OnAddSceneNode(actorID, pSceneNode);
    }

    void SceneRendererManager::SceneNodeRemovedDelegate(IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Scene_Node_Removed> pData = std::static_pointer_cast<EvtData_Scene_Node_Removed>(pEventData);

        ActorID actorID = pData->GetActorID();

        OnRemoveSceneNode(actorID);
    }

    void SceneRendererManager::RenderComponentChangedDelegate(IEventDataSharedPointer pEventData)
    {
        // TODO
        std::shared_ptr<EvtData_Changed_Render_Component> pData = std::static_pointer_cast<EvtData_Changed_Render_Component>(pEventData);

        ActorID actorID = pData->GetActorID();
    }

}
