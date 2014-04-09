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

/**
 * @file PrimeSearch.cpp
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "PrimeSearch.h"

#include <Utilities/Math/MathStd.h>

namespace uge
{

    uint32_t PrimeSearch::m_PrimeArray[] =
    {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
        67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
        139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
        223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
        293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
        383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
        463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563,
        569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
        647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
        743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
        839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
        941, 947, 953, 967, 971, 977, 983, 991, 997
    };

    PrimeSearch::PrimeSearch(const uint32_t num) :
        m_Prime(nullptr), m_Current(0), m_NumResults(0), m_MaxResults(num)
    {
        for (int i = 0; i < sizeof(m_PrimeArray) / sizeof(uint32_t); ++i)
        {
            if (num < m_PrimeArray[i])
            {
                m_Prime = &m_PrimeArray[i];
                break;
            }
        }
    }

    int32_t PrimeSearch::GetNext(bool bRestart)
    {
        if (!m_Prime)
        {
            return -1;
        }

        if (m_NumResults > m_MaxResults)
        {
            if (bRestart)
            {
                m_NumResults = 0;
                m_Current = 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            ++m_NumResults;
        }

        int randomA = Random() + 1;
        int randomB = Random() + 1;
        int randomC = Random() + 1;

        uint32_t skip = randomA * m_MaxResults * m_MaxResults + randomB * m_MaxResults + randomC;

        m_Current += skip;
        m_Current %= *m_Prime;

        return m_Current;
    }

}
