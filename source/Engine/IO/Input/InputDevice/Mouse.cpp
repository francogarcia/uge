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

#include "GameEngineStd.h"

#include "Mouse.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{
    namespace InputDevice
    {
        Mouse::Mouse()
        {

        }

        Mouse::~Mouse()
        {

        }

        bool Mouse::vInit()
        {
            return true;
        }

        bool Mouse::vDestroy()
        {
            return true;
        }

        bool Mouse::vUpdate(unsigned long timeElapsed)
        {
            return true;
        }

        // TODO / FIXME: Swap to this after MSVC fixes the bug.
        //uge::RawInput::MouseButton StringToRawInputMouseButton(const std::string& buttonName)
        void Mouse::StringToRawInputMouseButton(const std::string& buttonName, uge::RawInput::MouseButton& button)
        {
            //TODO: in the future, use compile-time hash.
            //std::size_t buttonNameHash = std::hash<std::string>()(buttonName);
            //switch (buttonNameHash)
            //{
            //case const_hash("KC_UNASSIGNED"):
            //    return uge::RawInput::Key::KC_KC_UNASSIGNED;
            //};
            std::string upperButtonName = uge::StringToUpper(buttonName);
            if (upperButtonName == "MB_LEFT")
            {
                button = uge::RawInput::MouseButton::LEFT;
                return;
            }
            else if (upperButtonName == "MB_RIGHT")
            {
                button = uge::RawInput::MouseButton::RIGHT;
                return;
            }
            else if (upperButtonName == "MB_MIDDLE")
            {
                button = uge::RawInput::MouseButton::MIDDLE;
                return;
            }
            else if (upperButtonName == "MB_3")
            {
                button = uge::RawInput::MouseButton::BUTTON_3;
                return;
            }
            else if (upperButtonName == "MB_4")
            {
                button = uge::RawInput::MouseButton::BUTTON_4;
                return;
            }
            else if (upperButtonName == "MB_5")
            {
                button = uge::RawInput::MouseButton::BUTTON_5;
                return;
            }
            else if (upperButtonName == "MB_6")
            {
                button = uge::RawInput::MouseButton::BUTTON_6;
                return;
            }
            else if (upperButtonName == "MB_7")
            {
                button = uge::RawInput::MouseButton::BUTTON_7;
                return;
            }

            LOG_ERROR("Invalid value!");
        }

        // TODO / FIXME: Swap to this after MSVC fixes the bug.
        //uge::RawInput::MouseAxis StringToRawInputAxis(const std::string& buttonName)
        void Mouse::StringToRawInputMouseAxis(const std::string& buttonName, uge::RawInput::MouseAxis& button)
        {
            //TODO: in the future, use compile-time hash.
            //std::size_t buttonNameHash = std::hash<std::string>()(buttonName);
            //switch (buttonNameHash)
            //{
            //case const_hash("KC_UNASSIGNED"):
            //    return uge::RawInput::Key::KC_KC_UNASSIGNED;
            //};
            std::string upperButtonName = uge::StringToUpper(buttonName);
            if (upperButtonName == "MOUSE_X")
            {
                button = uge::RawInput::MouseAxis::MOUSE_X;
                return;
            }
            else if (upperButtonName == "MOUSE_Y")
            {
                button = uge::RawInput::MouseAxis::MOUSE_Y;
                return;
            }

            LOG_ERROR("Invalid value!");
        }
    }
}
