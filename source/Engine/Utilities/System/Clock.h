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
