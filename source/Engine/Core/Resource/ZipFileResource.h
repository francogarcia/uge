#pragma once

#include "Resource.h"

#include <Utilities/File/ZipFile.h>

namespace uge
{

    class ZipFileResource : public IResourceFile
    {
    public:
        /**
         *  Constructor.
         */
        ZipFileResource(const std::string& zipFileName);

        /**
         *  Destructor.
         */
        virtual ~ZipFileResource();

        /**
         *  Opens the resource file.
         * @return : should return true if successful, false otherwise.
         */
        virtual bool vOpen() override;

        /**
         *  Returns the size of the specified resource.
         * @param resource : resource to query the size.
         * @return : the size of the resource, in bytes.
         */
        virtual int vGetRawResourceSize(const Resource& resource) override;

        /**
         *  Loads the raw resource from the cache.
         * @param resource : resource to load.
         * @param pData : buffer to store the resource.
         * @return : the size of the resource, in bytes.
         */
        virtual int vGetRawResource(const Resource& resource, char* pData) override;

        /**
         *  Returns the total number of resources stored in this cache.
         * @return : number of resources stored.
         */
        virtual int vGetNumberOfResources() const override;

        /**
         *  Returns the name of the resource corresponding to the given number.
         * @param resourceNumber : index of the resource in this cache.
         * @return : the name of the resource.
         */
        virtual std::string vGetResourceName(int resourceNumber) const override;

        /**
         *  Tells if this resource is being used for development.
         *  The development directory allows to fake directory structures or to
         *  avoid compressing the data, allowing faster development.
         * @return : true if a development directory is being used, false otherwise.
         */
        virtual bool vIsUsingDevelopmentDirectories() const override;

    private:
        ZipFile* m_pZipFile;
        std::string m_FileName;
    };

    class ZipFileDevelopmentResource : public ZipFileResource
    {
    public:
        enum class Mode : unsigned char
        {
            Development,	// this mode checks the original asset directory for changes - helps during development
            Editor			// this mode only checks the original asset directory - the ZIP file is left unopened.
        };

        ZipFileDevelopmentResource(const std::string& zipFileName,
                                   const std::string& workingPath, Mode mode);

        virtual ~ZipFileDevelopmentResource();

        virtual bool vOpen() override;

        virtual int vGetRawResourceSize(const Resource& resource) override;

        virtual int vGetRawResource(const Resource& resource, char* pData) override;

        virtual int vGetNumberOfResources() const override;

        virtual std::string vGetResourceName(int resourceNumber) const override;

        virtual bool vIsUsingDevelopmentDirectories() const override;

        int Find(const std::string& fileName);

    protected:
        void ReadAssetsDirectory(std::wstring fileSpec);

        ZipContentsMap m_DirectoryContents;
        std::string m_FileName;
        std::string m_WorkingDirectory;

        // TODO: Windows only; make this multiplataform.
        std::vector<WIN32_FIND_DATAW> m_AssetFileInfo;
        Mode m_Mode;
    };

}
