#pragma once

#include "IGameState.h"

namespace uge
{

    class GameStateStack
    {
    public:
        GameStateStack();
        ~GameStateStack();

        void PushGameState(IGameState* pGameState);
        void PopGameState();

        IGameState* GetCurrentGameState() const;

    private:
        std::stack<IGameState*> m_States;
    };

}
