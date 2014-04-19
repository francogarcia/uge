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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include <Core/Resource/ResourceCache.h>
#include <Core/Task/Task.h>

#include "Audio.h"

namespace uge
{

    class SoundTask : public Task
    {
    public:
        SoundTask(IAudioWeakPointer pAudio, ResourceHandleSharedPointer pSoundResource, float fVolume = 1.0f, bool bLoop = false);
        ~SoundTask();

        void Play(const float fVolume, const bool bLoop);
        void Pause();
        void Stop();

        void SetVolume(float fVolume);
        float GetVolume();
        int GetLengthInMilliseconds() const;

        bool IsSoundValid() const;

        bool IsPlaying();
        bool IsLooping() const;

        float GetProgress();

    protected:
        SoundTask();

        virtual void vOnInit() override;
        virtual void vOnUpdate(const unsigned long dt) override;

        void InitializeVolume();

        ResourceHandleSharedPointer m_pResource;
        std::shared_ptr<IAudioBuffer> m_pAudioBuffer;

        // TODO/XXX: duplicated so far, will be useful when InitializeVolume is implemented.
        float m_fVolume;
        bool m_bIsLooping;

        IAudioWeakPointer m_pAudio;
    };

    // TODO: finish this after graphics are implemented.
    class SoundEffectTask : public SoundTask
    {

    };

    // Background
    class AmbientSoundEffectTask : public SoundTask
    {

    };

    class MusicTask : public SoundTask
    {

    };

    class SpeechTask : public SoundTask
    {

    };

}
