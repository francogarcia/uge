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

#pragma once

// Based on: http://www.altdevblogaday.com/2011/10/27/quasi-compile-time-string-hashing/

namespace uge
{
    // TODO: change to a C++11 with constexpr when MSVC supports it.

    //template <unsigned int N, unsigned int I>
    //struct FnvHash
    //{
    //    /*ME_INLINE*/ __forceinline static unsigned int Hash(const char(&str)[N])
    //    {
    //        return (FnvHash < N, I - 1 >::Hash(str) ^ str[I - 1]) * 16777619u;
    //    }
    //};

    //template <unsigned int N>
    //struct FnvHash<N, 1>
    //{
    //    /*ME_INLINE*/ __forceinline static unsigned int Hash(const char(&str)[N])
    //    {
    //        return (2166136261u ^ str[0]) * 16777619u;
    //    }
    //};

    class StringHash
    {
    public:
        //template <unsigned int N>
        ///*ME_INLINE*/ __forceinline StringHash(const char(&string)[N])
        //    : m_String(string), m_bHashed(true), m_Hash(FnvHash<N, N>::Hash(str))
        //{

        //}

        StringHash(const char* pString);
        StringHash(const std::string& string);

        unsigned int GetHash();
        const std::string& GetString() const;

    private:
        std::string m_String;
        unsigned int m_Hash;
        bool m_bHashed;
    };
}
