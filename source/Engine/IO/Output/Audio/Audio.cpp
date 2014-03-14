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
