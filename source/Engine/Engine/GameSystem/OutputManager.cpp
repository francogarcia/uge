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

#include "OutputManager.h"

namespace uge
{
    OutputManager::OutputManager()
    {

    }

    OutputManager::~OutputManager()
    {

    }

    bool OutputManager::Init(IGraphicsSharedPointer pGraphics, IAudioSharedPointer pAudio)
    {
        bool bSuccess = SetGraphicsSystem(pGraphics);
        bSuccess &= SetAudioSystem(pAudio);

        return bSuccess;
    }

    void OutputManager::PostInit()
    {
        //m_pGraphics->vSetBackgroundColor(0, 0, 0, 0);
    }

    bool OutputManager::Destroy()
    {
        bool bSuccess = DestroyGraphicsSystem();
        bSuccess &= DestroyAudioSystem();

        return bSuccess;
    }

    bool OutputManager::PreRender()
    {
        bool bSuccess = m_pGraphics->vPreRender();

        return bSuccess;
    }

    void OutputManager::Update(unsigned long timeElapsed)
    {
        m_pAudio->vUpdate(timeElapsed);
    }

    bool OutputManager::PostRender()
    {
        bool bSuccess = m_pGraphics->vPostRender();

        return bSuccess;
    }

    bool OutputManager::SetGraphicsSystem(IGraphicsSharedPointer pGraphics)
    {
        assert(pGraphics != nullptr && "Invalid graphics system!");
        m_pGraphics = pGraphics;

        return m_pGraphics->vInit();
    }

    bool OutputManager::DestroyGraphicsSystem()
    {
        return m_pGraphics->vDestroy();
    }

    bool OutputManager::SetAudioSystem(IAudioSharedPointer pAudio)
    {
        assert(pAudio != nullptr && "Invalid audio system!");
        m_pAudio = pAudio;

        return m_pAudio->vInit();
    }

    bool OutputManager::DestroyAudioSystem()
    {
        return m_pAudio->vDestroy();
    }

    IGraphicsSharedPointer OutputManager::GetGraphics()
    {
        return m_pGraphics;
    }

    IAudioSharedPointer OutputManager::GetAudio()
    {
        return m_pAudio;
    }
}
