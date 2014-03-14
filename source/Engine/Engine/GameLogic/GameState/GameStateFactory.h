#pragma once

#include <Utilities/PatternTemplates.h>

#include "IGameState.h"

#include "BaseGameState.h"

namespace uge
{

    class GameStateFactory
    {
    public:
        GameStateFactory();
        ~GameStateFactory();

        void Init();

        IGameState* CreateGameState(const std::string& stateName);

    protected:
        virtual void vInitFactory();

    protected:
        GenericObjectFactory<IGameState, std::string> m_StateFactory;
    };

}
