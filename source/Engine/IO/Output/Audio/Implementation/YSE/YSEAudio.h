#pragma once

#include <yse.hpp>

#include <IO/Output/Audio/Audio.h>

namespace uge
{
    class YSEAudio : public Audio
    {
    public:
        YSEAudio();
        ~YSEAudio();

        virtual bool vIsActive() override;

        virtual void vUpdate(unsigned long timeElapsed) override;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) override;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) override;

        virtual bool vInit() override;
        virtual bool vDestroy() override;
    
    private:

    };
}
