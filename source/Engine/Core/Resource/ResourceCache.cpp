#include "GameEngineStd.h"

#include "ResourceCache.h"

// FIXME: refactor this out.
#include <Engine/GameApplication/GameApplication.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>
#include <Utilities/System/SystemInformation.h>

namespace uge
{

    ResourceHandle::ResourceHandle(Resource& resource,
                                   char* pData,
                                   unsigned int dataSize,
                                   ResourceCache* pResourceCache)
        : m_Resource(resource), m_pResourceData(pData),
          m_ResourceSize(dataSize), m_pResourceCache(pResourceCache),
          m_pResourceExtraData(nullptr)
    {

    }

    ResourceHandle::~ResourceHandle()
    {
        SAFE_DELETE_ARRAY(m_pResourceData);
        m_pResourceCache->MemoryHasBeenFreed(m_ResourceSize);
    }

    const std::string ResourceHandle::GetName() const
    {
        return m_Resource.m_Name;
    }

    unsigned int ResourceHandle::GetSize() const
    {
        return m_ResourceSize;
    }

    const char* const ResourceHandle::GetData() const
    {
        return m_pResourceData;
    }

    char* ResourceHandle::GetWritableData()
    {
        return m_pResourceData;
    }

    IResourceExtraDataSharedPointer ResourceHandle::GetExtraData()
    {
        return m_pResourceExtraData;
    }

    void ResourceHandle::SetExtraData(IResourceExtraDataSharedPointer pExtraData)
    {
        m_pResourceExtraData = pExtraData;
    }

    IResourceLoader::IResourceLoader()
    {

    }

    IResourceLoader::~IResourceLoader()
    {

    }

    bool IResourceLoader::vAddNullZero()
    {
        return false;
    }

    DefaultResourceLoader::DefaultResourceLoader()
    {

    }

    DefaultResourceLoader::~DefaultResourceLoader()
    {

    }

    std::string DefaultResourceLoader::vGetPattern()
    {
        return "*";
    }

    bool DefaultResourceLoader::vUseRawFile()
    {
        return true;
    }

    bool DefaultResourceLoader::vDiscardRawBufferAfterLoad()
    {
        return true;
    }

    bool DefaultResourceLoader::vAddNullZero()
    {
        return false;
    }

    unsigned int DefaultResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool DefaultResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        return true;
    }

    ResourceCache::ResourceCache()
        : m_ResourceCacheSizeMB(0U),
          m_ResourceCacheAllocatedSize(0U),
          m_pResourceFile(nullptr)
    {

    }

    ResourceCache::~ResourceCache()
    {
        if (m_pResourceFile != nullptr)
        {
            Destroy();
        }
    }

    bool ResourceCache::Init(const int cacheSizeMB, IResourceFile* pResourceFile)
    {
        assert(pResourceFile != nullptr && "Invalid resource file!");

        m_ResourceCacheSizeMB = cacheSizeMB * SystemInformation::MEGABYTE;
        m_ResourceCacheAllocatedSize = 0U;
        m_pResourceFile = pResourceFile;

        if (m_pResourceFile->vOpen())
        {
            IResourceLoaderSharedPointer pResourceLoader(LIB_NEW DefaultResourceLoader());
            RegisterLoader(pResourceLoader);

            return true;
        }

        return false;
    }

    bool ResourceCache::Destroy()
    {
        while (!m_LRU.empty())
        {
            FreeOneResource();
        }

        SAFE_DELETE(m_pResourceFile)

        return true;
    }

    void ResourceCache::RegisterLoader(IResourceLoaderSharedPointer pResourceLoader)
    {
        assert((pResourceLoader != nullptr) && "Invalid resource loader!");

        m_ResourceLoaders.push_front(pResourceLoader);
    }

    ResourceHandleSharedPointer ResourceCache::GetHandle(Resource* pResource)
    {
        ResourceHandleSharedPointer pResourceHandle(Find(pResource));
        if (pResourceHandle == nullptr)
        {
            pResourceHandle = Load(pResource);
        }
        else
        {
            Update(pResourceHandle);
        }

        return pResourceHandle;
    }

    int ResourceCache::Preload(const std::string pattern, void (*progressCallback)(int, bool&))
    {
        assert((m_pResourceFile != nullptr) && "No file!");

        int totalFiles = m_pResourceFile->vGetNumberOfResources();
        int totalFilesLoaded = 0;

        for (int file = 0; file < totalFiles; ++file)
        {
            Resource resource(m_pResourceFile->vGetResourceName(file));

            // FIXME: change to std::regex
            if (WildcardMatch(pattern.c_str(), resource.m_Name.c_str()))
            {
                ResourceHandleSharedPointer pHandle = g_pApp->vGetResourceCache()->GetHandle(&resource);
                ++totalFilesLoaded;
            }

            if (progressCallback != nullptr)
            {
                bool shallCancel = false;
                progressCallback((file * 100) / totalFiles, shallCancel);
            }
        }

        return totalFilesLoaded;
    }

    std::vector<std::string> ResourceCache::Match(const std::string pattern)
    {
        std::vector<std::string> matchingNames;

        if (m_pResourceFile == nullptr)
        {
            assert(0 && "No resource file!");

            return matchingNames;
        }

        int totalFiles = m_pResourceFile->vGetNumberOfResources();
        for (int i = 0; i < totalFiles; ++i)
        {
            std::string name(m_pResourceFile->vGetResourceName(i));
            std::transform(name.begin(), name.end(), name.begin(), std::tolower);
            if (WildcardMatch(pattern.c_str(), name.c_str()))
            {
                matchingNames.push_back(name);
            }
        }

        return matchingNames;
    }

    void ResourceCache::Flush()
    {
        while (!m_LRU.empty())
        {
            ResourceHandleSharedPointer pHandle = *(m_LRU.begin());
            Free(pHandle);
            m_LRU.pop_front();
        }
    }

    bool ResourceCache::IsUsingDevelopmentDirectories() const
    {
        assert((m_pResourceFile != nullptr) && "No file!");

        return m_pResourceFile->vIsUsingDevelopmentDirectories();
    }

    bool ResourceCache::MakeRoom(unsigned int size)
    {
        if (size > m_ResourceCacheSizeMB)
        {
            return false;
        }

        while (size > (m_ResourceCacheSizeMB - m_ResourceCacheAllocatedSize))
        {
            if (m_LRU.empty()) // FIXME: would fail on previous call.
            {
                return false;
            }

            FreeOneResource();
        }

        return true;
    }

    char* ResourceCache::Allocate(unsigned int size)
    {
        if (!MakeRoom(size))
        {
            return nullptr;
        }

        char* pMemory = LIB_NEW char[size];
        if (pMemory != nullptr)
        {
            m_ResourceCacheAllocatedSize += size;
        }

        return pMemory;
    }

    void ResourceCache::Free(ResourceHandleSharedPointer pResourceHandle)
    {
        m_LRU.remove(pResourceHandle);
        m_Resources.erase(pResourceHandle->m_Resource.m_Name);
    }

    ResourceHandleSharedPointer ResourceCache::Load(Resource* pResource)
    {
        IResourceLoaderSharedPointer pLoader;
        ResourceHandleSharedPointer pHandle;

        for (IResourceLoaderSharedPointer pResourceLoader : m_ResourceLoaders)
        {
            if (WildcardMatch(pResourceLoader->vGetPattern().c_str(),
                              pResource->m_Name.c_str()))
            {
                pLoader = pResourceLoader;

                break;
            }
        }

        if (pLoader == nullptr)
        {
            LOG_ERROR(std::string("Resource loader not found for resource: " + pResource->m_Name + "."));

            return pHandle; // nullptr
        }

        int rawSize = m_pResourceFile->vGetRawResourceSize(*pResource);
        if (rawSize < 0)
        {
            LOG_ERROR(std::string("Resource not found: " + pResource->m_Name + + "."));

            return pHandle; // nullptr
        }

        int allocSize = rawSize + (pLoader->vAddNullZero() ? 1 : 0);
        char* pRawBuffer = pLoader->vUseRawFile() ? Allocate(allocSize) : LIB_NEW char[allocSize];
        memset(pRawBuffer, 0, allocSize);

        if (pRawBuffer == nullptr || m_pResourceFile->vGetRawResource(*pResource, pRawBuffer) == 0)
        {
            return pHandle; // nullptr
        }

        char* pBuffer = nullptr;
        unsigned int size = 0;
        if (pLoader->vUseRawFile())
        {
            pBuffer = pRawBuffer;
            pHandle = ResourceHandleSharedPointer(LIB_NEW ResourceHandle(*pResource, pBuffer, rawSize, this));
        }
        else
        {
            size = pLoader->vGetLoadedResourceSize(pRawBuffer, rawSize);
            pBuffer = Allocate(size);
            if ((pRawBuffer == nullptr) || (pBuffer == nullptr))
            {
                return ResourceHandleSharedPointer(); // not enough memory
            }

            pHandle = ResourceHandleSharedPointer(LIB_NEW ResourceHandle(*pResource, pBuffer, size, this));
            bool bSuccess = pLoader->vLoadResource(pRawBuffer, rawSize, pHandle);

            if (pLoader->vDiscardRawBufferAfterLoad())
            {
                SAFE_DELETE_ARRAY(pRawBuffer);
            }

            if (!bSuccess)
            {
                return ResourceHandleSharedPointer();
            }
        }

        if (pHandle)
        {
            m_LRU.push_front(pHandle);
            m_Resources[pResource->m_Name] = pHandle;
        }

        assert((pLoader != nullptr) && "Default resource loader not found!");

        return pHandle;
    }

    ResourceHandleSharedPointer ResourceCache::Find(Resource* pResource)
    {
        assert((pResource != nullptr) && "Invalid resource!");

        ResourceHandleMap::iterator findIt = m_Resources.find(pResource->m_Name);
        if (findIt == m_Resources.end())
        {
            return ResourceHandleSharedPointer();
        }

        return findIt->second;
    }

    void ResourceCache::Update(ResourceHandleSharedPointer pHandle)
    {
        m_LRU.remove(pHandle);
        m_LRU.push_front(pHandle);
    }

    void ResourceCache::FreeOneResource()
    {
        ResourceHandleList::iterator gonner = m_LRU.end();
        gonner--;

        ResourceHandleSharedPointer pHandle = *gonner;

        m_LRU.pop_back();
        m_Resources.erase(pHandle->m_Resource.m_Name);
    }

    void ResourceCache::MemoryHasBeenFreed(unsigned int size)
    {
        m_ResourceCacheAllocatedSize -= size;
    }

}
