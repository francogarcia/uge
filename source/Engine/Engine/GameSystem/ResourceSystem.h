#pragma once

#include <Core/Resource/Resource.h>
#include <Core/Resource/ResourceCache.h>

#include <Core/Resource/XMLResource.h>
#include <Core/Resource/ZipFileResource.h>
#include <Core/Script/Lua/ScriptResource.h>

namespace uge
{
    class ResourceSystem
    {
    public:
        ResourceSystem();

        ~ResourceSystem();

        bool Init(unsigned int resourceCacheSizeMB, IResourceFile* pResourceFile);

        bool Destroy();

        void RegisterResourceLoader(IResourceLoaderSharedPointer pResourceLoader);

        ResourceHandleSharedPointer GetResourceHandle(Resource* pResource);

        ResourceCache& GetResourceCache();

    private:
        void RegisterDefaultResourceLoaders();

    private:
        IResourceFile* m_pResourceFile;
        ResourceCache m_ResourceCache;
    };
}
