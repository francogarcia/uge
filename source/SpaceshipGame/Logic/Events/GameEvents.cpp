/*
 * (c) Copyright 2014 Franco Eusébio Garcia
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

#include "SpaceshipGameStd.h"

#include "GameEvents.h"

namespace sg
{
    const uge::EventType AlienDestroyed::sk_EventType(0xe91b0343);
    const uge::EventType FireProjectile::sk_EventType(0xd8c91a61);
    const uge::EventType MoveActor::sk_EventType(0x9c4753d0);
    const uge::EventType StopActor::sk_EventType(0xb35753b9);
}
