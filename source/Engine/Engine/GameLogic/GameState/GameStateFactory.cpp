#include "GameEngineStd.h"

#include "GameStateFactory.h"

namespace uge
{
        GameStateFactory::GameStateFactory()
        {

        }

        GameStateFactory::~GameStateFactory()
        {

        }

        void GameStateFactory::Init()
        {
            vInitFactory();
        }

        IGameState* GameStateFactory::CreateGameState(const std::string& stateName)
        {
            IGameState* pGameState = m_StateFactory.Create(stateName);

            return pGameState;
        }

        void GameStateFactory::vInitFactory()
        {
            m_StateFactory.Register<GameState::Uninitialized>(GameState::Uninitialized::g_Name);
            m_StateFactory.Register<GameState::Initializing>(GameState::Initializing::g_Name);
            m_StateFactory.Register<GameState::Running>(GameState::Running::g_Name);
        }
}
