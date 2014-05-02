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

#include "OISMouse.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{
    namespace InputDevice
    {
        OISMouse::OISMouse(InputMapping::InputMapper& inputMapper,
                           const WindowSettings& windowSettings,
                           size_t windowHandle)
            : m_WindowSettings(windowSettings),
              m_InputMapper(inputMapper),
              m_OIS(windowHandle),
              m_pMouse(nullptr),
              m_LastX(0),
              m_LastY(0)
        {

        }

        OISMouse::~OISMouse()
        {

        }

        bool OISMouse::vInit()
        {
            if (!m_OIS.Init())
            {
                return false;
            }

            m_pMouse = static_cast<OIS::Mouse*>(m_OIS.CreateInputObject(OIS::OISMouse, true));
            assert(m_pMouse != nullptr);

            m_pMouse->setEventCallback(this);

            // TODO : handle window resizing.
            //windowResized(m_pWindow);

            m_pMouse->capture();
            const OIS::MouseState& mouseState = m_pMouse->getMouseState();
            m_LastX = mouseState.X.abs;
            m_LastY = mouseState.Y.abs;

            return true;
        }

        bool OISMouse::vDestroy()
        {
            m_OIS.DestroyInputObject(m_pMouse);

            return true;
        }

        bool OISMouse::vUpdate(unsigned long timeElapsed)
        {
            m_pMouse->capture();

            return true;
        }

        void OISMouse::vSetWindowSize(unsigned int windowWidth, unsigned int windowHeight)
        {
            const OIS::MouseState& mouseState = m_pMouse->getMouseState();
            mouseState.width = windowWidth;
            mouseState.height = windowHeight;

            WindowSettings::WindowSettingsData windowSettingsData = m_WindowSettings.GetWindowSettingsData();
            windowSettingsData.width = windowWidth;
            windowSettingsData.height = windowHeight;
        }

        bool OISMouse::mouseMoved(const OIS::MouseEvent& mouseEvent)
        {
            const OIS::MouseState& mouseState = mouseEvent.state;
            int x = mouseState.X.abs;
            int y = mouseState.Y.abs;

            m_InputMapper.SetRawAxisValue(RawInput::MouseAxis::MOUSE_X, static_cast<float>(x - m_LastX));
            m_InputMapper.SetRawAxisValue(RawInput::MouseAxis::MOUSE_Y, static_cast<float>(y - m_LastY));

            m_LastX = x;
            m_LastY = y;

            return true;
        }

        bool OISMouse::mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID)
        {
            RawInput::MouseButton button = FromOIS(buttonID);
            m_InputMapper.SetRawButtonState(button, true, false);

            return true;
        }

        bool OISMouse::mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID)
        {
            RawInput::MouseButton button = FromOIS(buttonID);
            m_InputMapper.SetRawButtonState(button, false, true);

            return true;
        }

        RawInput::MouseButton OISMouse::FromOIS(const OIS::MouseButtonID& buttonID)
        {
            switch (buttonID)
            {
                case OIS::MB_Left:
                    return RawInput::MouseButton::LEFT;

                case OIS::MB_Right:
                    return RawInput::MouseButton::RIGHT;

                case OIS::MB_Middle:
                    return RawInput::MouseButton::MIDDLE;

                case OIS::MB_Button3:
                    return RawInput::MouseButton::BUTTON_3;

                case OIS::MB_Button4:
                    return RawInput::MouseButton::BUTTON_4;

                case OIS::MB_Button5:
                    return RawInput::MouseButton::BUTTON_5;

                case OIS::MB_Button6:
                    return RawInput::MouseButton::BUTTON_6;

                case OIS::MB_Button7:
                    return RawInput::MouseButton::BUTTON_7;
            }

            LOG_ERROR("Invalid key code!");
            return RawInput::MouseButton::BUTTON_7;
        }

        OIS::MouseButtonID OISMouse::ToOIS(const RawInput::MouseButton& button)
        {
            switch (button)
            {
                case RawInput::MouseButton::LEFT:
                    return OIS::MB_Left;

                case RawInput::MouseButton::RIGHT:
                    return OIS::MB_Right;

                case RawInput::MouseButton::MIDDLE:
                    return OIS::MB_Middle;

                case RawInput::MouseButton::BUTTON_3:
                    return OIS::MB_Button3;

                case RawInput::MouseButton::BUTTON_4:
                    return OIS::MB_Button4;

                case RawInput::MouseButton::BUTTON_5:
                    return OIS::MB_Button5;

                case RawInput::MouseButton::BUTTON_6:
                    return OIS::MB_Button6;

                case RawInput::MouseButton::BUTTON_7:
                    return OIS::MB_Button7;
            }

            LOG_ERROR("Invalid key code!");
            return OIS::MB_Button7;
        }
    }
}
