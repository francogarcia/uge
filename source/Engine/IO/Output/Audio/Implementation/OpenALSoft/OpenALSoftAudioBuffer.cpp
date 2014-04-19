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

#include "OpenALSoftAudioBuffer.h"

#include <IO/Output/Audio/AudioResource.h>

namespace uge
{
    OpenALSoftAudioBuffer::OpenALSoftAudioBuffer(ResourceHandleSharedPointer pAudioBufferResource)
        : AudioBuffer(pAudioBufferResource), m_pAudioBuffer(nullptr), m_pAudio(nullptr),
          m_AudioLengthSamples(0u)
    {
        std::shared_ptr<SoundResourceExtraData> pExtraData = std::static_pointer_cast<SoundResourceExtraData>(pAudioBufferResource->GetExtraData());
        m_pAudioBuffer = static_cast<TinyOAL::cAudioResource*>(pExtraData->GetAudioData());

        m_pAudio = LIB_NEW TinyOAL::cAudio(m_pAudioBuffer);

        const unsigned int bufferSize = m_pAudioBuffer->GetBufSize();
        const unsigned int channels = m_pAudioBuffer->GetChannels();
        const unsigned int bitsPerSample = m_pAudioBuffer->GetBitsPerSample();
        m_AudioLengthSamples = GetAudioLengthInSamples(bufferSize, channels, bitsPerSample);
    }

    OpenALSoftAudioBuffer::~OpenALSoftAudioBuffer()
    {
        SAFE_DELETE(m_pAudio);

        //SAFE_DELETE(m_pAudioBuffer);
        m_pAudioBuffer = nullptr;
    }

    void* OpenALSoftAudioBuffer::vGet()
    {
        if (!vOnRestore())
        {
            return nullptr;
        }

        return m_pAudio;
    }

    bool OpenALSoftAudioBuffer::vOnRestore()
    {
        return true;
    }

    bool OpenALSoftAudioBuffer::vPlay(float fVolume, bool bLoop)
    {
        // TODO: reference the audio system.
        if (m_pAudio->IsPlaying())
        {
            m_pAudio->Stop();
        }

        m_fVolume = fVolume;
        m_bIsLooping = bLoop;
        m_bIsPaused = false;

        m_pAudio->SetVolume(fVolume);
        m_pAudio->SetLoopPoint(bLoop ? 0LL : -1LL);
        m_pAudio->Play();

        return true;
    }

    bool OpenALSoftAudioBuffer::vPause()
    {
        m_pAudio->Pause();
        m_bIsPaused = true;

        return true;
    }

    bool OpenALSoftAudioBuffer::vStop()
    {
        m_pAudio->Stop();
        m_bIsPaused = true;

        return true;
    }

    bool OpenALSoftAudioBuffer::vResume()
    {
        if (!m_pAudio->IsPlaying())
        {
            m_bIsPaused = true;
            m_pAudio->Play();
        }

        return true;
    }

    bool OpenALSoftAudioBuffer::vTogglePause()
    {
        if (m_bIsPaused)
        {
            vResume();
        }
        else
        {
            vPause();
        }

        return true;
    }

    bool OpenALSoftAudioBuffer::vIsPlaying()
    {
        // playing() does not change until a update(). Thus, paused is used.
        return (m_pAudio->IsPlaying() || (!m_bIsPaused));
    }

    bool OpenALSoftAudioBuffer::vIsLooping() const
    {
        return (m_pAudio->GetLoopPoint() != -1LL);
    }

    void OpenALSoftAudioBuffer::vSetVolume(float fVolume)
    {
        assert(fVolume >= 0.0f && fVolume <= 1.0f);

        m_pAudio->SetVolume(fVolume);
        m_fVolume = fVolume;
    }

    float OpenALSoftAudioBuffer::vGetVolume() const
    {
        return m_fVolume;
    }

    void OpenALSoftAudioBuffer::vSetProgress(float fAudioPosition)
    {
        assert(fAudioPosition >= 0.0f && fAudioPosition <= 1.0f);

        m_pAudio->Stop();
        m_pAudio->Skip(static_cast<unsigned long>(fAudioPosition * m_AudioLengthSamples));

        // Resume the playback.
        if (!m_bIsPaused)
        {
            m_pAudio->Play();
        }
    }

    float OpenALSoftAudioBuffer::vGetProgress()
    {
        return (m_pAudio->IsWhere() / m_AudioLengthSamples);
    }

    void OpenALSoftAudioBuffer::vSetPosition(const Vector3& position)
    {
        m_Position = position;

        if (position.y == 0.0f && position.z == 0.0f)
        {
            // FIXME: Is this really needed? m_pAudio->SetPosition() says so. Check.
            const float fOpenALZ = 0.1f;
            m_pAudio->SetPosition(position.x, position.y, position.z + fOpenALZ);
        }
        else
        {
            m_pAudio->SetPosition(position.x, position.y, position.z);
        }
    }
}
