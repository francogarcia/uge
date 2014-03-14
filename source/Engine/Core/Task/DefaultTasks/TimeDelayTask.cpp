#include "GameEngineStd.h"

#include "TimeDelayTask.h"

namespace uge
{

    TimeDelayTask::TimeDelayTask(const unsigned long timeToDelay) : m_TimeToDelay(timeToDelay),
        m_TimeElapsedSinceStart(0)
    {

    }

    TimeDelayTask::~TimeDelayTask()
    {
        m_TimeElapsedSinceStart = 0;
    }

    void TimeDelayTask::vOnUpdate(const unsigned long dt)
    {
        m_TimeElapsedSinceStart += dt;
        if (m_TimeElapsedSinceStart >= m_TimeToDelay)
        {
            Succeed();
        }
    }

}
