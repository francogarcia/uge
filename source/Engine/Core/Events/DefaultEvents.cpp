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

#include "DefaultEvents.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{ 

    const EventType EvtData_Destroy_Actor::sk_EventType(0x77DD2B3A);
    const EventType EvtData_Move_Actor::sk_EventType(0xA63E1849);
    const EventType EvtData_New_Actor::sk_EventType(0x77AD2B30);
    const EventType EvtData_Request_Start_Game::sk_EventType(0x11F2B19D);
    const EventType EvtData_Set_Controlled_Actor::sk_EventType(0x2d476e11);

}
