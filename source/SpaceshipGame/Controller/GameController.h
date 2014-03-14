#pragma once

#include <Engine/GameController/GameController.h>

#include <Core/PlayerProfile/GraphicalPreferences.h>

#include <IO/Input/InputDevice/Implementation/OIS/OISMouse.h>
#include <IO/Input/InputDevice/Implementation/OIS/OISKeyboard.h>

#include "InputTypes.h"

namespace sg
{

    class GameController : public uge::GameController
    {
    public:
        GameController(const uge::GraphicalPreferences::WindowSettings& windowSettings, size_t windowHandle);

        ~GameController();

        virtual bool vInit() override;
        virtual bool vDestroy() override;

        virtual bool vUpdate(unsigned long timeElapsed) override;

        void InputCallback(uge::InputMapping::MappedInput& inputs);

    protected:
        virtual const std::string vGetInputContextListFilename() override;
        virtual const uge::InputMapping::RawInputToInputTypeCallbacks vGetInputConverterDelegates() override;
        virtual const std::vector<std::string> vGetInputContexts() override;
        virtual std::vector<uge::GameController::MappedInputDelegate> vGetMappedInputDelegates() override;

    private:
        uge::GraphicalPreferences::WindowSettings m_WindowSettings;
        size_t m_WindowHandle;

        bool m_LastPlayerMoveLeft;
        bool m_LastPlayerMoveRight;

        uge::InputDevice::OISKeyboard m_Keyboard;
        uge::InputDevice::OISMouse m_Mouse;
    };

}
