//
// Input Mapping Demo
// By Mike Lewis, June 2011
// http://scribblings-by-apoch.googlecode.com/
//
// Wrapper class for managing input contexts
//

#pragma once

#include <IO/Input/RawInputConstants.h>

#include "GameCommand.h"
#include "InputTypes.h"
#include "RangeConverter.h"
#include "RawInputConstantsParser.h"

namespace uge
{

    namespace InputMapping
    {

        class InputContext
        {
            // Construction and destruction
        public:
            explicit InputContext(const GameCommand& gameCommands, const std::string& inputContextFilename, const RawInputToInputTypeCallbacks& callbacks);
            ~InputContext();

            // Mapping interface
            // TODO: write these funcion as templates.
            bool MapButtonToAction(RawInput::Key button, Action& out) const;
            bool MapButtonToAction(RawInput::MouseButton button, Action& out) const;
            bool MapButtonToState(RawInput::Key button, State& out) const;
            bool MapButtonToState(RawInput::MouseButton button, State& out) const;
            bool MapAxisToRange(RawInput::MouseAxis axis, Range& out) const;

            float GetSensitivity(Range range) const;

            const RangeConverter& GetConversions() const;

            // Internal tracking
        private:    
            std::map<RawInput::Key, Action> m_ActionButtons;
            std::map<RawInput::MouseButton, Action> m_ActionMouseButtons;

            std::map<RawInput::Key, State> m_StateButtons;
            std::map<RawInput::MouseButton, State> m_StateMouseButtons;

            std::map<RawInput::MouseAxis, Range> m_RangeMouseAxes;

            std::map<Range, float> m_SensitivityMap;
            RangeConverter m_Conversions;
        };

    }

}
