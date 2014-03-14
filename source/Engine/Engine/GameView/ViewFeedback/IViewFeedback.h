#pragma once

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
    class IViewFeedback
    {
    public:
        IViewFeedback();
        virtual ~IViewFeedback();

        virtual bool vInit(const std::string& resourceFileName) = 0;

        virtual void vSetAudioSystem(IAudioWeakPointer pAudioSystem);
        virtual void vSetGraphicsSystem(IGraphicsWeakPointer pGraphicsSystem);
    };
}
