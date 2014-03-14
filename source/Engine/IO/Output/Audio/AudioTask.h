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
