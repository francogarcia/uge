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
