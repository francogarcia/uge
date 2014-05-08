/*
 * (c) Copyright 2014 Franco Eusébio Garcia
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

#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>

#include <Core/PlayerProfile/PlayerProfile.h>

#include <Core/Scene/Implementation/Ogre3D/OgreSceneNodeRenderer.h>
#include <Core/Scene/Implementation/Ogre3D/OgreSceneRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneNodeRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneRenderer.h>

#include <Engine/GameView/GameView.h>

#include "../../EventFeedback/AuralFeedback.h"
#include "../../EventFeedback/FeedbackFactory.h"

#include "Controller/GameController.h"

namespace sg
{

    class HumanView : public uge::HumanGameView
    {
    public:
        HumanView(uge::IGraphicsSharedPointer pGraphics,
                  uge::IAudioSharedPointer pAudio,
                  uge::ResourceCache& resourceCache,
                  const uge::PlayerProfile& playerProfile)
            : m_pGraphics(pGraphics), m_pAudio(pAudio),
              m_ResourceCache(resourceCache), m_PlayerProfile(playerProfile),
              m_bSetCameraTarget(false)
        {

        }

        ~HumanView()
        {

        }

        uge::ISceneRendererSharedPointer GetPhysicsDebugRenderer()
        {
            return vGetSceneRenderer(m_GraphicalRendererID);
        }

    protected:
        virtual bool vInit(uge::IScene* pScene) override
        {
            if (!uge::HumanGameView::vInit(pScene))
            {
                return false;
            }

            RegisterEventDelegates();

            m_bSetCameraTarget = false;

            // Rendering subsystems.
            uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer(m_pGraphics, m_ResourceCache));
            pOgreSceneRenderer->Load();

            m_GraphicalRendererID = vAddSceneRenderer(pOgreSceneRenderer);

            uge::OpenALSoftSceneRendererSharedPointer pOpenALSoftSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer(m_pAudio, m_ResourceCache));
            m_AuralRendererID = vAddSceneRenderer(pOpenALSoftSceneRenderer);

            m_FeedbackFactory.Init();

            SetEventFeedback();

            return true;
        }

        virtual bool vDestroy() override
        {
            if (!uge::HumanGameView::vDestroy())
            {
                return false;
            }

            UnregisterEventDelegates();

            return true;
        }

        virtual uge::ICameraNodeSharedPointer vCreateCamera() override
        {
            const uge::WindowSettings::WindowSettingsData& windowSettings = m_PlayerProfile.GetOutputSettings().GetOutputSettingsData().window.GetWindowSettingsData();

            uge::Frustum viewFrustum;
            float fAspectRatio = windowSettings.width / windowSettings.height;
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
            uge::GameControllerSharedPointer pController(LIB_NEW GameController(m_PlayerProfile.GetOutputSettings().GetOutputSettingsData().window,
                                                                                m_pGraphics->vGetWindowHandle()));

            return pController;
        }

        virtual void vSetControlledActor(uge::ActorID actorID, bool bSetCameraTarget = false) override
        {
            uge::HumanGameView::vSetControlledActor(actorID, bSetCameraTarget);
        }

    private:
        void RegisterEventDelegates()
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &sg::HumanView::ControlledActorDelegate);
            uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_Set_Controlled_Actor::sk_EventType);
        }

        void UnregisterEventDelegates()
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &sg::HumanView::ControlledActorDelegate);
            uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_Set_Controlled_Actor::sk_EventType);
        }

        void ControlledActorDelegate(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<uge::EvtData_Set_Controlled_Actor> pData = std::static_pointer_cast<uge::EvtData_Set_Controlled_Actor>(pEventData);

            uge::ActorID actorID = pData->GetActorID();
            vSetControlledActor(actorID, m_bSetCameraTarget);
        }

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

    protected:
        uge::IGraphicsSharedPointer m_pGraphics;
        uge::IAudioSharedPointer m_pAudio;
        uge::ResourceCache& m_ResourceCache;

        uge::SceneRendererID m_AuralRendererID;
        uge::SceneRendererID m_GraphicalRendererID;

        uge::PlayerProfile m_PlayerProfile;

        sg::FeedbackFactory m_FeedbackFactory;
        uge::IViewFeedback* m_pViewFeedback;

        bool m_bSetCameraTarget;
    };

}
