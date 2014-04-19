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

extern "C"
{
#define MINIZ_HEADER_FILE_ONLY
#include <miniz.c>
};

namespace uge
{

    typedef std::map<std::string, int> ZipContentsMap;

    class ZipFile
    {
    public:
        ZipFile();

        virtual ~ZipFile();

        bool Init(const std::string& zipFileName);

        void Destroy();

        int GetTotalFiles() const;

        std::string GetFileName(int fileIndex) const;
        std::vector<std::string> GetAllFileNames() const;

        int GetFileLength(int fileIndex) const;

        bool ReadFile(int fileIndex, void* pBuffer);
        bool ReadFile(int fileIndex, void* pBuffer, int bufferSize);

        bool ReadLargeFile(int fileIndex, void* pBuffer, void (*progressCallback)(int, bool&));

        int Find(const std::string& fileName) const;

    private:
        ZipContentsMap m_ZipContentsMap;

        std::vector<mz_zip_archive_file_stat> m_FileStats;

        mz_zip_archive m_ZipArchive;
    };

}
