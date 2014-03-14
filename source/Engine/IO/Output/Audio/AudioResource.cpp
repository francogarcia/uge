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
