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

#include "GameStateFactory.h"

#include "State/Exiting.h"
#include "State/GameOver.h"
#include "State/Initializing.h"
#include "State/MainMenu.h"
#include "State/NewGame.h"
#include "State/Paused.h"
#include "State/Running.h"
#include "State/SplashScreen.h"

namespace pg
{

    namespace GameState
    {
        GameStateFactory::GameStateFactory()
        {

        }

        GameStateFactory::~GameStateFactory()
        {

        }

        void GameStateFactory::vInitFactory()
        {
            m_StateFactory.Register<GameState::Initializing>(GameState::Initializing::g_Name);
            m_StateFactory.Register<GameState::SplashScreen>(GameState::SplashScreen::g_Name);
            m_StateFactory.Register<GameState::Paused>(GameState::Paused::g_Name);
            m_StateFactory.Register<GameState::MainMenu>(GameState::MainMenu::g_Name);
            m_StateFactory.Register<GameState::NewGame>(GameState::NewGame::g_Name);
            m_StateFactory.Register<GameState::Running>(GameState::Running::g_Name);
            m_StateFactory.Register<GameState::GameOver>(GameState::GameOver::g_Name);
            m_StateFactory.Register<GameState::Exiting>(GameState::Exiting::g_Name);
        }
    }

}
