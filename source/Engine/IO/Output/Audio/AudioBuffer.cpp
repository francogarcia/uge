#include "GameEngineStd.h"

#include "Audio.h"

namespace uge
{

    IAudioBuffer::IAudioBuffer()
    {

    }

    IAudioBuffer::~IAudioBuffer()
    {

    }

    AudioBuffer::AudioBuffer(ResourceHandleSharedPointer pAudioBufferResource)
        : m_pResource(pAudioBufferResource), m_bIsPaused(true), m_bIsLooping(false), m_fVolume(0.0f), m_Position(0.0f, 0.0f, 0.0f)
    {

    }

    AudioBuffer::~AudioBuffer()
    {

    }

    ResourceHandleSharedPointer AudioBuffer::vGetResource()
    {
        return m_pResource;
    }

    bool AudioBuffer::vIsLooping() const
    {
        return m_bIsLooping;
    }

    float AudioBuffer::vGetVolume() const
    {
        return m_fVolume;
    }

    const Vector3& AudioBuffer::vGetPosition() const
    {
        return m_Position;
    }

}
