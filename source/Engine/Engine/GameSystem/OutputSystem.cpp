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

#include "OutputSystem.h"

namespace uge
{
    OutputSystem::OutputSystem()
    {

    }

    OutputSystem::~OutputSystem()
    {

    }

    bool OutputSystem::Init(IGraphicsSharedPointer pGraphics, IAudioSharedPointer pAudio)
    {
        bool bSuccess = SetGraphicsSystem(pGraphics);
        bSuccess &= SetAudioSystem(pAudio);

        return bSuccess;
    }

    void OutputSystem::PostInit()
    {
        //m_pGraphics->vSetBackgroundColor(0, 0, 0, 0);
    }

    bool OutputSystem::Destroy()
    {
        bool bSuccess = DestroyGraphicsSystem();
        bSuccess &= DestroyAudioSystem();

        return bSuccess;
    }

    bool OutputSystem::PreRender()
    {
        bool bSuccess = m_pGraphics->vPreRender();

        return bSuccess;
    }

    void OutputSystem::Update(unsigned long timeElapsed)
    {
        m_pAudio->vUpdate(timeElapsed);
    }

    bool OutputSystem::PostRender()
    {
        bool bSuccess = m_pGraphics->vPostRender();

        return bSuccess;
    }

    bool OutputSystem::SetGraphicsSystem(IGraphicsSharedPointer pGraphics)
    {
        assert(pGraphics != nullptr && "Invalid graphics system!");
        m_pGraphics = pGraphics;

        return m_pGraphics->vInit();
    }

    bool OutputSystem::DestroyGraphicsSystem()
    {
        return m_pGraphics->vDestroy();
    }

    bool OutputSystem::SetAudioSystem(IAudioSharedPointer pAudio)
    {
        assert(pAudio != nullptr && "Invalid audio system!");
        m_pAudio = pAudio;

        return m_pAudio->vInit();
    }

    bool OutputSystem::DestroyAudioSystem()
    {
        return m_pAudio->vDestroy();
    }

    IGraphicsSharedPointer OutputSystem::GetGraphics()
    {
        return m_pGraphics;
    }

    IAudioSharedPointer OutputSystem::GetAudio()
    {
        return m_pAudio;
    }
}
