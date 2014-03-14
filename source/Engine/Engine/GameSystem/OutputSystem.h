#pragma once

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/AudioTask.h>

#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
    class OutputSystem
    {
    public:
        OutputSystem();
        ~OutputSystem();

        bool Init(IGraphicsSharedPointer pGraphics, IAudioSharedPointer pAudio);
        void PostInit();

        bool Destroy();

        void Update(unsigned long timeElapsed);

        bool PreRender();

        bool PostRender();

        bool SetGraphicsSystem(IGraphicsSharedPointer pGraphics);

        bool SetAudioSystem(IAudioSharedPointer pAudio);

        IGraphicsSharedPointer GetGraphics();

        IAudioSharedPointer GetAudio();

    private:
        bool DestroyGraphicsSystem();

        bool DestroyAudioSystem();

    private:
        // Systems
        IGraphicsSharedPointer m_pGraphics;
        IAudioSharedPointer m_pAudio;
    };
}
