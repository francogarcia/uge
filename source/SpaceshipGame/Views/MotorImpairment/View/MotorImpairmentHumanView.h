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
