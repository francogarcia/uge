#pragma once

#include "Resource.h"
#include "ResourceCache.h"

#include <Utilities/File/XMLFile.h>

namespace uge
{

    class XMLResourceExtraData : public IResourceExtraData
    {
    public:
        XMLResourceExtraData();

        ~XMLResourceExtraData();

        std::string vToString() override;

        bool LoadXML(const char* pXMLBuffer);

        bool LoadXML(std::string& xmlBuffer);

        uge::XMLElement GetRootElement();

    private:
        uge::XMLFile m_XMLFile;
    };

    class XMLResourceLoader : public IResourceLoader
    {
    public:
        XMLResourceLoader();

        ~XMLResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;

        static uge::XMLElement LoadAndReturnRootElement(const char* pXMLBuffer);
        static uge::XMLElement LoadAndReturnRootElement(std::string& xmlBuffer);

        static IResourceLoaderSharedPointer CreateLoader();
    };

}
