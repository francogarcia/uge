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

#include "Time.h"

namespace uge
{

    namespace Time
    {

        /**
         * @class Clock
         *  Registers the time elapsed since the clock was initialized.
         */
        class Clock
        {
        public:
            /**
             *  Constructor.
             * The starting time is set when the object is created.
             * Call Init() to reset and re-initialize the start time.
             */
            Clock();

            /**
             *  Destructor.
             */
            ~Clock();

            /**
             *  Initializes the time counter, setting the start time.
             */
            void Init();

            /**
             *  Calculates the elapsed time since the clock was started.
             * @return : the difference between the current time and the start time.
             */
            float GetTimeElapsed() const;

        private:
            Time::TimePoint m_InitialTimePoint;
        };

    };

}
