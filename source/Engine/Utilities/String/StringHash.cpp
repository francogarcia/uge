#include "GameEngineStd.h"

#include "StringHash.h"

namespace uge
{
    StringHash::StringHash(const char* pString)
        : m_String(pString), m_bHashed(false), m_Hash(0u)
    {

    }

    StringHash::StringHash(const std::string& string)
        : m_String(string), m_bHashed(false), m_Hash(0u)
    {

    }

    unsigned int StringHash::GetHash()
    {
        if (m_bHashed)
        {
            m_Hash = std::hash<std::string>()(m_String);
            m_bHashed = true;
        }

        return m_Hash;
    }

    const std::string& StringHash::GetString() const
    {
        return m_String;
    }
}
