/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#include "GameEngineStd.h"

#include "AudioTask.h"

#include <Utilities/Debug/Logger.h>

#include "AudioResource.h"

namespace uge
{

    SoundTask::SoundTask(IAudioWeakPointer pAudio, ResourceHandleSharedPointer pSoundResource,
        float fVolume, bool bLoop) : m_pAudio(pAudio), m_pResource(pSoundResource),
          m_fVolume(fVolume), m_bIsLooping(bLoop), m_pAudioBuffer(nullptr)
    {
        InitializeVolume();
    }

    SoundTask::SoundTask() : m_pResource(nullptr), m_fVolume(100),
        m_bIsLooping(false), m_pAudioBuffer(nullptr)
    {
        m_pAudio.reset();
    }

    SoundTask::~SoundTask()
    {
        if (IsPlaying())
        {
            Stop();
        }

        if (m_pAudioBuffer != nullptr)
        {
            IAudioSharedPointer pAudio = m_pAudio.lock();
            LOG_ASSERT((pAudio != nullptr) && "Invalid value for the volume");
            pAudio->vReleaseAudioBuffer(m_pAudioBuffer.get());
        }
    }

    void SoundTask::Play(const float fVolume, const bool bLoop)
    {
        LOG_ASSERT(fVolume >= 0.0f && fVolume <= 1.0f && "Invalid value for the volume");

        if (m_pAudioBuffer == nullptr)
        {
            return;
        }

        m_pAudioBuffer->vPlay(fVolume, bLoop);
    }

    void SoundTask::Pause()
    {
        if (m_pAudioBuffer == nullptr)
        {
            return;
        }

        m_pAudioBuffer->vTogglePause();
    }

    void SoundTask::Stop()
    {
        if (m_pAudioBuffer == nullptr)
        {
            return;
        }

        m_pAudioBuffer->vStop();
    }

    void SoundTask::SetVolume(float fVolume)
    {
        if (m_pAudioBuffer == nullptr)
        {
            return;
        }

        LOG_ASSERT(fVolume >= 0.0f && fVolume <= 1.0f && "Invalid value for the volume");

        m_fVolume = fVolume; // XXX duplicated?
        m_pAudioBuffer->vSetVolume(fVolume);
    }

    float SoundTask::GetVolume()
    {
        if (m_pAudioBuffer == nullptr)
        {
            return 0.0f;
        }

        m_fVolume = m_pAudioBuffer->vGetVolume();

        return m_fVolume;
    }

    int SoundTask::GetLength() const
    {
        if ((m_pResource != nullptr) && (m_pResource->GetExtraData() != nullptr))
        {
            std::shared_ptr<SoundResourceExtraData> pExtraData = std::static_pointer_cast<SoundResourceExtraData>(m_pResource->GetExtraData());

            return pExtraData->GetLength();
        }

        return 0;
    }

    bool SoundTask::IsSoundValid() const
    {
        return (m_pResource != nullptr);
    }

    bool SoundTask::IsPlaying()
    {
        if ((m_pResource == nullptr) || (m_pAudioBuffer == nullptr))
        {
            return false;
        }

        return m_pAudioBuffer->vIsPlaying();
    }

    bool SoundTask::IsLooping() const
    {
        return (m_pAudioBuffer && m_pAudioBuffer->vIsLooping());
    }

    float SoundTask::GetProgress()
    {
        if (m_pAudioBuffer == nullptr)
        {
            return 0.0f;
        }

        return m_pAudioBuffer->vGetProgress();
    }

    void SoundTask::vOnInit()
    {
        Task::vOnInit();

        if ((m_pResource == nullptr) || (m_pResource->GetExtraData() == nullptr))
        {
            return;
        }

        IAudioSharedPointer pAudio = m_pAudio.lock();
        LOG_ASSERT((pAudio != nullptr) && "Invalid value for the volume");
        pAudio->vReleaseAudioBuffer(m_pAudioBuffer.get());
        IAudioBuffer* pAudioBuffer = pAudio->vInitAudioBuffer(m_pResource);
        if (pAudioBuffer == nullptr)
        {
            Fail();

            return;
        }
        m_pAudioBuffer.reset(pAudioBuffer);

        Play(m_fVolume, m_bIsLooping);
    }

    void SoundTask::vOnUpdate(const unsigned long dt)
    {
        if (!IsPlaying())
        {
            Succeed();
        }
    }

    void SoundTask::InitializeVolume()
    {
        // Todo: read volume from a preference's file.
        LOG_FATAL("Not implemented yet!");
    }

}
