/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "Audio.h"

namespace uge
{

    IAudio::~IAudio()
    {

    }

    Audio::Audio() : m_bIsInitialized(false), m_bAllPaused(false)
    {

    }

    Audio::~Audio()
    {
        if (m_bIsInitialized)
        {
            vDestroy();
        }
    }

    void Audio::vStopAllSounds()
    {
        assert(m_bIsInitialized);

        for (IAudioBuffer* pAudioBuffer : m_Samples)
        {
            pAudioBuffer->vStop();
        }

        m_bAllPaused = false;
    }

    void Audio::vPauseAllSounds()
    {
        assert(m_bIsInitialized);

        for (IAudioBuffer* pAudioBuffer : m_Samples)
        {
            pAudioBuffer->vPause();
        }

        m_bAllPaused = true;
    }

    void Audio::vResumeAllSounds()
    {
        assert(m_bIsInitialized);

        for (IAudioBuffer* pAudioBuffer : m_Samples)
        {
            pAudioBuffer->vResume();
        }

        m_bAllPaused = false;
    }

    bool Audio::vDestroy()
    {
        assert(m_bIsInitialized);

        for (IAudioBuffer* pAudioBuffer : m_Samples)
        {
            pAudioBuffer->vStop();
        }

        m_Samples.clear();

        return true;
    }

    bool Audio::HasSoundCard()
    {
        return vIsActive();
    }

    bool Audio::IsPaused() const
    {
        return m_bAllPaused;
    }

}
