#pragma once

#include <Engine/GameController/GameController.h>

#include <Core/PlayerProfile/GraphicalPreferences.h>

#include <IO/Input/InputDevice/Implementation/OIS/OISMouse.h>
#include <IO/Input/InputDevice/Implementation/OIS/OISKeyboard.h>

#include "PongGameInputTypes.h"

class PongGameController : public uge::GameController
{
public:
    PongGameController(const uge::GraphicalPreferences::WindowSettings& windowSettings, size_t windowHandle);

    ~PongGameController();

    virtual bool vInit() override;
    virtual bool vDestroy() override;

    virtual bool vUpdate(unsigned long timeElapsed) override;

    void PongGameInputCallback(uge::InputMapping::MappedInput& inputs);

protected:
    virtual const std::string vGetInputContextListFilename() override;
    virtual const uge::InputMapping::RawInputToInputTypeCallbacks vGetInputConverterDelegates() override;
    virtual const std::vector<std::string> vGetInputContexts() override;
    virtual std::vector<uge::GameController::MappedInputDelegate> vGetMappedInputDelegates() override;

private:
    uge::GraphicalPreferences::WindowSettings m_WindowSettings;
    size_t m_WindowHandle;

    bool m_LastPlayer1MoveUp;
    bool m_LastPlayer1MoveDown;

    bool m_LastPlayer2MoveUp;
    bool m_LastPlayer2MoveDown;

    uge::InputDevice::OISKeyboard m_Keyboard;
    uge::InputDevice::OISMouse m_Mouse;
};
