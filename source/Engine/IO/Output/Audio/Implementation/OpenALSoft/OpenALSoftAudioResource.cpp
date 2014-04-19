/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 */

#include "GameEngineStd.h"

#include "OpenALSoftAudioResource.h"

namespace uge
{
    OpenALSoftWaveResourceLoader::OpenALSoftWaveResourceLoader()
    {

    }

    OpenALSoftWaveResourceLoader::~OpenALSoftWaveResourceLoader()
    {

    }

    unsigned int OpenALSoftWaveResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool OpenALSoftWaveResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        std::shared_ptr<SoundResourceExtraData> pExtraData = std::shared_ptr<SoundResourceExtraData>(LIB_NEW SoundResourceExtraData());
        pResourceHandle->SetExtraData(pExtraData);

        const long long noLoop = -1LL;
        TinyOAL::cAudioResource* pAudioResource = TinyOAL::cAudioResource::Create(pRawBuffer, rawSize, TinyOAL::TINYOAL_COPYINTOMEMORY, noLoop);

        const unsigned int bufferSize = pAudioResource->GetBufSize();
        const unsigned int channels = pAudioResource->GetChannels();
        const unsigned int bitsPerSample = pAudioResource->GetBitsPerSample();
        const unsigned int frequency = pAudioResource->GetFreq();

        unsigned int audioLengthMilliseconds = GetAudioLengthInMilliseconds(bufferSize,
                                               channels, bitsPerSample, frequency);

        WaveResourceLoader::SetResourceExtraData(pExtraData, pAudioResource, audioLengthMilliseconds);

        return (pAudioResource != nullptr);
    }

    OpenALSoftOggResourceLoader::OpenALSoftOggResourceLoader()
    {

    }

    OpenALSoftOggResourceLoader::~OpenALSoftOggResourceLoader()
    {

    }

    unsigned int OpenALSoftOggResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool OpenALSoftOggResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        std::shared_ptr<SoundResourceExtraData> pExtraData = std::shared_ptr<SoundResourceExtraData>(LIB_NEW SoundResourceExtraData());
        pResourceHandle->SetExtraData(pExtraData);

        const long long noLoop = -1LL;
        TinyOAL::cAudioResource* pAudioResource = TinyOAL::cAudioResource::Create(pRawBuffer, rawSize, TinyOAL::TINYOAL_COPYINTOMEMORY, noLoop);
        //TinyOAL::cAudioResource* pAudioResource = TinyOAL::cAudioResource::Create(pResourceHandle->GetName().c_str(), (TinyOAL::TINYOAL_FLAG) TinyOAL::TINYOAL_COPYINTOMEMORY, noLoop);

        const unsigned int bufferSize = pAudioResource->GetBufSize();
        const unsigned int channels = pAudioResource->GetChannels();
        const unsigned int bitsPerSample = pAudioResource->GetBitsPerSample();
        const unsigned int frequency = pAudioResource->GetFreq();

        unsigned int audioLengthMilliseconds = GetAudioLengthInMilliseconds(bufferSize,
                                               channels, bitsPerSample, frequency);

        OggResourceLoader::SetResourceExtraData(pExtraData, pAudioResource, audioLengthMilliseconds);

        return (pAudioResource != nullptr);
    }
}
