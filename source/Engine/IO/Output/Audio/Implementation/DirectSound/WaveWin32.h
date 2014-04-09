/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#pragma once

#include <Core/Resource/ResourceCache.h>

#include "Audio.h"

namespace uge
{

    class SoundResourceExtraData;
    class WaveResourceLoader;
    class OggResourceLoader;

    // FIXME: Remove this and add support to other platforms.
#ifdef _WIN32
#include <mmsystem.h>
#else
#error "Other platforms are not supported yet!"
#endif

    class SoundResourceExtraData : public IResourceExtraData
    {
        friend class WaveResourceLoader;
        friend class OggResourceLoader;

    public:
        SoundResourceExtraData();
        virtual ~SoundResourceExtraData();

        std::string vToString() override;

        AudioFileType GetSoundType();
        WAVEFORMATEX const* GetFormat();
        int GetLength() const;

    private:
        AudioFileType m_SoundType;
        bool m_bIsInitialized;
        WAVEFORMATEX m_WaveFormat;
        int m_SoundLength;
    };

    class WaveResourceLoader : public IResourceLoader
    {
    public:
        WaveResourceLoader();
        virtual ~WaveResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;

    protected:
        virtual bool vParseWave(char* pWaveStream, size_t length, ResourceHandleSharedPointer pHandle) = 0;
    };

    class OggResourceLoader : public IResourceLoader
    {
    public:
        OggResourceLoader();
        virtual ~OggResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;

    protected:
        virtual bool vParseOgg(char* pOggStream, size_t length, ResourceHandleSharedPointer pHandle) = 0;
    };

}
