#pragma once

#include <Core/Resource/ResourceCache.h>
#include <IO/Output/IOutput.h>

#include "AudioBuffer.h"
#include "AudioResource.h"
#include "AudioTypes.h"

namespace uge
{

    class AudioResourceExtraData;
    class IAudio;
    typedef std::shared_ptr<IAudio> IAudioSharedPointer;
    typedef std::weak_ptr<IAudio> IAudioWeakPointer;

    class IAudio : public IOutput
    {
    public:
        virtual ~IAudio();

        virtual bool vIsActive() = 0;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) = 0;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) = 0;

        virtual void vUpdate(unsigned long timeElapsed) = 0;

        virtual void vStopAllSounds() = 0;
        virtual void vPauseAllSounds() = 0;
        virtual void vResumeAllSounds() = 0;

        virtual bool vInit() = 0;
        virtual bool vDestroy() = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

    class Audio : public IAudio
    {
    public:
        Audio();
        virtual ~Audio();

        virtual bool vIsActive() = 0;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) = 0;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) = 0;

        virtual void vUpdate(unsigned long timeElapsed) = 0;

        virtual void vStopAllSounds() override;
        virtual void vPauseAllSounds() override;
        virtual void vResumeAllSounds() override;

        virtual bool vInit() = 0;
        virtual bool vDestroy() override;
        bool HasSoundCard();
        bool IsPaused() const;

        virtual OutputType vGetOutputType() const override
        {
            return OutputType::Aural;
        }

    protected:
        typedef std::list<IAudioBuffer*> AudioBufferList;

        AudioBufferList m_Samples;
        bool m_bAllPaused;
        bool m_bIsInitialized;
    };

}
