#pragma once

#include <cTinyOAL.h>

#include <IO/Output/Audio/AudioResource.h>

namespace uge
{
    class OpenALSoftWaveResourceLoader : public WaveResourceLoader
    {
    public:
        OpenALSoftWaveResourceLoader();
        ~OpenALSoftWaveResourceLoader();

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;
    };

    class OpenALSoftOggResourceLoader : public OggResourceLoader
    {
    public:
        OpenALSoftOggResourceLoader();
        ~OpenALSoftOggResourceLoader();

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;
    };
}
