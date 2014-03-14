#pragma once

#include <yse.hpp>

#include <IO/Output/Audio/AudioResource.h>

namespace uge
{
    class YSEWaveResourceLoader : public WaveResourceLoader
    {
    public:
        YSEWaveResourceLoader();
        ~YSEWaveResourceLoader();

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;
    };

    class YSEOggResourceLoader : public OggResourceLoader
    {
    public:
        YSEOggResourceLoader();
        ~YSEOggResourceLoader();

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;
    };
}
