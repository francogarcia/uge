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

#include "SceneEvents.h"

namespace uge
{
    const EventType EvtData_Scene_Node_Attached::sk_EventType(0xc8861E57);
    const EventType EvtData_Scene_Node_Removed::sk_EventType(0xa2e5b384);
    const EventType EvtData_Changed_Render_Component::sk_EventType(0xd4E5fBB);
}
