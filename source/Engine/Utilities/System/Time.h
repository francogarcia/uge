/*
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

#include <Utilities/Math/MathUtil.h>

namespace uge
{

    namespace Time
    {
        /*
            uge::Time::Second sec(1);
            uge::Time::Millisecond ms(1);
            min += sec;
            uge::Time::Millisecond sec_to_millisec(std::chrono::duration_cast<uge::Time::Millisecond>(sec).count());
            uge::Time::Microsecond sec_to_microsec(std::chrono::duration_cast<uge::Time::Microsecond>(sec).count());
            uge::Time::Millisecond sec_to_nanosec(std::chrono::duration_cast<uge::Time::Nanosecond>(sec).count());
        */

        typedef std::chrono::duration<Int64> Second;
        
        typedef std::chrono::duration<Int64, std::milli> Millisecond;
        typedef std::chrono::duration<Int64, std::micro> Microsecond;
        typedef std::chrono::duration<Int64, std::nano> Nanosecond;

        typedef std::chrono::duration<Int64, std::ratio<60>> Minute;
        typedef std::chrono::duration<Int64, std::ratio<3600>> Hour;
        typedef std::chrono::duration<Int64, std::ratio<24 * 3600>> Day;
        typedef std::chrono::duration<Int64, std::ratio<365 * 24 * 3600>> Year;

        typedef std::chrono::duration<Float32> FSecond;
        typedef std::chrono::duration<Float32, std::milli> FMillisecond;
        typedef std::chrono::duration<Float32, std::micro> FMicrosecond;
        typedef std::chrono::duration<Float32, std::nano> FNanosecond;

        typedef std::chrono::high_resolution_clock HighResolutionClock;
        typedef std::chrono::high_resolution_clock::time_point TimePoint;

        // GetCurrentTime is used by a Windows macro.
        TimePoint GetTime();
        long long GetTimeNowAsMilliseconds();
        long long GetTimeNowAsMicroseconds();
        long long GetTimeNowAsNanoseconds();

        float GetDeltaAsSeconds(TimePoint endTimePoint, TimePoint startTimePoint);
        const unsigned long GetDeltaAsMilliseconds(TimePoint endTimePoint, TimePoint startTimePoint);
        const unsigned long long GetDeltaAsMicroseconds(TimePoint endTimePoint, TimePoint startTimePoint);
        const unsigned long long GetDeltaAsNanoseconds(TimePoint endTimePoint, TimePoint startTimePoint);

        std::string GetDateAndTimeAsString(const std::string& format = "%Y/%m/%d %X");
    };

}
