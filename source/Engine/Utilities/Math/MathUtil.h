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

#include "GameEngineStd.h"

namespace uge
{

    /// Pi
    static const float PI = 3.1415926535f;

    /// Pi ^ 2
    static const float PI_SQUARE = PI * PI;

    /// Pi / 2.0f
    static const float PI_HALF = PI * 0.5f;

    /// Pi / 4.0f
    static const float PI_QUARTER = PI * 0.25f;

    /// E (Euler's number)
    static const float E = 2.718281828f;

    /// The Epsilon value for float point precision.
    static const float EPSILON = 0.01f;

    /**
     *  Returns the absolute value of an integer.
     * @param i : integer value.
     * @ return : the absolute value of the input number.
     */
    inline int Abs(int i)
    {
        return std::abs(i);
    }

    /**
     *  Returns the absolute value of a float.
     * @param f : input float value.
     * @ return : the absolute value of the input.
     */
    inline float FAbs(float f)
    {
        return std::fabs(f);
    }

    /**
     *  Rounds a value to its nearest bottom value.
     * @param f : the input value.
     * @ return : the floor of the input.
     */
    inline float Floor(float f)
    {
        return std::floor(f);
    }

    /**
     * Generates a random integer value.
     * @ return : a random integer value.
     */
    inline int Random()
    {
        return std::rand();
    }

    /**
     *  Generates a random float value, between 0 and 1.
     * @ return : a random float value.
     */
    inline float FRandom()
    {
        return (float)(std::rand() - RAND_MAX / 2) / (RAND_MAX / 2);
    }

    /**
     *  Returns the maximum value of the 2 input values.
     * @param fX : a value.
     * @param fY : another value.
     * @return : the maximum both values.
     */
    inline float Max(float fX, float fY)
    {
        // (std::max) avoid name crash with Windows.h define.
        return (std::max)(fX, fY);
    }

    /**
     *  Returns the minumum value of the 2 input values.
     * @param fX : a value.
     * @param fY : another value.
     * @return : the minimum of both values.
     */
    inline float Min(float fX, float fY)
    {
        // (std::min) avoid name crash with Windows.h define.
        return (std::min)(fX, fY);
    }

    /**
     *  Converts an angle from degrees to radians.
     * @param fDegAngle : angle in degrees.
     * @return : angle in radians.
     */
    inline float DegreesToRadians(float fDegAngle)
    {
        const float fFactor = uge::PI / 180.0f;

        return fDegAngle * fFactor;
    }

    /**
     *  Converts an angle from radians to degrees.
     * @param fRadAngle : angle in radians.
     * @return : angle in degrees.
     */
    inline float RadiansToDegrees(float fRadAngle)
    {
        const float fFactor = 180.0f / uge::PI;

        return fRadAngle * fFactor;
    }

    /**
     *  Calculate the sin value of the input angle.
     * @param fAngle : an angle, in radians.
     * @return : the sin value of the angle.
     */
    inline float Sin(float fAngle)
    {
        return std::sin(fAngle);
    }

    /**
     *  Calculate the cos value of the input angle.
     * @param fAngle : an angle, in radians.
     * @return : the cos value of the angle.
     */
    inline float Cos(float fAngle)
    {
        return std::cos(fAngle);
    }

    /**
     *  Calculate the tg value of the input angle.
     * @param fAngle : an angle, in radians.
     * @return : the tg value of the angle.
     */
    inline float Tg(float fAngle)
    {
        return std::tan(fAngle);
    }

    /**
     *  Obtains the arc corresponing to the input sin value.
     * The return arc is given in radians.
     * @param fSinValue : a sin value.
     * @return : the angle with the specified sin value.
     */
    inline float ArcSin(float fSinValue)
    {
        return std::asin(fSinValue);
    }

    /**
     *  Obtains the arc corresponing to the input sin value.
     * The return arc is given in radians.
     * @param fCosValue : a sin value.
     * @return : the angle with the specified sin value.
     */
    inline float ArcCos(float fCosValue)
    {
        return std::acos(fCosValue);
    }

    /**
     *  Obtains the arc corresponing to the input sin value.
     * The return arc is given in radians.
     * @param fTgValue : a sin value.
     * @return : the angle with the specified sin value.
     */
    inline float ArcTg(float fTgValue)
    {
        return std::atan(fTgValue);
    }

    /**
     *  Calculates the exponential of the input number.
     * @param fBase : a float value to be used as the base.
     * @param fExponent : the desired power.
     * @return : fBase ^ fExponent.
     */
    inline float Power(float fBase, float fExponent)
    {
        return std::pow(fBase, fExponent);
    }

    /**
     *  Calculates the exponential of the input number.
     * @param fBase : a float value to be used as the base.
     * @return : e ^ fExponent.
     */
    inline float Exponential(float fExponent)
    {
        return std::exp(fExponent);
    }

    /**
     *  Calculates the square root of the input number.
     * @param fValue : a float value (>= 0.0f).
     * @return : the square root of the input.
     */
    inline float SquareRoot(float fValue)
    {
        assert(fValue >= 0.0f && "Invalid value number used in SquareRoot!");

        return std::sqrt(fValue);
    }

    /**
     *  Calculates the base 10 logarithm of the input number.
     * @param fValue : a float value.
     * @return : log10(fValue)
     */
    inline float Logarithm10(float fValue)
    {
        return std::log10(fValue);
    }

    /**
     *  Calculates the base 10 logarithm of the input number.
     * @param fValue : a float value.
     * @return : logE(fValue)
     */
    inline float LogarithmNatural(float fValue)
    {
        return std::log(fValue);
    }

    /**
     *  Converts a float to int, rounding the result.
     * @param f : a float value.
     * @return : the float number rounded to an integer.
     */
    inline int FloatToInt(float f)
    {
        if (f >= 0.0f)
        {
            return static_cast<int>(f + 0.5f);
        }

        return static_cast<int>(f - 0.5f);
    }

    /**
     *  Converts a integer to float.
     * @param i : a integer value
     * @return : a float representation of the value.
     */
    inline float IntToFloat(int i)
    {
        return static_cast<float>(i);
    }

}
