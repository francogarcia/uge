/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#include "IInputDevice.h"

namespace uge
{
    namespace InputDevice
    {
        class Mouse : public IInputDevice
        {
        public:
            Mouse();
            virtual ~Mouse();

            virtual bool vInit() override;
            virtual bool vDestroy() override;

            virtual bool vUpdate(unsigned long timeElapsed) override;

            virtual void vSetWindowSize(unsigned int windowWidth, unsigned int windowHeight) = 0;

            static void StringToRawInputMouseButton(const std::string& buttonName, uge::RawInput::MouseButton& button);
            static void StringToRawInputMouseAxis(const std::string& buttonName, uge::RawInput::MouseAxis& button);
        };
    }
}
