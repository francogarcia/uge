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

#include <IO/Input/InputMapping/InputTypes.h>

enum class uge::InputMapping::Action : unsigned int
{

};

enum class uge::InputMapping::State : unsigned int
{
    Player1MoveUp,
    Player1MoveDown,
    Player2MoveUp,
    Player2MoveDown
};

enum class uge::InputMapping::Range : unsigned int
{

};
