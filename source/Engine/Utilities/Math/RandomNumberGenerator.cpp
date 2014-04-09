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
 * @file RandomNumberGenerator.cpp
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

/* Period parameters */
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

#define CMATH_MAXINT ((2 << 31) - 1)

#include "RandomNumberGenerator.h"

namespace uge
{

    //========================================================================
    //
    //  "Mersenne Twister pseudorandom number generator"
    //  Original Code written by Takuji Nishimura and Makoto Matsumoto
    //
    //========================================================================

    RandomNumberGenerator::RandomNumberGenerator(void)
    {
        rseed = 1;
        // safe0 start
        rseed_sp = 0;
        mti = CMATH_N + 1;
        // safe0 end
    }

    // Returns a number from 0 to n (excluding n)
    const unsigned int RandomNumberGenerator::Random(const unsigned int n)
    {
        unsigned long y;
        static unsigned long mag01[2] = {0x0, CMATH_MATRIX_A};

        if (n == 0)
        {
            return (0);
        }

        /* mag01[x] = x * MATRIX_A  for x=0,1 */

        if (mti >= CMATH_N)   /* generate N words at one time */
        {
            int kk;

            if (mti == CMATH_N + 1) /* if sgenrand() has not been called, */
            {
                SetRandomSeed(4357);    /* a default initial seed is used   */
            }

            for (kk = 0; kk < CMATH_N - CMATH_M; kk++)
            {
                y = (mt[kk] & CMATH_UPPER_MASK) | (mt[kk + 1] & CMATH_LOWER_MASK);
                mt[kk] = mt[kk + CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
            }
            for (; kk < CMATH_N - 1; kk++)
            {
                y = (mt[kk] & CMATH_UPPER_MASK) | (mt[kk + 1] & CMATH_LOWER_MASK);
                mt[kk] = mt[kk + (CMATH_M - CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
            }
            y = (mt[CMATH_N - 1] & CMATH_UPPER_MASK) | (mt[0] & CMATH_LOWER_MASK);
            mt[CMATH_N - 1] = mt[CMATH_M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

            mti = 0;
        }

        y = mt[mti++];
        y ^= CMATH_TEMPERING_SHIFT_U(y);
        y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
        y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
        y ^= CMATH_TEMPERING_SHIFT_L(y);

        // ET - old engine added one to the result.
        // We almost NEVER wanted to use this function
        // like this.  So, removed the +1 to return a
        // range from 0 to n (not including n).
        return (y % n);
    }

    const float RandomNumberGenerator::Random()
    {
        float r = (float) Random(CMATH_MAXINT);
        float divisor = (float) CMATH_MAXINT;
        return (r / divisor);
    }

    void RandomNumberGenerator::SetRandomSeed(const unsigned int n)
    {
        /* setting initial seeds to mt[N] using         */
        /* the generator Line 25 of Table 1 in          */
        /* [KNUTH 1981, The Art of Computer Programming */
        /*    Vol. 2 (2nd Ed.), pp102]                  */
        mt[0] = n & 0xffffffff;
        for (mti = 1; mti < CMATH_N; mti++)
        {
            mt[mti] = (69069 * mt[mti - 1]) & 0xffffffff;
        }

        rseed = n;
    }

    const unsigned int RandomNumberGenerator::GetRandomSeed(void)
    {
        return (rseed);
    }

    void RandomNumberGenerator::Randomize(void)
    {
        SetRandomSeed((unsigned int) time(nullptr));
    }

}
