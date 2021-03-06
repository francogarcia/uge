/*
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

#include "OpenALSoftAudio.h"

#include "OpenALSoftAudioBuffer.h"
#include "OpenALSoftAudioResource.h"

#include <Utilities/String/StringUtil.h>

namespace uge
{
    const char* OpenALSoftAudio::g_Name = "OpenAL-Soft";

    const unsigned int TOTAL_BUFFERS = 4u;

    OpenALSoftAudio::OpenALSoftAudio()
        : m_TotalBuffers(TOTAL_BUFFERS), m_pTinyOAL(nullptr), m_TotalSoundsBeingPlayed(0)
    {

    }

    OpenALSoftAudio::~OpenALSoftAudio()
    {

    }

    bool OpenALSoftAudio::vInit(const OutputSettings& outputSettings)
    {
        if (m_bIsInitialized)
        {
            return true;
        }

        OutputSettings::OutputSettingsData outputData = outputSettings.GetOutputSettingsData();
        const OutputSubsystemSettings::OutputSubsystemSettingsData& subsystemSettings
            = outputData.subsystems["openal-soft"].GetOutputSubsystemSettingsData();

        auto valueIt = subsystemSettings.settings.find("AudioBuffers");
        m_TotalBuffers = StringToUInt(valueIt->second);

        m_Samples.clear();

        // HRTF settings.
        //const ALCint frequency = 44100; // Hz, used by HRTF.
        //ALCint openAlLContext[] = { ALC_FREQUENCY, frequency, 0};
        //m_TinyOAL.
        
        m_pTinyOAL = LIB_NEW TinyOAL::cTinyOAL(m_TotalBuffers);
        assert(m_pTinyOAL);

        m_bIsInitialized = (m_pTinyOAL != nullptr);
        m_TotalSoundsBeingPlayed = 0;

        return m_bIsInitialized;
    }

    bool OpenALSoftAudio::vPostInit()
    {
        return true;
    }

    bool OpenALSoftAudio::vDestroy()
    {
        if (m_bIsInitialized)
        {
            // TinyOAL is destroyed by the destructor.
            SAFE_DELETE(m_pTinyOAL);
            m_bIsInitialized = false;
        }

        return true;
    }

    bool OpenALSoftAudio::vUpdate(unsigned long timeElapsed)
    {
        assert(m_bIsInitialized);

        m_TotalSoundsBeingPlayed = m_pTinyOAL->Update();

        return true;
    }

    bool OpenALSoftAudio::vPreRender()
    {
        return true;
    }

    bool OpenALSoftAudio::vRender()
    {
        return true;
    }

    bool OpenALSoftAudio::vPostRender()
    {
        return true;
    }

    bool OpenALSoftAudio::vIsActive()
    {
        return m_bIsInitialized;
    }

    IAudioBuffer* OpenALSoftAudio::vInitAudioBuffer(ResourceHandleSharedPointer pHandle)
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

        IAudioBuffer* pAudioBuffer = LIB_NEW OpenALSoftAudioBuffer(pHandle);
        m_Samples.push_front(pAudioBuffer);

        return pAudioBuffer;
    }
    
    void OpenALSoftAudio::vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer)
    {
        assert(m_bIsInitialized);

        pAudioBuffer->vStop();
        m_Samples.remove(pAudioBuffer);
    }
    
    const std::string OpenALSoftAudio::vGetName() const
    {
        return g_Name;
    }

}
