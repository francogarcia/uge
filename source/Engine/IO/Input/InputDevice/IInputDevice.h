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

#include <IO/Input/RawInputConstants.h>

#include <IO/Input/InputMapping/InputMapper.h>

namespace uge
{
    namespace InputDevice
    {
        class IInputDevice;
        typedef std::vector<IInputDevice*> InputDeviceList;

        class IInputDevice
        {
        public:
            IInputDevice();
            virtual ~IInputDevice();

            virtual bool vInit() = 0;
            virtual bool vDestroy() = 0;

            virtual bool vUpdate(unsigned long timeElapsed) = 0;
        };
    }
}
