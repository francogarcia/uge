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

#include "HumanView.h"

namespace pg
{

    class FirstPersonHumanView : public pg::HumanView
    {
    public:
        FirstPersonHumanView(uge::OutputManager* pOutputManager,
                             uge::ResourceCache& resourceCache,
                             const uge::PlayerProfile& playerProfile)
                             : HumanView(pOutputManager, resourceCache, playerProfile)
        {
            m_bSetCameraTarget = true;
        }

        ~FirstPersonHumanView()
        {

        }

    protected:
        virtual void vSetControlledActor(uge::ActorID actorID, bool bSetCameraTarget = true) override
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
    };

}
