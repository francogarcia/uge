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

namespace sg
{

    class AudioHumanView : public sg::HumanView
    {
    public:
        AudioHumanView(uge::OutputManager* pOutputManager,
                       uge::ResourceCache& resourceCache,
                       const uge::PlayerProfile& playerProfile)
            : sg::HumanView(pOutputManager,
                            resourceCache,
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
