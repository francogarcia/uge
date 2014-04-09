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
