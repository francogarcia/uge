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

#include "GameEngineStd.h"

#include "SceneRendererFactory.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

// First for subsystem name, second for scene renderer.
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/Scene/OpenALSoftSceneRenderer.h>

#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>
#include <IO/Output/Audio/Implementation/YSE/Scene/YSESceneRenderer.h>

#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/Scene/OgreSceneRenderer.h>

namespace uge
{

    SceneRendererFactory::SceneRendererFactory()
    {

    }

    SceneRendererFactory::~SceneRendererFactory()
    {

    }

    void SceneRendererFactory::Init()
    {
        m_Factory.Register<OgreSceneRenderer>(StringToLower(OgreGraphics::g_Name));
        m_Factory.Register<OpenALSoftSceneRenderer>(StringToLower(OpenALSoftAudio::g_Name));
        m_Factory.Register<YSESceneRenderer>(StringToLower(YSEAudio::g_Name));

        vInitFactory();
    }

    ISceneRenderer* SceneRendererFactory::CreateSceneRenderer(IOutputSharedPointer pSystem, ResourceCache* pResourceCache)
    {
        ISceneRenderer* pRenderer = m_Factory.Create(pSystem->vGetName());
        LOG_ASSERT(pRenderer != nullptr && "Could not create the scene renderer for the output subsystem!");

        if (!pRenderer->vInit(pSystem, pResourceCache))
        {
            LOG_ERROR("Error initializing the output scene renderer!");
            SAFE_DELETE(pRenderer);

            return nullptr;
        }

        return pRenderer;
    }

    void SceneRendererFactory::vInitFactory()
    {

    }

}
