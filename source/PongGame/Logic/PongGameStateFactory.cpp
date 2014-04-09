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

#include "PongGameStd.h"

#include "PongGameStateFactory.h"

namespace PongState
{
    PongGameStateFactory::PongGameStateFactory()
    {

    }

    PongGameStateFactory::~PongGameStateFactory()
    {

    }

    void PongGameStateFactory::vInitFactory()
    {
        //m_StateFactory.Register<PongState::Uninitialized>(PongState::Uninitialized::g_Name);
        m_StateFactory.Register<PongState::Initializing>(PongState::Initializing::g_Name);
        m_StateFactory.Register<PongState::SplashScreen>(PongState::SplashScreen::g_Name);
        m_StateFactory.Register<PongState::Paused>(PongState::Paused::g_Name);
        m_StateFactory.Register<PongState::HiScores>(PongState::HiScores::g_Name);
        m_StateFactory.Register<PongState::MainMenu>(PongState::MainMenu::g_Name);
        m_StateFactory.Register<PongState::NewGame>(PongState::NewGame::g_Name);
        m_StateFactory.Register<PongState::Running>(PongState::Running::g_Name);
        m_StateFactory.Register<PongState::GameOver>(PongState::GameOver::g_Name);
        m_StateFactory.Register<PongState::Exiting>(PongState::Exiting::g_Name);
    }
}
