#include "GameEngineStd.h"

#include "OpenALSoftAudio.h"

#include "OpenALSoftAudioBuffer.h"
#include "OpenALSoftAudioResource.h"

namespace uge
{
    OpenALSoftAudio::OpenALSoftAudio(unsigned int totalBuffers)
        : m_TotalBuffers(totalBuffers), m_pTinyOAL(nullptr), m_TotalSoundsBeingPlayed(0)
    {
        assert(totalBuffers > 0);
    }

    OpenALSoftAudio::~OpenALSoftAudio()
    {

    }

    bool OpenALSoftAudio::vIsActive()
    {
        return m_bIsInitialized;
    }

    void OpenALSoftAudio::vUpdate(unsigned long timeElapsed)
    {
        assert(m_bIsInitialized);

        m_TotalSoundsBeingPlayed = m_pTinyOAL->Update();
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
    
    bool OpenALSoftAudio::vInit()
    {
        if (m_bIsInitialized)
        {
            return true;
        }

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
}
