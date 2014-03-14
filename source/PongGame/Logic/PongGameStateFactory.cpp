#include "PongGameStd.h"

#include "PongGameStateFactory.h"

namespace PongState
{
    PongGameStateFactory::PongGameStateFactory()
    {

    }

    PongGameStateFactory::~PongGameStateFactory()
    {

    }

    void PongGameStateFactory::vInitFactory()
    {
        //m_StateFactory.Register<PongState::Uninitialized>(PongState::Uninitialized::g_Name);
        m_StateFactory.Register<PongState::Initializing>(PongState::Initializing::g_Name);
        m_StateFactory.Register<PongState::SplashScreen>(PongState::SplashScreen::g_Name);
        m_StateFactory.Register<PongState::Paused>(PongState::Paused::g_Name);
        m_StateFactory.Register<PongState::HiScores>(PongState::HiScores::g_Name);
        m_StateFactory.Register<PongState::MainMenu>(PongState::MainMenu::g_Name);
        m_StateFactory.Register<PongState::NewGame>(PongState::NewGame::g_Name);
        m_StateFactory.Register<PongState::Running>(PongState::Running::g_Name);
        m_StateFactory.Register<PongState::GameOver>(PongState::GameOver::g_Name);
        m_StateFactory.Register<PongState::Exiting>(PongState::Exiting::g_Name);
    }
}
