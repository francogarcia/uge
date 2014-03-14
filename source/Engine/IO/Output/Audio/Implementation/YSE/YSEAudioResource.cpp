#include "GameEngineStd.h"

#include "YSEAudioResource.h"

namespace uge
{
    YSEWaveResourceLoader::YSEWaveResourceLoader()
    {

    }

    YSEWaveResourceLoader::~YSEWaveResourceLoader()
    {

    }

    unsigned int YSEWaveResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool YSEWaveResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        std::shared_ptr<SoundResourceExtraData> pExtraData = std::shared_ptr<SoundResourceExtraData>(LIB_NEW SoundResourceExtraData());
        pResourceHandle->SetExtraData(pExtraData);

        std::string waveFilename = pResourceHandle->GetName();
        YSE::sound* pSound = LIB_NEW(YSE::sound);
        pSound->create(waveFilename.c_str());
        WaveResourceLoader::SetResourceExtraData(pExtraData, pSound, pSound->length());

        return pSound->valid();
    }

    YSEOggResourceLoader::YSEOggResourceLoader()
    {

    }

    YSEOggResourceLoader::~YSEOggResourceLoader()
    {

    }

    unsigned int YSEOggResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool YSEOggResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        std::shared_ptr<SoundResourceExtraData> pExtraData = std::shared_ptr<SoundResourceExtraData>(LIB_NEW SoundResourceExtraData());
        pResourceHandle->SetExtraData(pExtraData);

        std::string oggFilename = pResourceHandle->GetName();
        YSE::sound* pSound = new YSE::sound;
        pSound->create(oggFilename.c_str());
        OggResourceLoader::SetResourceExtraData(pExtraData, pSound, pSound->length());

        return pSound->valid();
    }
}
