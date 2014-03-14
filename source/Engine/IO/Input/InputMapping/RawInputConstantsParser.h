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