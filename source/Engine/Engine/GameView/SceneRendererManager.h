#pragma once

#include <Core/Scene/IScene.h>
#include <Core/Scene/Scene.h>
#include <Core/Scene/SceneEvents.h>

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
