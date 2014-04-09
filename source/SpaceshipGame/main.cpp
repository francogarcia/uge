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

#include "SpaceshipGameStd.h"

#define UGE_ENABLE_PHYSICS  1
//#define UGE_DEBUG_PHYSICS   1

#define SG_USE_DEVELOPMENT_RESOURCE_FILE 1

// Game specific headers
#include "Application/Application.h"

// UGE headers.
#include <Utilities/Debug/Logger.h>

int main()
{
    uge::debug::log::Init("data/debug/LogConfig.xml");
    //LOG_INFO("Game started.");

    sg::Application game;
    game.vInit();
    game.vRun();
    game.vDestroy();

    //LOG_INFO("Game finished.");
    uge::debug::log::Destroy();

    return 0;
}
