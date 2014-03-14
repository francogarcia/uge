#pragma once

#include <Engine/GameLogic/GameState/GameStateFactory.h>

#include "GameStates.h"

namespace sg
{

namespace GameState
{

    class GameStateFactory : public uge::GameStateFactory
    {
    public:
        GameStateFactory();
        ~GameStateFactory();

    protected:
        virtual void vInitFactory() override;
    };

}

}
