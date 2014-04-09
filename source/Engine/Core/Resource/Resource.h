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

class ResourceHandle;

namespace uge
{

    class IResourceExtraData
    {
    public:
        IResourceExtraData();

        virtual ~IResourceExtraData();

        virtual std::string vToString() = 0;
    };
    typedef std::shared_ptr<IResourceExtraData> IResourceExtraDataSharedPointer;

    class Resource
    {
    public:
        std::string m_Name;

        Resource(const std::string& name);

        Resource(const Resource& resource);

        ~Resource();
    };

    class IResourceFile
    {
    public:
        /**
         *  Constructor.
         */
        IResourceFile();

        /**
         *  Destructor.
         */
        virtual ~IResourceFile();

        /**
         *  Opens the resource file.
         * @return : should return true if successful, false otherwise.
         */
        virtual bool vOpen() = 0;

        /**
         *  Returns the size of the specified resource.
         * @param resource : resource to query the size.
         * @return : the size of the resource, in bytes.
         */
        virtual int vGetRawResourceSize(const Resource& resource) = 0;

        /**
         *  Loads the raw resource from the cache.
         * @param resource : resource to load.
         * @param pData : buffer to store the resource.
         * @return : the size of the resource, in bytes.
         */
        virtual int vGetRawResource(const Resource& resource, char* pData) = 0;

        /**
         *  Returns the total number of resources stored in this cache.
         * @return : number of resources stored.
         */
        virtual int vGetNumberOfResources() const = 0;

        /**
         *  Returns the name of the resource corresponding to the given number.
         * @param resourceNumber : index of the resource in this cache.
         * @return : the name of the resource.
         */
        virtual std::string vGetResourceName(int resourceNumber) const = 0;

        /**
         *  Tells if this resource is being used for development.
         *  The development directory allows to fake directory structures or to
         *  avoid compressing the data, allowing faster development.
         * @return : true if a development directory is being used, false otherwise.
         */
        virtual bool vIsUsingDevelopmentDirectories() const = 0;
    };

}
