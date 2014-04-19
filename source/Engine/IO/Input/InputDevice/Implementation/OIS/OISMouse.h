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

#include <Core/PlayerProfile/GraphicalPreferences.h>

#include <IO/Input/InputDevice/Mouse.h>

#include "OISDevice.h"

namespace uge
{
    namespace InputDevice
    {
        class OISMouse : public Mouse, public OIS::MouseListener
        {
        public:
            OISMouse(InputMapping::InputMapper& inputMapper, const GraphicalPreferences::WindowSettings& windowSettings, size_t windowHandle);
            virtual ~OISMouse();

            virtual bool vInit() override;
            virtual bool vDestroy() override;

            virtual bool vUpdate(unsigned long timeElapsed) override;

            virtual void vSetWindowSize(unsigned int windowWidth, unsigned int windowHeight) override;

            // IOS
        protected:
            virtual bool mouseMoved(const OIS::MouseEvent& mouseEvent);

            virtual bool mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID);

            virtual bool mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID);

        private:
            static RawInput::MouseButton FromOIS(const OIS::MouseButtonID& buttonID);
            static OIS::MouseButtonID ToOIS(const RawInput::MouseButton& button);

        private:
            GraphicalPreferences::WindowSettings m_WindowSettings;

            InputMapping::InputMapper& m_InputMapper;

            // OIS
            OISDevice m_OIS;
            OIS::Mouse* m_pMouse;

            int m_LastX;
            int m_LastY;
        };
    }
}
