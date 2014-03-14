#pragma once

#include <Core/Resource/ResourceCache.h>

#include "Audio.h"

namespace uge
{

    class SoundResourceExtraData;
    typedef std::shared_ptr<SoundResourceExtraData> SoundResourceExtraDataSharedPointer;

    unsigned int GetAudioLengthInSamples(const unsigned int bufferSizeBytes,
                                         const unsigned int channels,
                                         const unsigned int bitsPerSample);

    unsigned int GetAudioLengthInSeconds(const unsigned int bufferSizeBytes,
                                         const unsigned int channels,
                                         const unsigned int bitsPerSample,
                                         const unsigned int frequency);

    unsigned int GetAudioLengthInMilliseconds(const unsigned int bufferSizeBytes,
            const unsigned int channels,
            const unsigned int bitsPerSample,
            const unsigned int frequency);


    class SoundResourceExtraData : public IResourceExtraData
    {
        friend class WaveResourceLoader;
        friend class OggResourceLoader;

    public:
        SoundResourceExtraData()
            : m_FileType(AudioFileType::UNKNOWN), m_SoundLengtMilliseconds(0u), m_pAudioData(nullptr)
        {

        }

        ~SoundResourceExtraData()
        {

        }

        std::string vToString()
        {
            return "SoundResourceExtraData";
        }

        AudioFileType GetAudioType()
        {
            return m_FileType;
        }

        unsigned int GetLengthInMilliseconds() const
        {
            return m_SoundLengtMilliseconds;
        }

        const void* GetAudioData() const
        {
            return m_pAudioData;
        }

        void* GetAudioData()
        {
            return m_pAudioData;
        }

    private:
        void SetSoundType(AudioFileType fileType)
        {
            m_FileType = fileType;
        }

        void SetAudioData(void* pAudioData)
        {
            assert(pAudioData != nullptr);

            m_pAudioData = pAudioData;
        }

        void SetLength(unsigned int audioLengthMilliseconds)
        {
            m_SoundLengtMilliseconds = audioLengthMilliseconds;
        }

        AudioFileType m_FileType;
        void* m_pAudioData;
        // In milliseconds.
        unsigned int m_SoundLengtMilliseconds;
    };

    class WaveResourceLoader : public IResourceLoader
    {
    public:
        WaveResourceLoader();
        virtual ~WaveResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) = 0;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) = 0;

    protected:
        void SetResourceExtraData(std::shared_ptr<SoundResourceExtraData> pExtraData,
                                  void* pAudioData, unsigned int soundLength)
        {
            pExtraData->SetSoundType(AudioFileType::OGG);
            pExtraData->SetAudioData(pAudioData);
            pExtraData->SetLength(soundLength);
        }
    };

    class OggResourceLoader : public IResourceLoader
    {
    public:
        OggResourceLoader();
        virtual ~OggResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) = 0;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) = 0;

    protected:
        void SetResourceExtraData(std::shared_ptr<SoundResourceExtraData> pExtraData,
                                  void* pAudioData, unsigned int soundLength)
        {
            pExtraData->SetSoundType(AudioFileType::OGG);
            pExtraData->SetAudioData(pAudioData);
            pExtraData->SetLength(soundLength);
        }
    };

}
