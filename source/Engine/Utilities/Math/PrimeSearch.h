/*
  * (c) Copyright 2014 Franco Eus�bio Garcia
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

/**
 * @file PrimeSearch.h
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

namespace uge
{

    class PrimeSearch
    {

    public:
        PrimeSearch(const uint32_t num);

        int32_t GetNext(bool bRestart = false);

    private:
        static uint32_t m_PrimeArray[];

        uint32_t* m_Prime;

        uint32_t m_Current;

        uint32_t m_NumResults;

        uint32_t m_MaxResults;
    };

}
