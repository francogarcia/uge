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

#include <Core/PlayerProfile/PlayerProfile.h>

#include <IO/Output/Graphics/Implementation/Ogre3D/Scene/OgreSceneRenderer.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/Scene/OgreSceneNodeRenderer.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/Scene/OpenALSoftSceneNodeRenderer.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/Scene/OpenALSoftSceneRenderer.h>

#include "../PongHumanView.h"

// FIXME : temporary
#include "Events/AuralFeedback.h"

#include "../EventFeedback/PongFeedbackFactory.h"

class PongAuralHumanView : public PongHumanView
{
public:
    PongAuralHumanView(uge::OutputManager* pOutputManager,
                           uge::ResourceCache& resourceCache,
                           const uge::PlayerProfile& playerProfile)
        : m_pOutputManager(pOutputManager), m_pGraphics(nullptr), m_pAudio(nullptr),
          m_ResourceCache(resourceCache), m_PlayerProfile(playerProfile)
    {
        uge::IGraphicsWeakPointer pWeakGraphics = m_pOutputManager->GetOutputSystem<uge::IGraphics>(1);//m_GraphicsID);
        m_pGraphics = pWeakGraphics.lock();
        uge::IAudioWeakPointer pWeakAudio = m_pOutputManager->GetOutputSystem<uge::IAudio>(2);//m_AudioID);
        m_pAudio = pWeakAudio.lock();
    }

    ~PongAuralHumanView()
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

        uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer);
        pOgreSceneRenderer->vInit(m_pGraphics, &m_ResourceCache);
        pOgreSceneRenderer->Load();

        m_GraphicalRendererID = vAddSceneRenderer(pOgreSceneRenderer);

        uge::OpenALSoftSceneRendererSharedPointer pOpenALSoftSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer);
        pOpenALSoftSceneRenderer->vInit(m_pAudio, &m_ResourceCache);
        m_AuralRendererID = vAddSceneRenderer(pOpenALSoftSceneRenderer);

        m_FeedbackFactory.Init();

        SetEventFeedback();

        return true;
    }

    virtual bool vDestroy() override
    {
        SAFE_DELETE(m_pViewFeedback);

        if (!uge::HumanGameView::vDestroy())
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
        uge::GameControllerSharedPointer pController(LIB_NEW PongGameController(m_PlayerProfile.GetOutputSettings().GetOutputSettingsData().window,
                                                                                m_pGraphics->vGetWindowHandle()));

        return pController;
    }

    virtual void vSetControlledActor(uge::ActorID actorID, bool bSetCameraTarget) override
    {
        uge::HumanGameView::vSetControlledActor(actorID, bSetCameraTarget);

        bSetCameraTarget = true;
        // FIXME: temporary, for first person camera.
        if (bSetCameraTarget)
        {
            m_pCamera->vSetCameraOffset(uge::Vector4(-10.0f, 2.0f, 0.0f, 0.0f));
            m_pCamera->vSetCameraOrientation(-1.57f, -0.0f, 0.0f);
            m_pCamera->vSetTarget(m_SceneRenderManager.GetSceneNode(actorID));
        }
    }

private:
    void SetEventFeedback()
    {
        uge::GameplaySettings::GameplaySettingsData gameplaySettings = m_PlayerProfile.GetGameplaySettings().GetGameplaySettingsData();
        const auto& specializations = gameplaySettings.eventSpecializationResources;
        for (const auto& specialization : specializations)
        {
            std::string name = specialization.first;
            std::string resource = specialization.second;

            m_pViewFeedback = m_FeedbackFactory.CreateViewFeedback(name);
            assert(m_pViewFeedback != nullptr && "Invalid event specializaton!");

            m_pViewFeedback->vInit(resource);
            m_pViewFeedback->vSetAudioSystem(m_pAudio);
            m_pViewFeedback->vSetGraphicsSystem(m_pGraphics);
        }
    }

private:
    uge::OutputManager* m_pOutputManager;

    uge::IGraphicsSharedPointer m_pGraphics;
    uge::IAudioSharedPointer m_pAudio;
    uge::ResourceCache& m_ResourceCache;

    uge::SceneRendererID m_AuralRendererID;
    uge::SceneRendererID m_GraphicalRendererID;

    uge::PlayerProfile m_PlayerProfile;

    PongFeedbackFactory m_FeedbackFactory;
    uge::IViewFeedback* m_pViewFeedback;
};
