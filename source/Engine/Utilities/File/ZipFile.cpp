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

#include "GameEngineStd.h"

extern "C"
{
#include <miniz.c>
};

#include "ZipFile.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{

    ZipFile::ZipFile()
    {

    }

    ZipFile::~ZipFile()
    {
        Destroy();
    }

    bool ZipFile::Init(const std::string& zipFileName)
    {
        memset(&m_ZipArchive, 0, sizeof m_ZipArchive);

        mz_bool bStatus = mz_zip_reader_init_file(&m_ZipArchive, zipFileName.c_str(), 0);
        if (!bStatus)
        {
            return false;
        }

        // Get and print information about each file in the archive.
        int totalFiles = mz_zip_reader_get_num_files(&m_ZipArchive);
        for (int fileNumber = 0; fileNumber < totalFiles; fileNumber++)
        {
            mz_zip_archive_file_stat fileStat;
            if (!mz_zip_reader_file_stat(&m_ZipArchive, fileNumber, &fileStat))
            {
                Destroy();

                return false;
            }

            // Stores the filenames in lower case.
            std::string lowerCaseFileName(StringToLower(fileStat.m_filename));

            // FIXME: Skip directory names.
            //const std::string directoryEnding("/");
            //if (!StringEndsWith(fileName, directoryEnding))
            //{
            m_ZipContentsMap[lowerCaseFileName] = fileNumber;
            m_FileStats.push_back(fileStat);
            //}
        }
        m_FileStats.shrink_to_fit();

        return true;
    }

    void ZipFile::Destroy()
    {
        if (m_ZipContentsMap.size() > 0)
        {
            m_ZipContentsMap.clear();

            mz_zip_reader_end(&m_ZipArchive);
        }
    }

    int ZipFile::GetTotalFiles() const
    {
        return m_ZipContentsMap.size();
    }

    std::string ZipFile::GetFileName(int fileIndex) const
    {
        assert((fileIndex >= 0) && (fileIndex < m_ZipContentsMap.size()) && "Invalid index!");

        return m_FileStats[fileIndex].m_filename;
    }

    std::vector<std::string> ZipFile::GetAllFileNames() const
    {
        std::vector<std::string> m_FileNames;

        ZipContentsMap::const_iterator fileIt = m_ZipContentsMap.begin();
        ZipContentsMap::const_iterator zipFileEnd = m_ZipContentsMap.end();
        while (fileIt != zipFileEnd)
        {
            m_FileNames.push_back(fileIt->first);
            ++fileIt;
        }

        return m_FileNames;
    }

    int ZipFile::GetFileLength(int fileIndex) const
    {
        assert((fileIndex >= 0) && (fileIndex < m_FileStats.size()) && "Invalid index!");

        return m_FileStats[fileIndex].m_uncomp_size;
    }

    bool ZipFile::ReadFile(int fileIndex, void* pBuffer)
    {
        assert((fileIndex >= 0) && (fileIndex < m_ZipContentsMap.size()) && "Invalid index!");
        assert((pBuffer != nullptr) && "Buffer is null!");

        return ReadFile(fileIndex, pBuffer, m_FileStats[fileIndex].m_uncomp_size);
    }

    bool ZipFile::ReadFile(int fileIndex, void* pBuffer, int bufferSize)
    {
        assert((fileIndex >= 0) && (fileIndex < m_ZipContentsMap.size()) && "Invalid index!");
        assert((pBuffer != nullptr) && "Buffer is null!");
        assert((bufferSize > 0) && "Invalid size!");

        return (mz_zip_reader_extract_file_to_mem(&m_ZipArchive,
                                                  m_FileStats[fileIndex].m_filename,
                                                  pBuffer, bufferSize, 0) == MZ_TRUE);
    }

    bool ZipFile::ReadLargeFile(int fileIndex, void* pBuffer, void (*progressCallback)(int, bool&))
    {
        assert((fileIndex >= 0) && (fileIndex < m_ZipContentsMap.size()) && "Invalid index!");

        // TODO: implement this method.
        LOG_FATAL("Not implemented yet!");

        return false;
    }

    int ZipFile::Find(const std::string& fileName) const
    {
        std::string lowerCaseFileName = StringToLower(fileName);

        ZipContentsMap::const_iterator fileIt = m_ZipContentsMap.find(lowerCaseFileName);
        if (fileIt == m_ZipContentsMap.end())
        {
            return -1;
        }

        return fileIt->second;
    }

}
