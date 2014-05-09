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

#include <IO/Output/Graphics/Implementation/Ogre3D/Scene/OgreSceneRenderer.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/Scene/OgreSceneNodeRenderer.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/Scene/OpenALSoftSceneNodeRenderer.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/Scene/OpenALSoftSceneRenderer.h>

#include <Engine/GameView/GameView.h>

#include "../../AverageUser/View/HumanView.h"

#include "../Controller/MotorImpairmentGameController.h"

namespace sg
{

    class MotorImpairmentHumanView : public sg::HumanView
    {
    public:
        MotorImpairmentHumanView(uge::OutputManager* pOutputManager,
                                 uge::ResourceCache& resourceCache,
                                 const uge::PlayerProfile& playerProfile)
            : sg::HumanView(pOutputManager,
                            resourceCache,
                            playerProfile)
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
                    m_PlayerProfile.GetOutputSettings().GetOutputSettingsData().window,
                    m_pGraphics->vGetWindowHandle()));

            return pController;
        }
    };

}
