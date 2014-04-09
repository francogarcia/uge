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

#include "GameEngineStd.h"

#include "GameStateStack.h"

namespace uge
{
    GameStateStack::GameStateStack()
    {

    }

    GameStateStack::~GameStateStack()
    {

    }

    void GameStateStack::PushGameState(IGameState* pGameState)
    {
        assert(pGameState != nullptr && "Invalid game state!");

        m_States.push(pGameState);
    }

    void GameStateStack::PopGameState()
    {
        IGameState* pGameState = GetCurrentGameState();
        //pGameState->vDestroy();

        m_States.pop();
    }

    IGameState* GameStateStack::GetCurrentGameState() const
    {
        return m_States.top();
    }
}
