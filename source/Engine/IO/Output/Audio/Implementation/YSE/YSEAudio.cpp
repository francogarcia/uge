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

#include "YSEAudio.h"

#include "YSEAudioBuffer.h"
#include "YSEAudioResource.h"

namespace uge
{
    YSEAudio::YSEAudio()
    {

    }

    YSEAudio::~YSEAudio()
    {

    }

    bool YSEAudio::vIsActive()
    {
        return m_bIsInitialized;
    }

    void YSEAudio::vUpdate(unsigned long timeElapsed)
    {
        assert(m_bIsInitialized);

        YSE::System.update();
    }

    IAudioBuffer* YSEAudio::vInitAudioBuffer(ResourceHandleSharedPointer pHandle)
    {
        assert(m_bIsInitialized);

        SoundResourceExtraDataSharedPointer pExtraData = std::static_pointer_cast<SoundResourceExtraData>(pHandle->GetExtraData());

        switch (pExtraData->GetAudioType())
        {
        case AudioFileType::OGG:
        case AudioFileType::WAVE:
            break;

        case AudioFileType::MIDI:
        case AudioFileType::FLAC:
        case AudioFileType::AIFF:
        case AudioFileType::RAW:
            assert("Supported but not implemented yet!");
            break; // Supported types.

        case AudioFileType::MP3:
            assert(0 && "MP3 is not supported!");
            return nullptr;
            
        default:
            assert(0 && "Unknown audio type!");
            return nullptr;
        }

        // FIXME : Read file here -> resource name...
        IAudioBuffer* pAudioBuffer = LIB_NEW YSEAudioBuffer(pHandle);
        m_Samples.push_front(pAudioBuffer);

        return pAudioBuffer;
    }
    
    void YSEAudio::vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer)
    {
        assert(m_bIsInitialized);

        pAudioBuffer->vStop();
        m_Samples.remove(pAudioBuffer);
    }
    
    bool YSEAudio::vInit()
    {
        if (m_bIsInitialized)
        {
            return true;
        }

        m_Samples.clear();
        m_bIsInitialized = YSE::System.init();

        return m_bIsInitialized;
    }

    bool YSEAudio::vDestroy()
    {
        if (m_bIsInitialized)
        {
            YSE::System.close();
            m_bIsInitialized = false;
        }

        return true;
    }
}
