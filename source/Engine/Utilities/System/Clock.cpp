#include "GameEngineStd.h"

#include "Clock.h"

namespace uge
{

    namespace Time
    {

        Clock::Clock()
        {
            m_InitialTimePoint = Time::GetTime();
        }

        Clock::~Clock()
        {

        }

        void Clock::Init()
        {
            m_InitialTimePoint = Time::GetTime();
        }

        float Clock::GetTimeElapsed() const
        {
            Time::TimePoint currentTime = Time::GetTime();

            return Time::GetDeltaAsSeconds(currentTime, m_InitialTimePoint);
        }

    };

}
