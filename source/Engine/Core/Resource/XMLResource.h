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
#include "ResourceCache.h"

#include <Utilities/File/XMLFile.h>

namespace uge
{

    class XMLResourceExtraData : public IResourceExtraData
    {
    public:
        XMLResourceExtraData();

        ~XMLResourceExtraData();

        std::string vToString() override;

        bool LoadXML(const char* pXMLBuffer);

        bool LoadXML(std::string& xmlBuffer);

        uge::XMLElement GetRootElement();

    private:
        uge::XMLFile m_XMLFile;
    };

    class XMLResourceLoader : public IResourceLoader
    {
    public:
        XMLResourceLoader();

        ~XMLResourceLoader();

        virtual std::string vGetPattern() override;
        virtual bool vUseRawFile() override;
        virtual bool vDiscardRawBufferAfterLoad() override;

        virtual unsigned int vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize) override;
        virtual bool vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle) override;

        static uge::XMLElement LoadAndReturnRootElement(const char* pXMLBuffer);
        static uge::XMLElement LoadAndReturnRootElement(std::string& xmlBuffer);

        static IResourceLoaderSharedPointer CreateLoader();
    };

}
