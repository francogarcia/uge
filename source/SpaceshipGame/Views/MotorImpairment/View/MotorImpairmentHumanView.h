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

#include "../Controller/MotorImpairmentGameController.h"

namespace sg
{

    class MotorImpairmentHumanView : public sg::HumanView
    {
    public:
        MotorImpairmentHumanView(uge::IGraphicsSharedPointer pGraphics,
                                 uge::IAudioSharedPointer pAudio,
                                 uge::ResourceCache& resourceCache,
                                 const uge::PlayerProfile& playerProfile)
            : sg::HumanView(pGraphics, pAudio, resourceCache, playerProfile)
        {

        }

        ~MotorImpairmentHumanView()
        {

        }

    protected:
        virtual uge::GameControllerSharedPointer vCreateController() override
        {
            uge::GameControllerSharedPointer pController(
                LIB_NEW MotorImpairmentGameController(
                    m_PlayerProfile.GetGraphicalPreferences().GetWindowSettings(),
                    m_pGraphics->vGetWindowHandle()));

            return pController;
        }
    };

}
