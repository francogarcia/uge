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

//
// Input Mapping Demo
// By Mike Lewis, June 2011
// http://scribblings-by-apoch.googlecode.com/
//
// Wrapper class for mapping inputs
//

#pragma once

// Dependencies
#include <IO/Input/RawInputConstants.h>

#include "GameCommand.h"
#include "InputTypes.h"
#include "RawInputConstantsParser.h"

// Only call Dispatch when a new event happens.
// Remove this to restore the old behaviour, allowing states to be
// continuosly sent to the application.
#define UGE_EVENT_BASED_INPUT_DISPATCHING 1

namespace uge
{

    namespace InputMapping
    {

        // Forward declarations
        class InputContext;

        // Helper structure
        class MappedInput
        {
        public:
            MappedInput();
            ~MappedInput();

            bool IsActionEnabled(Action action);
            bool IsStateEnabled(State state);
            bool IsRangeEnabled(Range range);
            float GetRangeValue(Range range);

            void AddAction(Action action);
            void AddState(State state);
            void AddRange(Range range, float fRangeValue);

            // Consumption helpers
            void EatAction(Action action);
            void EatState(State state);
            void EatRange(Range range);

            void ClearActions();
            void ClearStates();
            void ClearRanges();

        private:
            std::set<Action> m_Actions;
            std::set<State> m_States;
            std::map<Range, float> m_Ranges;
        };

        // TODO: use C++11 std::function instead.
        // Handy type shortcuts
        //typedef std::function<void(MappedInput&)> InputCallback;
        typedef fastdelegate::FastDelegate1<MappedInput&> InputCallback;

        class InputMapper
        {
            // Construction and destruction
        public:
            InputMapper();
            ~InputMapper();

            // Raw input interface
            void Init(const std::string& inputContextListFilename, const RawInputToInputTypeCallbacks& callbacks);
            void Destroy();

            void Clear();
            void SetRawButtonState(RawInput::Key button, bool bIsPressed, bool bWasPreviouslyPressed);
            void SetRawButtonState(RawInput::MouseButton button, bool bIsPressed, bool bWasPreviouslyPressed);
            void SetRawAxisValue(RawInput::MouseAxis axis, float fValue);

            // Input dispatching interface
            void Dispatch() const;

            // Input callback registration interface
            void AddCallback(InputCallback callback, int priority);

            // Context management interface
            void PushContext(const std::string& name);
            void PopContext();

            // Internal helpers
        private:
            // TODO: write these funcion as templates.
            bool MapButtonToAction(RawInput::Key button, Action& action) const;
            bool MapButtonToAction(RawInput::MouseButton button, Action& action) const;
            bool MapButtonToState(RawInput::Key button, State& state) const;
            bool MapButtonToState(RawInput::MouseButton button, State& state) const;
            void MapAndEatButton(RawInput::Key button);
            void MapAndEatButton(RawInput::MouseButton button);

            GameCommand m_GameCommands;

            // Internal tracking
            std::map<std::string, InputContext*> m_InputContexts;
            std::list<InputContext*> m_ActiveContexts;

            std::multimap<int, InputCallback> m_CallbackTable;

            MappedInput m_CurrentMappedInput;

#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            bool m_bChanged;
#endif
        };

    }

}
