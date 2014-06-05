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

#include "GameOver.h"

namespace pg
{

    namespace GameState
    {

        const char* GameOver::g_Name = "GameOver";

        GameOver::GameOver()
        {

        }

        GameOver::~GameOver()
        {

        }

        bool GameOver::vInit(uge::BaseGameLogic* pGameLogic)
        {
            m_pGameLogic = pGameLogic;

            return true;
        }

        bool GameOver::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool GameOver::vDestroy()
        {
            return true;
        }

        bool GameOver::vOnUpdate(unsigned long timeElapsed)
        {
            return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
        }

        bool GameOver::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string GameOver::vGetName() const
        {
            return g_Name;
        }

    }

}
