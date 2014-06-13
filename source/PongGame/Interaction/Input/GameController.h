/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#pragma once

#include <Engine/GameController/GameController.h>

#include <Core/PlayerProfile/InputSettings/InputSettings.h>
#include <Core/PlayerProfile/OutputSettings/WindowSettings.h>

#include <IO/Input/InputDevice/Implementation/OIS/OISMouse.h>
#include <IO/Input/InputDevice/Implementation/OIS/OISKeyboard.h>

#include "InputTypes.h"

namespace pg
{

    class GameController : public uge::GameController
    {
    public:
        GameController(const uge::WindowSettings& windowSettings, size_t windowHandle);

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
        uge::WindowSettings m_WindowSettings;
        size_t m_WindowHandle;

        bool m_LastPlayerMoveLeft;
        bool m_LastPlayerMoveRight;

        bool m_LastOpponentMoveLeft;
        bool m_LastOpponentMoveRight;

        uge::InputDevice::OISKeyboard m_Keyboard;
        uge::InputDevice::OISMouse m_Mouse;
    };

}
