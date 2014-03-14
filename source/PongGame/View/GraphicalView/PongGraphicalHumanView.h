#pragma once

#include <Core/PlayerProfile/PlayerProfiles.h>

#include <Core/Scene/Implementation/Ogre3D/OgreSceneNodeRenderer.h>
#include <Core/Scene/Implementation/Ogre3D/OgreSceneRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneNodeRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneRenderer.h>

#include "../PongHumanView.h"

#include "Events/GraphicalFeedback.h"

class PongGraphicalHumanView : public PongHumanView
{
public:
    PongGraphicalHumanView(uge::IGraphicsSharedPointer pGraphics,
                           uge::IAudioSharedPointer pAudio,
                           uge::ResourceCache& resourceCache,
                           const uge::PlayerProfile& playerProfile)
        : m_pGraphics(pGraphics), m_pAudio(pAudio),
          m_ResourceCache(resourceCache), m_PlayerProfile(playerProfile)
    {

    }

    ~PongGraphicalHumanView()
    {

    }

    uge::ISceneRendererSharedPointer GetPhysicsDebugRenderer()
    {
        return vGetSceneRenderer(m_GraphicalRendererID);
    }

protected:
    virtual bool vInit(uge::IScene* pScene) override
    {
        if (!PongHumanView::vInit(pScene))
        {
            return false;
        }

        uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer(m_pGraphics, m_ResourceCache));
        pOgreSceneRenderer->Load();

        // TODO: save the renderer ID.
        m_GraphicalRendererID = vAddSceneRenderer(pOgreSceneRenderer);

        uge::OpenALSoftSceneRendererSharedPointer pOpenALSoftSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer(m_pAudio, m_ResourceCache));
        m_AuralRendererID = vAddSceneRenderer(pOpenALSoftSceneRenderer);

        // FIXME: temporary
        GraphicalFeedback::Options gfOptions;
        //gfOptions.bEnableOnRestartGame = true;
        //gfOptions.bEnableOnPlayerScored = true;
        //gfOptions.bEnableOnBallWallCollision = true;
        //gfOptions.bEnableOnBallPaddleCollision = true;
        //gfOptions.bEnableOnPaddleWallCollision = true;
        //gfOptions.bEnableOnMovePaddle = true;
        //gfOptions.bEnableOnStopPaddle = true;
        m_pGraphicsFeedback = LIB_NEW GraphicalFeedback(gfOptions, m_pGraphics);

        return true;
    }

    virtual bool vDestroy() override
    {
        SAFE_DELETE(m_pGraphicsFeedback);

        if (!PongHumanView::vDestroy())
        {
            return false;
        }

        return true;
    }

    virtual uge::ICameraNodeSharedPointer vCreateCamera() override
    {
        uge::Frustum viewFrustum;
        float fAspectRatio = 1024.0 / 768.0f;
        viewFrustum.Init(45.0f, fAspectRatio, 5.0f, 10000.0f); // fov, aspect ratio, near plane, far plane

        const uge::Vector3 position(0.0f, 500.0f, 0.0f);
        const uge::Vector3 rotation(-1.57f, 0.0f, 0.0f);

        uge::Matrix4 cameraInitialTransform;
        cameraInitialTransform.MakeRotationMatrix(uge::Quaternion(rotation));
        cameraInitialTransform.SetPositionFromVector(position);

        uge::ICameraNodeSharedPointer pCamera(LIB_NEW uge::CameraNode(cameraInitialTransform, viewFrustum));

        return pCamera;
    }

    virtual uge::GameControllerSharedPointer vCreateController() override
    {
        uge::GameControllerSharedPointer pController(LIB_NEW PongGameController(m_PlayerProfile.GetGraphicalPreferences().GetWindowSettings(),
                                                                                m_pGraphics->vGetWindowHandle()));

        return pController;
    }

    virtual void vSetControlledActor(uge::ActorID actorID, bool bSetCameraTarget = false) override
    {
        uge::HumanGameView::vSetControlledActor(actorID, bSetCameraTarget);
    }

private:
    uge::IGraphicsSharedPointer m_pGraphics;
    uge::IAudioSharedPointer m_pAudio;
    uge::ResourceCache& m_ResourceCache;

    uge::SceneRendererID m_AuralRendererID;
    uge::SceneRendererID m_GraphicalRendererID;

    uge::PlayerProfile m_PlayerProfile;

    // Temporary
    GraphicalFeedback* m_pGraphicsFeedback;
};
