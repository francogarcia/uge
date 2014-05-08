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

#include "OutputSystemFactory.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

namespace uge
{

    OutputSystemFactory::OutputSystemFactory()
    {

    }

    OutputSystemFactory::~OutputSystemFactory()
    {

    }

    void OutputSystemFactory::Init()
    {
        m_Factory.Register<OgreGraphics>(StringToLower(OgreGraphics::g_Name));
        m_Factory.Register<OpenALSoftAudio>(StringToLower(OpenALSoftAudio::g_Name));
        m_Factory.Register<YSEAudio>(StringToLower(YSEAudio::g_Name));

        vInitFactory();
    }

    IOutput* OutputSystemFactory::CreateOutputSubsystem(const std::string& systemName, const OutputSettings& outputSettings)
    {
        IOutput* pSystem = m_Factory.Create(systemName);
        if (!pSystem->vInit(outputSettings))
        {
            LOG_ERROR("Error initializing the output system!");
            SAFE_DELETE(pSystem);

            return nullptr;
        }

        return pSystem;
    }

    void OutputSystemFactory::vInitFactory()
    {

    }

}
