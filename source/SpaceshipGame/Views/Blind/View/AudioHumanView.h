#pragma once

#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>

#include <Core/PlayerProfile/PlayerProfiles.h>

#include <Core/Scene/Implementation/Ogre3D/OgreSceneNodeRenderer.h>
#include <Core/Scene/Implementation/Ogre3D/OgreSceneRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneNodeRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneRenderer.h>

#include <Engine/GameView/GameView.h>

#include "../../AverageUser/View/HumanView.h"

namespace sg
{

    class AudioHumanView : public sg::HumanView
    {
    public:
        AudioHumanView(uge::IGraphicsSharedPointer pGraphics,
                       uge::IAudioSharedPointer pAudio,
                       uge::ResourceCache& resourceCache,
                       const uge::PlayerProfile& playerProfile)
            : sg::HumanView(pGraphics, pAudio, resourceCache,
                            playerProfile)
        {

        }

        ~AudioHumanView()
        {

        }

    protected:
        virtual bool vInit(uge::IScene* pScene) override
        {
            if (!sg::HumanView::vInit(pScene))
            {
                return false;
            }

            m_bSetCameraTarget = true;

            return true;
        }

        virtual bool vDestroy() override
        {
            if (!sg::HumanView::vDestroy())
            {
                return false;
            }

            return true;
        }

        virtual void vSetControlledActor(uge::ActorID actorID, bool bSetCameraTarget) override
        {
            sg::HumanView::vSetControlledActor(actorID, m_bSetCameraTarget);

            // First-person camera settings.
            if (m_bSetCameraTarget)
            {
                m_pCamera->vSetCameraOffset(uge::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
                m_pCamera->vSetCameraOrientation(3.14f, 0.0f, 0.0f);
                m_pCamera->vSetTarget(m_SceneRenderManager.GetSceneNode(actorID));
            }
        }
    };

}
