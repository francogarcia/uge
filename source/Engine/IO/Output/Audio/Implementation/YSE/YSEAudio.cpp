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
