#pragma once

#include "../Task.h"

namespace uge
{

    class TimeDelayTask : public Task
    {
    public:
        explicit TimeDelayTask(const unsigned long timeToDelay);
        ~TimeDelayTask();

    protected:
        virtual void vOnUpdate(const unsigned long dt);

    private:
        unsigned long m_TimeToDelay;
        unsigned long m_TimeElapsedSinceStart;
    };

}
