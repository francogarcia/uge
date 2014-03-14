#include "SpaceshipGameStd.h"

#include "GameController.h"

#include <Core/Events/IEventManager.h>

#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "../Events/GameEvents.h"

namespace sg
{

GameController::GameController(const uge::GraphicalPreferences::WindowSettings& windowSettings, size_t windowHandle)
    : m_WindowSettings(windowSettings),
      m_WindowHandle(windowHandle),
      m_Keyboard(m_InputMapper, windowHandle),
      m_Mouse(m_InputMapper, windowSettings, windowHandle)
{

}

GameController::~GameController()
{

}

bool GameController::vInit()
{
    if (!uge::GameController::vInit())
    {
        return false;
    }

    m_Keyboard.vInit();
    AddInputDevice(&m_Keyboard);

    m_Mouse.vInit();
    m_Mouse.vSetWindowSize(m_WindowSettings.width, m_WindowSettings.height);
    AddInputDevice(&m_Mouse);

    m_LastPlayer1MoveUp = false;
    m_LastPlayer1MoveDown = false;

    m_LastPlayer2MoveUp = false;
    m_LastPlayer2MoveDown = false;

    return true;
}

bool GameController::vDestroy()
{
    if (!uge::GameController::vDestroy())
    {
        return false;
    }

    return true;
}

bool GameController::vUpdate(unsigned long timeElapsed)
{
    if (!uge::GameController::vUpdate(timeElapsed))
    {
        return false;
    }

    return true;
}

void GameController::PongGameInputCallback(uge::InputMapping::MappedInput& inputs)
{

}

const std::string GameController::vGetInputContextListFilename()
{
    return std::string("data/game/commands/input_context_list.xml");
}

const uge::InputMapping::RawInputToInputTypeCallbacks GameController::vGetInputConverterDelegates()
{
    uge::InputMapping::RawInputToInputTypeCallbacks callbacks;
    callbacks.StringToRawInputButton = &uge::InputDevice::Keyboard::StringToRawInputButton;
    callbacks.StringToRawInputMouseButton = &uge::InputDevice::Mouse::StringToRawInputMouseButton;
    callbacks.StringToRawInputMouseAxis = &uge::InputDevice::Mouse::StringToRawInputMouseAxis;

    return callbacks;
}

const std::vector<std::string> GameController::vGetInputContexts()
{
    std::vector<std::string> inputContexts;
    inputContexts.push_back("game_commands");

    return inputContexts;
}

std::vector<uge::GameController::MappedInputDelegate> GameController::vGetMappedInputDelegates()
{
    std::vector<uge::GameController::MappedInputDelegate> mappedInputCallbacks;

    uge::GameController::MappedInputDelegate mappedInputDelegate;
    mappedInputDelegate.callback = fastdelegate::MakeDelegate(this, &GameController::PongGameInputCallback);
    mappedInputDelegate.priority = 0;

    mappedInputCallbacks.push_back(mappedInputDelegate);

    return mappedInputCallbacks;
}

}
