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

#include "Time.h"

namespace uge
{

    namespace Time
    {

        TimePoint GetTime()
        {
            return std::chrono::high_resolution_clock::now();
        }

        long long GetTimeNowAsMilliseconds()
        {
            std::chrono::high_resolution_clock::time_point timeNow = GetTime();
            auto duration = timeNow.time_since_epoch();

            return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        }

        long long GetTimeNowAsMicroseconds()
        {
            std::chrono::high_resolution_clock::time_point timeNow = GetTime();
            auto duration = timeNow.time_since_epoch();

            return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        }

        long long GetTimeNowAsNanoseconds()
        {
            std::chrono::high_resolution_clock::time_point timeNow = GetTime();
            auto duration = timeNow.time_since_epoch();

            return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        }

        float GetDeltaAsSeconds(TimePoint endTimePoint, TimePoint startTimePoint)
        {
            return Time::FSecond(endTimePoint - startTimePoint).count();
        }

        const unsigned long GetDeltaAsMilliseconds(TimePoint endTimePoint, TimePoint startTimePoint)
        {
            double diff = Time::FMillisecond(endTimePoint - startTimePoint).count();

            return static_cast<unsigned long>(diff);
        }

        const unsigned long long GetDeltaAsMicroseconds(TimePoint endTimePoint, TimePoint startTimePoint)
        {
            double diff = Time::FMicrosecond(endTimePoint - startTimePoint).count();

            return static_cast<unsigned long long>(diff);
        }

        const unsigned long long GetDeltaAsNanoseconds(TimePoint endTimePoint, TimePoint startTimePoint)
        {
            double diff = Time::FNanosecond(endTimePoint - startTimePoint).count();

            return static_cast<unsigned long long>(diff);
        }

        std::string GetDateAndTimeAsString(const std::string& format)
        {
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
            time_t timeT = std::chrono::system_clock::to_time_t(timeNow);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&timeT), format.c_str());

            return ss.str();
        }

    };

}
