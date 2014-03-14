#include "SpaceshipGameStd.h"

#include "GameStateFactory.h"

namespace sg
{

namespace GameState
{
    GameStateFactory::GameStateFactory()
    {

    }

    GameStateFactory::~GameStateFactory()
    {

    }

    void GameStateFactory::vInitFactory()
    {
        //m_StateFactory.Register<GameState::Uninitialized>(GameState::Uninitialized::g_Name);
        m_StateFactory.Register<GameState::Initializing>(GameState::Initializing::g_Name);
        m_StateFactory.Register<GameState::SplashScreen>(GameState::SplashScreen::g_Name);
        m_StateFactory.Register<GameState::Paused>(GameState::Paused::g_Name);
        m_StateFactory.Register<GameState::MainMenu>(GameState::MainMenu::g_Name);
        m_StateFactory.Register<GameState::NewGame>(GameState::NewGame::g_Name);
        m_StateFactory.Register<GameState::Running>(GameState::Running::g_Name);
        m_StateFactory.Register<GameState::GameOver>(GameState::GameOver::g_Name);
        m_StateFactory.Register<GameState::Exiting>(GameState::Exiting::g_Name);
    }
}

}
