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

#include <Core/Scene/IScene.h>
#include <Core/Scene/Scene.h>
#include <Core/Scene/SceneEvents.h>

#include <IO/Output/Scene/ISceneRenderer.h>

namespace uge
{
    class SceneRendererManager
    {
    public:
        SceneRendererManager();

        ~SceneRendererManager();

        bool Init(IScene* pScene);

        bool Destroy();

        bool Update(const unsigned long timeElapsed);

        bool Render();

        SceneRendererID AddSceneRenderer(ISceneRendererSharedPointer pSceneRenderer);
        ISceneRendererSharedPointer GetSceneRenderer(SceneRendererID sceneRendererID);
        void RemoveSceneRenderer(SceneRendererID sceneRendererID);

        // Currently, only one camera is supported.
        void AddCamera(ICameraNodeSharedPointer pCamera);

        // Currently, only one camera is supported.
        ICameraNodeSharedPointer AddCamera(float fFieldOfView, float fAspectRatio, float fNearPlaneDistance, float fFarPlaneDistance,
                                           const Vector3& cameraPosition);

        // Currently, only one camera is supported.
        void RemoveCamera(CameraNodeSharedPointer pCamera);

        bool OnAddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode);

        bool OnRemoveSceneNode(ActorID actorID);

        ISceneNodeSharedPointer GetSceneNode(ActorID actorID);

    private:
        void RegisterEvents();
        void UnregisterEvents();

        void SceneNodeAttachedDelegate(IEventDataSharedPointer pEventData);
        void SceneNodeRemovedDelegate(IEventDataSharedPointer pEventData);
        void RenderComponentChangedDelegate(IEventDataSharedPointer pEventData);

    private:
        // Scene
        Scene* m_pScene;

        // Camera
        CameraNodeSharedPointer m_pCamera;

        // Renderers
        SceneRendererID m_TotalSceneRenderers;
        ISceneRendererMap m_SceneRenderers;
    };

}
