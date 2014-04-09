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
