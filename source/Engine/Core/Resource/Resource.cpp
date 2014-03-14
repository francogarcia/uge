#include "GameEngineStd.h"

#include "Resource.h"
#include <Utilities/String/StringUtil.h>

namespace uge
{

    IResourceExtraData::IResourceExtraData()
    {

    }

    IResourceExtraData::~IResourceExtraData()
    {

    }

    Resource::Resource(const std::string& name) : m_Name(name)
    {
        StringToLower(m_Name);
    }

    Resource::Resource(const Resource& resource) : m_Name(resource.m_Name)
    {

    }

    Resource::~Resource()
    {

    }

    IResourceFile::IResourceFile()
    {

    }

    IResourceFile::~IResourceFile()
    {

    }

}
