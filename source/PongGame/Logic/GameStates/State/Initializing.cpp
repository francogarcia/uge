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

#include "Initializing.h"

// State transitions.
#include "SplashScreen.h"

namespace pg
{

    namespace GameState
    {

        Initializing::Initializing()
        {

        }

        Initializing::~Initializing()
        {

        }

        bool Initializing::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[Initializing] Initializing the game!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool Initializing::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Initializing::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool Initializing::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(SplashScreen::g_Name);

            return bSuccess;
        }

        bool Initializing::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

    }

}
