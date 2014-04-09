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

#pragma once

#include "Resource.h"

// TODO / FIXME: Add PhysFS
// TODO: improve error handling, allow multiple file usage.

namespace uge
{

    class ResourceCache;
    class ResourceHandle;

    typedef std::shared_ptr<ResourceHandle> ResourceHandleSharedPointer;
    typedef std::list<ResourceHandleSharedPointer> ResourceHandleList;
    typedef std::map<std::string, ResourceHandleSharedPointer> ResourceHandleMap;

    class ResourceHandle
    {
        friend class ResourceCache;

    public:
        ResourceHandle(Resource& resource, char* pData, unsigned int dataSize, ResourceCache* pResourceCache);

        virtual ~ResourceHandle();

        const std::string GetName() const;
        unsigned int GetSize() const;
        const char* const GetData() const;
        char* GetWritableData();

        IResourceExtraDataSharedPointer GetExtraData();
        void SetExtraData(IResourceExtraDataSharedPointer pExtraData);

    protected:
        Resource m_Resource;
        char* m_pResourceData;
        unsigned int m_ResourceSize;
        IResourceExtraDataSharedPointer m_pResourceExtraData;
        ResourceCache* m_pResourceCache;

    private:

    };

    class IResourceLoader
    {
    public:
        IResourceLoader();
        virtual ~IResourceLoader();

        virtual std::string vGetPattern() = 0;
        virtual bool vUseRawFile() = 0;
        virtual bool vDiscardRawBufferAfterLoad() = 0;
        virtual bool vAddNullZero();

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) = 0;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) = 0;
    };

    typedef std::shared_ptr<IResourceLoader> IResourceLoaderSharedPointer;
    typedef std::list<IResourceLoaderSharedPointer> ResourceLoaderList;

    class DefaultResourceLoader : public IResourceLoader
    {
    public:
        DefaultResourceLoader();
        virtual ~DefaultResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;
        virtual bool vAddNullZero() override;
        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;
    };

    class ResourceCache
    {
        friend class ResourceHandle;

    public:
        ResourceCache();
        virtual ~ResourceCache();

        bool Init(const int cacheSizeMB, IResourceFile* pResourceFile);
        bool Destroy();

        void RegisterLoader(IResourceLoaderSharedPointer pResourceLoader);
        ResourceHandleSharedPointer GetHandle(Resource* pResource);

        // TODO: Swap function pointer to std::function, if it's faster.
        int Preload(const std::string pattern, void (*progressCallback)(int, bool&));
        std::vector<std::string> Match(const std::string pattern);

        void Flush();

        bool IsUsingDevelopmentDirectories() const;

    protected:
        bool MakeRoom(unsigned int size);
        char* Allocate(unsigned int size);
        void Free(ResourceHandleSharedPointer pResourceHandle);

        ResourceHandleSharedPointer Load(Resource* pResource);
        ResourceHandleSharedPointer Find(Resource* pResource);
        void Update(ResourceHandleSharedPointer pHandle);

        void FreeOneResource();
        void MemoryHasBeenFreed(unsigned int size);

        ResourceHandleList m_LRU;
        ResourceHandleMap m_Resources;
        ResourceLoaderList m_ResourceLoaders;

        IResourceFile* m_pResourceFile;

        unsigned int m_ResourceCacheSizeMB;
        unsigned int m_ResourceCacheAllocatedSize;
    };

}
