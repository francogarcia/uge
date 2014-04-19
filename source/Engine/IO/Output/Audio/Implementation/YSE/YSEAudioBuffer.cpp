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

#include "YSEAudioBuffer.h"

#include <IO/Output/Audio/AudioResource.h>

namespace uge
{
    YSEAudioBuffer::YSEAudioBuffer(ResourceHandleSharedPointer pAudioBufferResource)
        : AudioBuffer(pAudioBufferResource), m_pAudioBuffer(nullptr)
    {
        std::shared_ptr<SoundResourceExtraData> pExtraData = std::static_pointer_cast<SoundResourceExtraData>(pAudioBufferResource->GetExtraData());
        m_pAudioBuffer = static_cast<YSE::sound*>(pExtraData->GetAudioData());
    }

    YSEAudioBuffer::~YSEAudioBuffer()
    {
        m_pAudioBuffer->release();
        SAFE_DELETE(m_pAudioBuffer);
    }

    void* YSEAudioBuffer::vGet()
    {
        if (!vOnRestore())
        {
            return nullptr;
        }

        return m_pAudioBuffer;
    }

    bool YSEAudioBuffer::vOnRestore()
    {
        return true;
    }

    bool YSEAudioBuffer::vPlay(float fVolume, bool bLoop)
    {
        // TODO: reference the audio system.
        if (m_pAudioBuffer->playing())
        {
            m_pAudioBuffer->pause();
            m_pAudioBuffer->restart();
        }

        m_fVolume = fVolume;
        m_bIsLooping = bLoop;
        m_bIsPaused = false;

        m_pAudioBuffer->volume(fVolume);
        m_pAudioBuffer->loop(bLoop);
        m_pAudioBuffer->play();

        return true;
    }

    bool YSEAudioBuffer::vPause()
    {
        m_pAudioBuffer->pause();
        m_bIsPaused = true;

        return true;
    }

    bool YSEAudioBuffer::vStop()
    {
        m_pAudioBuffer->stop();
        m_bIsPaused = true;

        return true;
    }

    bool YSEAudioBuffer::vResume()
    {
        if (m_pAudioBuffer->paused())
        {
            m_bIsPaused = true;
            m_pAudioBuffer->toggle();
        }

        return true;
    }

    bool YSEAudioBuffer::vTogglePause()
    {
        m_pAudioBuffer->toggle();
        m_bIsPaused = !m_bIsPaused;

        return true;
    }

    bool YSEAudioBuffer::vIsPlaying()
    {
        // playing() does not change until a update(). Thus, paused is used.
        return (m_pAudioBuffer->playing() || (!m_bIsPaused));
    }

    bool YSEAudioBuffer::vIsLooping() const
    {
        return m_pAudioBuffer->loop();
    }

    void YSEAudioBuffer::vSetVolume(float fVolume)
    {
        assert(fVolume >= 0.0f && fVolume <= 1.0f);

        m_pAudioBuffer->volume(fVolume);
        m_fVolume = fVolume;
    }

    float YSEAudioBuffer::vGetVolume() const
    {
        return m_fVolume;
    }

    void YSEAudioBuffer::vSetProgress(float fAudioPosition)
    {
        m_pAudioBuffer->time(fAudioPosition);
    }

    float YSEAudioBuffer::vGetProgress()
    {
        return (m_pAudioBuffer->time() / m_pAudioBuffer->length());
    }

    void YSEAudioBuffer::vSetPosition(const Vector3& position)
    {
        m_Position = position;
        m_pAudioBuffer->pos(YSE::Vec(position.x, position.y, position.z));
    }
}
