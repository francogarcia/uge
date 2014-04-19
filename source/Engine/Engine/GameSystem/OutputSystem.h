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

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/AudioTask.h>

#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
    class OutputSystem
    {
    public:
        OutputSystem();
        ~OutputSystem();

        bool Init(IGraphicsSharedPointer pGraphics, IAudioSharedPointer pAudio);
        void PostInit();

        bool Destroy();

        void Update(unsigned long timeElapsed);

        bool PreRender();

        bool PostRender();

        bool SetGraphicsSystem(IGraphicsSharedPointer pGraphics);

        bool SetAudioSystem(IAudioSharedPointer pAudio);

        IGraphicsSharedPointer GetGraphics();

        IAudioSharedPointer GetAudio();

    private:
        bool DestroyGraphicsSystem();

        bool DestroyAudioSystem();

    private:
        // Systems
        IGraphicsSharedPointer m_pGraphics;
        IAudioSharedPointer m_pAudio;
    };
}
