#include <Utilities/Debug/Logger.h>
#include <Utilities/File/ZipFile.h>

#include <iostream>

int main()
{
    uge::ZipFile zipFile;

    std::string fileName("ZipFile.zip");
    if (!zipFile.Init(fileName))
    {
        std::cerr << "Error loading the zip file." << std::endl;

        return -1;
    }

    std::vector<std::string> allFiles(zipFile.GetAllFileNames());
    std::cout << "Files in " << fileName << ":";
    for (const std::string& filename : allFiles)
    {
        std::cout << " " << filename;
    }
    std::cout << std::endl;

    int totalFiles = allFiles.size();
    for (int filePosition = 0; filePosition < totalFiles; ++filePosition)
    {
        const std::string& filename = allFiles[filePosition];
        std::cout << " " << filename << std::endl;

        const int fileLength = zipFile.GetFileLength(filePosition);
        if (fileLength > 0)
        {
            // Assuming it is a text file (ASCII).
            char* pBuffer = new char[fileLength + 1]; // +1: '\0'
            if (zipFile.ReadFile(filePosition, pBuffer))
            {
                pBuffer[fileLength] = '\0';
                std::cout << pBuffer;
            }

            SAFE_DELETE_ARRAY(pBuffer);
        }
        else
        {
            std::cout << "Directory or blank file.";
        }

        std::cout << std::endl;
    }

    zipFile.Destroy();

    return 0;
}
