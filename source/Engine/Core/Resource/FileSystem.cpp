#include "GameEngineStd.h"

#include "FileSystem.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    FileSystemResourceFile::FileSystemResourceFile()
    {

    }

    FileSystemResourceFile::~FileSystemResourceFile()
    {

    }

    bool FileSystemResourceFile::vOpen()
    {
        LOG_FATAL("Not implemented yet.");

        return false;
    }

    int FileSystemResourceFile::vGetRawResourceSize(const Resource& resource)
    {
        LOG_FATAL("Not implemented yet.");

        return -1;
    }

    int FileSystemResourceFile::vGetRawResource(const Resource& resource, char* pData)
    {
        LOG_FATAL("Not implemented yet.");

        return -1;
    }

    int FileSystemResourceFile::vGetNumberOfResources() const
    {
        LOG_FATAL("Not implemented yet.");

        return -1;
    }

    std::string FileSystemResourceFile::vGetResourceName(int resourceNumber) const
    {
        LOG_FATAL("Not implemented yet.");

        return "";
    }

    bool FileSystemResourceFile::vIsUsingDevelopmentDirectories() const
    {
        LOG_FATAL("Not implemented yet.");

        return false;
    }

}
