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
