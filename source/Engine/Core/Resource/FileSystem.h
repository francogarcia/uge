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

#pragma once

#include "Resource.h"
#include "ResourceCache.h"

namespace uge
{

    class FileSystemResourceFile : public IResourceFile
    {
    public:
        FileSystemResourceFile();
        ~FileSystemResourceFile();

        bool vOpen() override;
        int vGetRawResourceSize(const Resource& resource) override;
        int vGetRawResource(const Resource& resource, char* pData) override;
        int vGetNumberOfResources() const override;
        std::string vGetResourceName(int resourceNumber) const override;
        bool vIsUsingDevelopmentDirectories() const override;

    private:
    };

    class FileSystemResourceExtraData : public IResourceExtraData
    {
    public:
        std::string vToString() override
        {
            return "FileSystemResourceExtraData";
        }

    private:
        PHYSFS_File* m_pFile;
    };

    class FileSystemResourceLoader : public IResourceLoader
    {
    public:
        std::string vGetPattern() override
        {
            return "*.zip";
        }
        bool vUseRawFile() override
        {
            return false;
        }
        bool vDiscardRawBufferAfterLoad() override
        {
            return true;
        }
        bool vAddNullZero() override
        {
            return false;
        }
        unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override
        {
            return rawSize;
        }
        bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle);
    };


    class FileSystem
    {
    public:
        enum class MountPosition : unsigned char
        {
            Prepend = 0,
            Append = 1
        };

        enum class Mode : unsigned char
        {
            Read = 0,
            Write = 1
        };

        FileSystem();
        ~FileSystem();

        void Init(const char* const pProgramName);
        void Destroy();

        void Mount(const std::string& path, const std::string& mountPoint, const MountPosition position);

        bool ResourceExists(const std::string& resourseName);

        bool OpenResorce(const std::string& resourceName);


    private:

    };

    /* // TODO: Finish the wrapper to PhysFS.
    int main(int argc, char* argv[])
    {
        debug::log::Init("data/debug/LogConfig.xml");

        const char* pSystemProgramName = argv[0];
        if (PHYSFS_init(pSystemProgramName) == 0)
        {
            // Erro
            LOG_ERROR(PHYSFS_getLastError());
        }

        //PHYSFS_mount("data/data.zip", "/", 1); // Mount a file.
        PHYSFS_mount("data/", "/", 1); // Mount an entire directory.

        if (PHYSFS_exists("save/foo.txt") == 0)
        {
            // Erro
            LOG_ERROR(PHYSFS_getLastError());
        }

        PHYSFS_File* pFile = PHYSFS_openRead("save/foo.txt");
        if (pFile == nullptr)
        {
            // Erro
            LOG_ERROR(PHYSFS_getLastError());
        }

        PHYSFS_sint64 fileSize = PHYSFS_fileLength(pFile);

        char* pBuffer = new char[fileSize + 1];
        int lenght_read = PHYSFS_read(pFile, pBuffer, 1, fileSize);
        assert(lenght_read > 0 && "Failed to read the data!");
        pBuffer[lenght_read] = '\0';

        printf("%s", pBuffer);

        if (PHYSFS_close(pFile) <= 0)
        {
            // Erro
            LOG_ERROR(PHYSFS_getLastError());
        }
        pFile = nullptr;

        SAFE_DELETE_ARRAY(pBuffer);
        SAFE_DELETE(pFile);

        if (PHYSFS_deinit() == 0)
        {
            // Erro
            LOG_ERROR(PHYSFS_getLastError());
        }

        debug::log::Destroy();

        return 0;
    }

    */

}
