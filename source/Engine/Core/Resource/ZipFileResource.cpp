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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "ZipFileResource.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{

    ZipFileResource::ZipFileResource(const std::string& zipFileName) :
        m_pZipFile(nullptr), m_FileName(zipFileName)
    {

    }

    ZipFileResource::~ZipFileResource()
    {
        SAFE_DELETE(m_pZipFile);
    }

    bool ZipFileResource::vOpen()
    {
        m_pZipFile = new ZipFile;
        if (!m_pZipFile)
        {
            return false;
        }

        return m_pZipFile->Init(m_FileName);
    }

    int ZipFileResource::vGetRawResourceSize(const Resource& resource)
    {
        assert((m_pZipFile != nullptr) && "Resource wasn't loaded!");

        int resourceIndex = m_pZipFile->Find(resource.m_Name);
        if (resourceIndex < 0)
        {
            return -1;
        }

        return m_pZipFile->GetFileLength(resourceIndex);
    }

    int ZipFileResource::vGetRawResource(const Resource& resource, char* pData)
    {
        assert((m_pZipFile != nullptr) && "Resource wasn't loaded!");
        assert((pData != nullptr) && "pData is null!");

        int resourceIndex = m_pZipFile->Find(resource.m_Name);
        if (resourceIndex < 0)
        {
            return -1;
        }

        int resourceSize = m_pZipFile->GetFileLength(resourceIndex);
        m_pZipFile->ReadFile(resourceIndex, pData, resourceSize);

        return resourceSize;
    }

    int ZipFileResource::vGetNumberOfResources() const
    {
        assert((m_pZipFile != nullptr) && "Resource wasn't loaded!");

        return m_pZipFile->GetTotalFiles();
    }

    std::string ZipFileResource::vGetResourceName(int resourceNumber) const
    {
        assert((m_pZipFile != nullptr) && "Resource wasn't loaded!");
        assert((resourceNumber >= 0) && (resourceNumber < vGetNumberOfResources()) && "Invalid number!");

        return m_pZipFile->GetFileName(resourceNumber);
    }

    bool ZipFileResource::vIsUsingDevelopmentDirectories() const
    {
        return false;
    }

    ZipFileDevelopmentResource::ZipFileDevelopmentResource(const std::string& zipFileName, const std::string& workingPath, Mode mode)
        : ZipFileResource(zipFileName), m_FileName(zipFileName), m_WorkingDirectory(workingPath), m_Mode(mode)
    {

    }

    ZipFileDevelopmentResource::~ZipFileDevelopmentResource()
    {

    }

    bool ZipFileDevelopmentResource::vOpen()
    {
        if (m_Mode != Mode::Editor)
        {
            ZipFileResource::vOpen();
        }
        else if (m_Mode == Mode::Editor)
        {
            ReadAssetsDirectory(L"*");
        }
        else
        {
            // TODO: check last update date to auto-refresh or auto-update the zip.
            LOG_FATAL("Not implemented yet!");
        }

        return true;
    }

    int ZipFileDevelopmentResource::vGetRawResourceSize(const Resource& resource)
    {
        if (m_Mode == Mode::Editor)
        {
            int resourceIndex = Find(resource.m_Name);
            if (resourceIndex < 0)
            {
                return -1;
            }

            return  m_AssetFileInfo[resourceIndex].nFileSizeLow;
        }

        return ZipFileResource::vGetRawResourceSize(resource);
    }

    int ZipFileDevelopmentResource::vGetRawResource(const Resource& resource, char* pData)
    {
        if (m_Mode == Mode::Editor)
        {
            int resourceIndex = Find(resource.m_Name);
            if (resourceIndex < 0)
            {
                return -1;
            }

            std::string fullFileSpec = m_WorkingDirectory + resource.m_Name;
            FILE* pFile = fopen(fullFileSpec.c_str(), "rb");
            size_t bytes = fread(pData, 1, m_AssetFileInfo[resourceIndex].nFileSizeLow, pFile);
            fclose(pFile);

            return bytes;
        }

        return ZipFileResource::vGetRawResource(resource, pData);
    }

    int ZipFileDevelopmentResource::vGetNumberOfResources() const
    {
        if (m_Mode == Mode::Editor)
        {
            return m_AssetFileInfo.size();
        }

        return ZipFileResource::vGetNumberOfResources();
    }

    std::string ZipFileDevelopmentResource::vGetResourceName(int resourceNumber) const
    {
        if (m_Mode == Mode::Editor)
        {
            std::wstring wideName = m_AssetFileInfo[resourceNumber].cFileName;

            return WStringToString(wideName);
        }

        return ZipFileResource::vGetResourceName(resourceNumber);
    }

    bool ZipFileDevelopmentResource::vIsUsingDevelopmentDirectories() const
    {
        return true;
    }

    int ZipFileDevelopmentResource::Find(const std::string& fileName)
    {
        std::string lowerCaseFileName = StringToLower(fileName);
        ZipContentsMap::iterator findIt = m_DirectoryContents.find(lowerCaseFileName);
        if (findIt == m_DirectoryContents.end())
        {
            return -1;
        }

        return findIt->second;
    }

    // TODO: this is Windows-only currently.
    void ZipFileDevelopmentResource::ReadAssetsDirectory(std::wstring fileSpec)
    {
        HANDLE fileHandle;
        WIN32_FIND_DATAW findData;

        // get first file
        std::wstring pathSpec = StringToWString(m_WorkingDirectory) + fileSpec;
        fileHandle = FindFirstFileW(pathSpec.c_str(), &findData);
        if(fileHandle != INVALID_HANDLE_VALUE)
        {
            // loop on all remeaining entries in dir
            while(FindNextFileW(fileHandle,&findData))
            {
                if (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
                    continue;

                std::wstring fileName = findData.cFileName;
                if(findData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (fileName != L".." && fileName != L".")
                    {
                        fileName = fileSpec.substr(0, fileSpec.length()-1) + fileName + L"\\*";
                        ReadAssetsDirectory(fileName);
                    }
                }
                else
                {
                    fileName = fileSpec.substr(0, fileSpec.length()-1) + fileName;
                    std::wstring lower = fileName;
                    std::transform(lower.begin(), lower.end(), lower.begin(), (int(*)(int)) std::tolower);
                    
                    wcscpy_s(&findData.cFileName[0], MAX_PATH, lower.c_str());
                    std::string sFileName = WStringToString(lower);
                    sFileName = StringReplaceAll(sFileName, "\\\\", "/");
                    m_DirectoryContents[sFileName] = m_AssetFileInfo.size();
                    
                    m_AssetFileInfo.push_back(findData);
                }
            }
        }

        FindClose(fileHandle);
    }

}
