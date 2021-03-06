/*
  * (c) Copyright 2014 Franco Eus�bio Garcia
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

#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>

#include <Core/PlayerProfile/PlayerProfiles.h>

#include <Core/Scene/Implementation/Ogre3D/OgreSceneNodeRenderer.h>
#include <Core/Scene/Implementation/Ogre3D/OgreSceneRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneNodeRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneRenderer.h>

#include <Engine/GameView/GameView.h>

#include "../Controller/GameController.h"

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
          m_ResourceCache(resourceCache), m_PlayerProfile(playerProfile)
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

        // Rendering subsystems.
        uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer(m_pGraphics, m_ResourceCache));
        pOgreSceneRenderer->Load();

        // TODO: save the renderer ID.
        m_GraphicalRendererID = vAddSceneRenderer(pOgreSceneRenderer);

        uge::OpenALSoftSceneRendererSharedPointer pOpenALSoftSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer(m_pAudio, m_ResourceCache));
        m_AuralRendererID = vAddSceneRenderer(pOpenALSoftSceneRenderer);

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
        uge::Frustum viewFrustum;
        float fAspectRatio = 1024.0f / 768.0f;
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
        uge::GameControllerSharedPointer pController(LIB_NEW GameController(m_PlayerProfile.GetGraphicalPreferences().GetWindowSettings(),
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
        vSetControlledActor(actorID, false);
    }

private:
    uge::IGraphicsSharedPointer m_pGraphics;
    uge::IAudioSharedPointer m_pAudio;
    uge::ResourceCache& m_ResourceCache;

    uge::SceneRendererID m_AuralRendererID;
    uge::SceneRendererID m_GraphicalRendererID;

    uge::PlayerProfile m_PlayerProfile;
};

}
