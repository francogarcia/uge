#pragma once

#include <cTinyOAL.h>

#include <IO/Output/Audio/AudioBuffer.h>

namespace uge
{
    class OpenALSoftAudioBuffer : public AudioBuffer
    {
    public:
        OpenALSoftAudioBuffer(ResourceHandleSharedPointer pAudioBufferResource);
        ~OpenALSoftAudioBuffer();

        virtual void* vGet() override;
        virtual bool vOnRestore() override;

        virtual bool vPlay(float fVolume, bool bLoop) override;
        virtual bool vPause() override;
        virtual bool vStop() override;
        virtual bool vResume() override;

        virtual bool vTogglePause() override;

        virtual bool vIsPlaying() override;
        virtual bool vIsLooping() const override;

        virtual void vSetVolume(float fVolume) override;
        virtual float vGetVolume() const override;
 
        virtual void vSetProgress(float fAudioPosition) override;
        virtual float vGetProgress() override;

        virtual void vSetPosition(const Vector3& position) override;

    private:
        TinyOAL::cAudioResource* m_pAudioBuffer;
        TinyOAL::cAudio* m_pAudio;

        unsigned int m_AudioLengthSamples;
    };
}
