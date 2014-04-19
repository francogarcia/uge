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
 */

#pragma once

#include <IO/Input/InputDevice/Keyboard.h>

#include "OISDevice.h"

namespace uge
{
    namespace InputDevice
    {
        class OISKeyboard : public Keyboard, public OIS::KeyListener
        {
        public:
            OISKeyboard(InputMapping::InputMapper& inputMapper, size_t windowHandle);
            virtual ~OISKeyboard();

            virtual bool vInit() override;
            virtual bool vDestroy() override;

            virtual bool vUpdate(unsigned long timeElapsed) override;

            // OIS virtual methods.
        protected:
            virtual bool keyPressed(const OIS::KeyEvent& keyEvent) override;

            virtual bool keyReleased(const OIS::KeyEvent& keyEvent) override;

        private:
            static RawInput::Key FromOIS(const OIS::KeyCode& key);
            static OIS::KeyCode ToOIS(const RawInput::Key& key);

        private:
            InputMapping::InputMapper& m_InputMapper;

            // OIS
            OISDevice m_OIS;
            OIS::Keyboard* m_pKeyboard;
        };
    }
}
