/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE.
 *
 * UGE is free software; you can redistribute it and/or
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "PongGameStd.h"

#include "GameEvents.h"

namespace pg
{
    const uge::EventType EvtData_Player_Scored::sk_EventType(0xd9820000);
    const uge::EventType EvtData_Ball_Wall_Collision::sk_EventType(0x285e83b);
    const uge::EventType EvtData_Ball_Paddle_Collision::sk_EventType(0xc3771e27);
    const uge::EventType EvtData_Paddle_Wall_Collision::sk_EventType(0x182ad93d);
    const uge::EventType EvtData_Restart_Game::sk_EventType(0x1711f7b2);
    const uge::EventType MoveActor::sk_EventType(0x9c4753d0);
    const uge::EventType StopActor::sk_EventType(0xb35753b9);
}
