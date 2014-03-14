#pragma once

//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alext.h>

#include <cTinyOAL.h>

#include <IO/Output/Audio/Audio.h>

namespace uge
{
    class OpenALSoftAudio : public Audio
    {
    public:
        OpenALSoftAudio(unsigned int totalBuffers = 4);
        ~OpenALSoftAudio();

        virtual bool vIsActive() override;

        virtual void vUpdate(unsigned long timeElapsed) override;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) override;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) override;

        virtual bool vInit() override;
        virtual bool vDestroy() override;

    private:
        TinyOAL::cTinyOAL* m_pTinyOAL;
        unsigned int m_TotalBuffers;
        unsigned int m_TotalSoundsBeingPlayed;
    };
}
