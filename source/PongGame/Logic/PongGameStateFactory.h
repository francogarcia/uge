#pragma once

#include <Engine/GameLogic/GameState/GameStateFactory.h>

#include "PongStates.h"

namespace PongState
{

    class PongGameStateFactory : public uge::GameStateFactory
    {
    public:
        PongGameStateFactory();
        ~PongGameStateFactory();

    protected:
        virtual void vInitFactory() override;
    };

}
