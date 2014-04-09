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

#include "GameEngineStd.h"

#include <IO/Input/RawInputConstants.h>

namespace uge
{
    namespace InputMapping
    {
        // TODO / FIXME: Swap to this after MSVC fixes the bug.
        //typedef std::function<RawInput::Key(const std::string&)> StringToRawInputButtonCallback;
        //typedef std::function<RawInput::MouseButton(const std::string&)> StringToRawInputMouseButtonCallback;
        //typedef std::function<RawInput::MouseAxis(const std::string&)> StringToRawInputAxisCallback;

        // TODO: use C++11 functions instead.
        //typedef std::function<void(const std::string&, RawInput::Key&)> StringToRawInputButtonCallback;
        //typedef std::function<void(const std::string&, RawInput::MouseButton&)> StringToRawInputMouseButtonCallback;
        //typedef std::function<void(const std::string&, RawInput::MouseAxis&)> StringToRawInputMouseAxisCallback;

        typedef fastdelegate::FastDelegate2<const std::string&, RawInput::Key&> StringToRawInputButtonCallback;
        typedef fastdelegate::FastDelegate2<const std::string&, RawInput::MouseButton&> StringToRawInputMouseButtonCallback;
        typedef fastdelegate::FastDelegate2<const std::string&, RawInput::MouseAxis&> StringToRawInputMouseAxisCallback;

        struct RawInputToInputTypeCallbacks
        {
            StringToRawInputButtonCallback StringToRawInputButton;
            StringToRawInputMouseButtonCallback StringToRawInputMouseButton;
            StringToRawInputMouseAxisCallback StringToRawInputMouseAxis;
        };
    }
}
