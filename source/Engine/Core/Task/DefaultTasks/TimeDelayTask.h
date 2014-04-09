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
