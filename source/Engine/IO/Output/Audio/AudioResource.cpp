/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "AudioResource.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    unsigned int GetAudioLengthInSamples(const unsigned int bufferSizeBytes,
                                         const unsigned int channels,
                                         const unsigned int bitsPerSample)
    {
        assert(bufferSizeBytes != 0);
        assert(channels != 0);
        assert(bitsPerSample != 0);

        const unsigned int bitsToByte = 8u;

        return bufferSizeBytes * bitsToByte / (channels * bitsPerSample);
    }

    unsigned int GetAudioLengthInSeconds(const unsigned int bufferSizeBytes,
                                         const unsigned int channels,
                                         const unsigned int bitsPerSample,
                                         const unsigned int frequency)
    {
        unsigned int lengthInSamples = GetAudioLengthInSamples(bufferSizeBytes,
                                       channels,
                                       bitsPerSample);
        unsigned int audioLengthSeconds = (static_cast<float>(lengthInSamples) / static_cast<float>(frequency));

        return audioLengthSeconds;
    }

    unsigned int GetAudioLengthInMilliseconds(const unsigned int bufferSizeBytes,
            const unsigned int channels,
            const unsigned int bitsPerSample,
            const unsigned int frequency)
    {
        const unsigned int secondsToMilliseconds = 1000u;

        // Duplicate from GetAudioLengthInSeconds() to reduce precision loss.
        unsigned int lengthInSamples = GetAudioLengthInSamples(bufferSizeBytes,
                                       channels,
                                       bitsPerSample);
        unsigned int audioLengthSeconds = (static_cast<float>(lengthInSamples) / static_cast<float>(frequency));

        return secondsToMilliseconds * GetAudioLengthInSeconds(bufferSizeBytes,
                channels,
                bitsPerSample,
                frequency);
    }

    WaveResourceLoader::WaveResourceLoader()
    {

    }

    WaveResourceLoader::~WaveResourceLoader()
    {

    }

    std::string WaveResourceLoader::vGetPattern()
    {
        return "*.wav";
    }

    bool WaveResourceLoader::vUseRawFile()
    {
        return false;
    }

    bool WaveResourceLoader::vDiscardRawBufferAfterLoad()
    {
        return true;
    }

    OggResourceLoader::OggResourceLoader()
    {

    }

    OggResourceLoader::~OggResourceLoader()
    {

    }

    std::string OggResourceLoader::vGetPattern()
    {
        return "*.ogg";
    }

    bool OggResourceLoader::vUseRawFile()
    {
        return false;
    }

    bool OggResourceLoader::vDiscardRawBufferAfterLoad()
    {
        return true;
    }

}
