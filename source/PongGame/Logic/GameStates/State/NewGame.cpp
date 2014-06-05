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

#include "NewGame.h"

namespace pg
{

    namespace GameState
    {

        const char* NewGame::g_Name = "NewGame";

        NewGame::NewGame()
        {

        }

        NewGame::~NewGame()
        {

        }

        bool NewGame::vInit(uge::BaseGameLogic* pGameLogic)
        {
            std::cout << "[NewGame] NewGame!" << std::endl;

            uge::GameState::BaseGameState::vInit(pGameLogic);

            return true;
        }

        bool NewGame::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool NewGame::vDestroy()
        {
            uge::GameState::BaseGameState::vDestroy();

            return true;
        }

        bool NewGame::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(uge::GameState::Running::g_Name);

            return bSuccess;
        }

        bool NewGame::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string NewGame::vGetName() const
        {
            return g_Name;
        }

    }

}
