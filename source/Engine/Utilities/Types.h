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
    /// char
    typedef int8_t Int8;
    const Int8 Int8_MAX = std::numeric_limits<Int8>::max();
    const Int8 Int8_MIN = std::numeric_limits<Int8>::min();

    /// unsigned chat
    typedef uint8_t UInt8;
    const UInt8 UInt8_MAX = std::numeric_limits<UInt8>::max();
    const UInt8 UInt8_MIN = std::numeric_limits<UInt8>::min();

    /// short
    typedef int16_t Int16;
    const Int16 Int16_MAX = std::numeric_limits<Int16>::max();
    const Int16 Int16_MIN = std::numeric_limits<Int16>::min();

    /// unsigned short
    typedef uint16_t UInt16;
    const UInt16 UInt16_MAX = std::numeric_limits<UInt16>::max();
    const UInt16 UInt16_MIN = std::numeric_limits<UInt16>::min();

    /// int
    typedef int32_t Int32;
    const Int32 Int32_MAX = std::numeric_limits<Int32>::max();
    const Int32 Int32_MIN = std::numeric_limits<Int32>::min();
    
    /// unsigned int
    typedef uint32_t UInt32;
    const UInt32 UInt32_MAX = std::numeric_limits<UInt32>::max();
    const UInt32 UInt32_MIN = std::numeric_limits<UInt32>::min();

    /// long long
    typedef int64_t Int64;
    const Int64 Int64_MAX = std::numeric_limits<Int64>::max();
    const Int64 Int64_MIN = std::numeric_limits<Int64>::min();

    /// unsigned long long
    typedef uint64_t UInt64;
    const UInt64 UInt64_MAX = std::numeric_limits<UInt64>::max();
    const UInt64 UInt64_MIN = std::numeric_limits<UInt64>::min();

    /// float
    typedef float Float32;
    const Float32 Float32_MAX = std::numeric_limits<Float32>::max();
    const Float32 Float32_MIN = std::numeric_limits<Float32>::min();

    /// double
    typedef double Float64;
    const Float64 Float64_MAX = std::numeric_limits<Float64>::max();
    const Float64 Float64_MIN = std::numeric_limits<Float64>::min();
}
