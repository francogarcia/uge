#include "SpaceshipGameStd.h"

#include "GameStates.h"

namespace sg
{

namespace GameState
{

    Initializing::Initializing()
    {

    }

    Initializing::~Initializing()
    {

    }

    bool Initializing::vInit(uge::BaseGameLogic* pGameLogic)
    {
        std::cout << "[Initializing] Initializing the game!" << std::endl;

        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool Initializing::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool Initializing::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool Initializing::vOnUpdate(unsigned long timeElapsed)
    {
        bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

        m_pGameLogic->vChangeGameState(SplashScreen::g_Name);

        return bSuccess;
    }

    bool Initializing::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    SplashScreen::SplashScreen()
    {

    }

    SplashScreen::~SplashScreen()
    {

    }

    const char* SplashScreen::g_Name = "SplashScreen";

    bool SplashScreen::vInit(uge::BaseGameLogic* pGameLogic)
    {
        std::cout << "[SplashScreen] Splash screen!" << std::endl;

        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool SplashScreen::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool SplashScreen::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool SplashScreen::vOnUpdate(unsigned long timeElapsed)
    {
        bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

        m_pGameLogic->vChangeGameState(MainMenu::g_Name);

        return bSuccess;
    }

    bool SplashScreen::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string SplashScreen::vGetName() const
    {
        return g_Name;
    }

    const char* MainMenu::g_Name = "MainMenu";

    MainMenu::MainMenu()
    {

    }

    MainMenu::~MainMenu()
    {

    }

    bool MainMenu::vInit(uge::BaseGameLogic* pGameLogic)
    {
        std::cout << "[MainMenu] Main menu!" << std::endl;

        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool MainMenu::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool MainMenu::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool MainMenu::vOnUpdate(unsigned long timeElapsed)
    {
        bool bSuccess = uge::GameState::BaseGameState::vOnUpdate(timeElapsed);

        m_pGameLogic->vChangeGameState(uge::GameState::Running::g_Name);

        return bSuccess;
    }

    bool MainMenu::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string MainMenu::vGetName() const
    {
        return g_Name;
    }

    Running::Running()
    {

    }

    Running::~Running()
    {

    }

    bool Running::vInit(uge::BaseGameLogic* pGameLogic)
    {
        std::cout << "[Running] Game is running!" << std::endl;

        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool Running::vTailorToProfile(const std::string& xmlResourceFilename)
    {

        return true;
    }

    bool Running::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool Running::vOnUpdate(unsigned long timeElapsed)
    {
        bool bSuccess = uge::GameState::Running::vOnUpdate(timeElapsed);

        return bSuccess;
    }

    bool Running::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const char* Paused::g_Name = "Paused";

    Paused::Paused()
    {

    }

    Paused::~Paused()
    {

    }

    bool Paused::vInit(uge::BaseGameLogic* pGameLogic)
    {
        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool Paused::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool Paused::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool Paused::vOnUpdate(unsigned long timeElapsed)
    {
        return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
    }

    bool Paused::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string Paused::vGetName() const
    {
        return g_Name;
    }

    const char* HiScores::g_Name = "HiScores";

    HiScores::HiScores()
    {

    }

    HiScores::~HiScores()
    {

    }

    bool HiScores::vInit(uge::BaseGameLogic* pGameLogic)
    {
        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool HiScores::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool HiScores::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool HiScores::vOnUpdate(unsigned long timeElapsed)
    {
        return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
    }

    bool HiScores::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string HiScores::vGetName() const
    {
        return g_Name;
    }

    const char* NewGame::g_Name = "NewGame";

    NewGame::NewGame()
    {

    }

    NewGame::~NewGame()
    {

    }

    bool NewGame::vInit(uge::BaseGameLogic* pGameLogic)
    {
        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool NewGame::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool NewGame::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool NewGame::vOnUpdate(unsigned long timeElapsed)
    {
        return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
    }

    bool NewGame::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string NewGame::vGetName() const
    {
        return g_Name;
    }

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

    const char* Exiting::g_Name = "Exiting";

    Exiting::Exiting()
    {

    }

    Exiting::~Exiting()
    {

    }

    bool Exiting::vInit(uge::BaseGameLogic* pGameLogic)
    {
        uge::GameState::BaseGameState::vInit(pGameLogic);

        return true;
    }

    bool Exiting::vTailorToProfile(const std::string& xmlResourceFilename)
    {
        return true;
    }

    bool Exiting::vDestroy()
    {
        uge::GameState::BaseGameState::vDestroy();

        return true;
    }

    bool Exiting::vOnUpdate(unsigned long timeElapsed)
    {
        return uge::GameState::BaseGameState::vOnUpdate(timeElapsed);
    }

    bool Exiting::vOnRender(unsigned long timeElapsed)
    {
        return true;
    }

    const std::string Exiting::vGetName() const
    {
        return g_Name;
    }

}

}
