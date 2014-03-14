#include "GameEngineStd.h"

#include "ResourceSystem.h"

namespace uge
{
    ResourceSystem::ResourceSystem()
        : m_pResourceFile(nullptr)
    {

    }

    ResourceSystem::~ResourceSystem()
    {
        if (m_pResourceFile != nullptr)
        {
            Destroy();
        }
    }

    bool ResourceSystem::Init(unsigned int resourceCacheSizeMB, IResourceFile* pResourceFile)
    {
        assert(pResourceFile != nullptr && "Invalid resource file!");
        assert(resourceCacheSizeMB > 0 && "Invalid resource cache size!");

        if (!m_ResourceCache.Init(resourceCacheSizeMB, pResourceFile))
        {
            return false;
        }

        RegisterDefaultResourceLoaders();

        return true;
    }

    bool ResourceSystem::Destroy()
    {
        m_pResourceFile = nullptr;

        return m_ResourceCache.Destroy();
    }

    void ResourceSystem::RegisterResourceLoader(IResourceLoaderSharedPointer pResourceLoader)
    {
        m_ResourceCache.RegisterLoader(pResourceLoader);
    }

    ResourceHandleSharedPointer ResourceSystem::GetResourceHandle(Resource* pResource)
    {
        return m_ResourceCache.GetHandle(pResource);
    }

    ResourceCache& ResourceSystem::GetResourceCache()
    {
        return m_ResourceCache;
    }

    void ResourceSystem::RegisterDefaultResourceLoaders()
    {
        // Register loaders from the more specific ones to the least specific.

        // XML loader.
        IResourceLoaderSharedPointer pCreateXMLLoader = XMLResourceLoader::CreateLoader();
        RegisterResourceLoader(pCreateXMLLoader);
        // Lua loader.
        IResourceLoaderSharedPointer pCreateLuaScriptLoader = LuaScriptResourceLoader::CreateLoader();
        RegisterResourceLoader(pCreateLuaScriptLoader);
    }
}
