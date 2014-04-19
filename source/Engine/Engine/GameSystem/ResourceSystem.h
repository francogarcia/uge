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
