/**
 * @file RandomNumberGenerator.h
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

namespace uge
{

    /**
     * @class RandomNumberGenerator
     *  Abstraction for retrieving random numbers.
     */
    class RandomNumberGenerator
    {
    public:
        /**
         *  Constructor.
         */
        RandomNumberGenerator();

        /**
         *  Destructor.
         */
        ~RandomNumberGenerator();

        /**
         *  Gets a random number ranging from 0 to upperLimit - 1 (inclusive).
         * @return : the random number.
         */
        const unsigned int Random(const unsigned int upperLimit);

        /**
         *  Gets a random float number ranging from 0.0f to 1.0f.
         * @return : the random number.
         */
        const float Random();

        /**
         *  Sets a new seed to be used by the random number generator.
         * @param seed : the seed value which will be used for the RNG.
         */
        void SetRandomSeed(const unsigned int seed);

        /**
         *  Retrieves the seed used to generate the random numbers.
         * @return : the current RNG seed.
         */
        const unsigned int GetRandomSeed();

        /**
         *  Generates a new seed for the random number generator, reinitializing it.
         */
        void Randomize();

    private:
        /// Seed being used.
        unsigned int rseed;
        unsigned int rseed_sp;
        unsigned long mt[CMATH_N]; /* the array for the state vector  */
        int mti; /* mti==N+1 means mt[N] is not initialized */
    };

}
