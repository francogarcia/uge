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

#include "GameEngineStd.h"

#include "XMLResource.h"

// TODO: refactor this out.
#include <Engine/GameApplication/GameApplication.h>

namespace uge
{

    XMLResourceExtraData::XMLResourceExtraData()
    {

    }

    XMLResourceExtraData::~XMLResourceExtraData()
    {

    }

    std::string XMLResourceExtraData::vToString()
    {
        return "XMLResourceExtraData";
    }

    bool XMLResourceExtraData::LoadXML(const char* pXMLBuffer)
    {
        assert((pXMLBuffer != nullptr) && "Invalid XML buffer!");

        return (m_XMLFile.LoadFromMemory(pXMLBuffer));
    }

    bool XMLResourceExtraData::LoadXML(std::string& xmlBuffer)
    {
        return (m_XMLFile.LoadFromMemory(xmlBuffer));
    }

    XMLElement XMLResourceExtraData::GetRootElement()
    {
        return m_XMLFile.GetRootElement();
    }

    XMLResourceLoader::XMLResourceLoader()
    {

    }

    XMLResourceLoader::~XMLResourceLoader()
    {

    }

    std::string XMLResourceLoader::vGetPattern()
    {
        return ".xml";
    }

    bool XMLResourceLoader::vUseRawFile()
    {
        return false;
    }

    bool XMLResourceLoader::vDiscardRawBufferAfterLoad()
    {
        return true;
    }

    unsigned int XMLResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool XMLResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        if (rawSize == 0U)
        {
            return false;
        }

        std::shared_ptr<XMLResourceExtraData> pExtraData = std::shared_ptr<XMLResourceExtraData>(LIB_NEW(XMLResourceExtraData));
        pExtraData->LoadXML(pRawBuffer);

        pResourceHandle->SetExtraData(pExtraData);

        return true;
    }

    XMLElement XMLResourceLoader::LoadAndReturnRootElement(const char* pXMLBuffer)
    {
        return LoadAndReturnRootElement(std::string(pXMLBuffer));
    }

    XMLElement XMLResourceLoader::LoadAndReturnRootElement(std::string& xmlBuffer)
    {
        Resource resource(xmlBuffer);
        ResourceHandleSharedPointer pResourceHandle = g_pApp->vGetResourceCache()->GetHandle(&resource);
        std::shared_ptr<XMLResourceExtraData> pExtraData = std::static_pointer_cast<XMLResourceExtraData>(pResourceHandle->GetExtraData());

        return pExtraData->GetRootElement();
    }

    IResourceLoaderSharedPointer XMLResourceLoader::CreateLoader()
    {
        return IResourceLoaderSharedPointer(LIB_NEW XMLResourceLoader);
    }

}
