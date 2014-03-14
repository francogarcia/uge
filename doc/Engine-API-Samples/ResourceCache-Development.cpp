#include <Core/Resource/ResourceCache.h>
#include <Core/Resource/ZipFileResource.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/File/ZipFile.h>

#include <iostream>

int main()
{
    // uge::ZipFileDevelopmentResource::Mode::Editor requests to use the filesystem
    // instead of a ZIP resource file.
    uge::IResourceFile* pResourceFile = new uge::ZipFileDevelopmentResource("ResourceCache.zip",
                                                                            ".\\",
                                                                            uge::ZipFileDevelopmentResource::Mode::Editor);
    uge::ResourceCache resourceCache;

    if (!resourceCache.Init(10, pResourceFile)) // 10MB
    {
        std::cerr << "Could not create the resource cache!" << std::endl;

        return -1;
    }

    uge::Resource resource("text.txt");
    uge::ResourceHandleSharedPointer pHandle = resourceCache.GetHandle(&resource);
    assert((pHandle != nullptr) && "Error loading the file!");

    int textLength = pHandle->GetSize();
    assert((textLength > 0) && "Error loading the file!");

    char* pText = new char[textLength + 1];
    memcpy(pText, (char*) pHandle->GetData(), textLength);
    pText[textLength] = '\0';
    std::cout << pText << std::endl;  
    
    // The resource file is deleted by the resource cache.

    return 0;
}
