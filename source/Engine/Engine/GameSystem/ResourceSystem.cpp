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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

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
