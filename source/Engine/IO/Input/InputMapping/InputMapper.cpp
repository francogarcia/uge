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

#include "GameEngineStd.h"

#include "InputMapper.h"

#include "InputContext.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/File/XMLFile.h>

namespace uge
{

    namespace InputMapping
    {

        MappedInput::MappedInput()
        {

        }

        MappedInput::~MappedInput()
        {

        }

        bool MappedInput::IsActionEnabled(Action action)
        {
            return (m_Actions.find(action) != m_Actions.end());
        }

        bool MappedInput::IsStateEnabled(State state)
        {
            return (m_States.find(state) != m_States.end());
        }

        bool MappedInput::IsRangeEnabled(Range range)
        {
            return (m_Ranges.find(range) != m_Ranges.end());
        }

        float MappedInput::GetRangeValue(Range range)
        {
            assert(m_Ranges.find(range) != m_Ranges.end());

            return m_Ranges[range];
        }

        void MappedInput::AddAction(Action action)
        {
            m_Actions.insert(action);
        }

        void MappedInput::AddState(State state)
        {
            m_States.insert(state);
        }

        void MappedInput::AddRange(Range range, float fRangeValue)
        {
            m_Ranges[range] = fRangeValue;
        }

        void MappedInput::EatAction(Action action)
        {
            m_Actions.erase(action);
        }

        void MappedInput::EatState(State state)
        {
            m_States.erase(state);
        }

        void MappedInput::EatRange(Range range)
        {
            std::map<Range, float>::iterator iter = m_Ranges.find(range);
            if (iter != m_Ranges.end())
            {
                m_Ranges.erase(iter);
            }
        }

        void MappedInput::ClearActions()
        {
            m_Actions.clear();
        }

        void MappedInput::ClearStates()
        {
            m_States.clear();
        }

        void MappedInput::ClearRanges()
        {
            m_Ranges.clear();
        }

        //
        // Construct and initialize an input mapper
        //
        InputMapper::InputMapper()
        {

        }

        //
        // Destruct and clean up an input mapper
        //
        InputMapper::~InputMapper()
        {
            Destroy();
        }


        void InputMapper::Init(const std::string& inputContextListFilename,
                               const RawInputToInputTypeCallbacks& callbacks)
        {
            XMLFile inputContextList;
            if (!inputContextList.OpenFile(inputContextListFilename, File::FileMode::FileReadOnly))
            {
                LOG_FATAL("ERROR: Could not load the input context list file.");
            }

            XMLElement xmlRootElement(inputContextList.GetRootElement());
            assert(xmlRootElement.IsGood());
            int total_files = 0;
            for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement();
                 xmlElement.IsGood();
                 xmlElement = xmlElement.GetNextSiblingElement())
            {
                std::string inputContextName;
                xmlElement.GetAttribute("name", &inputContextName);

                XMLElement gameCommandsElement(xmlElement.GetFirstChildElement("Commands"));
                std::string gameCommandListFilename;
                gameCommandsElement.GetAttribute("resource", &gameCommandListFilename);
                m_GameCommands.Init(gameCommandListFilename);

                std::string inputContextFilename;
                XMLElement inputMappingElement(xmlElement.GetFirstChildElement("InputMapping"));
                inputMappingElement.GetAttribute("resource", &inputContextFilename);
                m_InputContexts[inputContextName] = new InputContext(m_GameCommands, inputContextFilename, callbacks);
            }

#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            m_bChanged = false;
#endif
        }

        void InputMapper::Destroy()
        {
            Clear();

            for (std::map<std::string, InputContext*>::iterator iter = m_InputContexts.begin(); iter != m_InputContexts.end(); ++iter)
            {
                delete iter->second;
            }
        }

        //
        // Clear all mapped input
        //
        void InputMapper::Clear()
        {
            m_CurrentMappedInput.ClearActions();
            m_CurrentMappedInput.ClearRanges();
            // Note: we do NOT clear states, because they need to remain set
            // across frames so that they don't accidentally show "off" for
            // a tick or two while the raw input is still pending.

#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            m_bChanged = false;
#endif
        }

        //
        // Set the state of a raw button
        //
        void InputMapper::SetRawButtonState(RawInput::Key button, bool bIsPressed, bool bWasPreviouslyPressed)
        {
            Action action;
            State state;

#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            m_bChanged = true;
#endif

            if (bIsPressed && !bWasPreviouslyPressed)
            {
                if (MapButtonToAction(button, action))
                {
                    m_CurrentMappedInput.AddAction(action);

                    return;
                }
            }

            if (bIsPressed)
            {
                if (MapButtonToState(button, state))
                {
                    m_CurrentMappedInput.AddState(state);

                    return;
                }
            }

            MapAndEatButton(button);
        }

        void InputMapper::SetRawButtonState(RawInput::MouseButton button, bool bIsPressed, bool bWasPreviouslyPressed)
        {
            Action action;
            State state;

#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            m_bChanged = true;
#endif

            if (bIsPressed && !bWasPreviouslyPressed)
            {
                if (MapButtonToAction(button, action))
                {
                    m_CurrentMappedInput.AddAction(action);

                    return;
                }
            }

            if (bIsPressed)
            {
                if (MapButtonToState(button, state))
                {
                    m_CurrentMappedInput.AddState(state);

                    return;
                }
            }

            MapAndEatButton(button);
        }

        //
        // Set the raw axis value of a given axis
        //
        void InputMapper::SetRawAxisValue(RawInput::MouseAxis axis, float fValue)
        {
#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            m_bChanged = true;
#endif

            for (std::list<InputContext*>::const_iterator iter = m_ActiveContexts.begin(); iter != m_ActiveContexts.end(); ++iter)
            {
                const InputContext* context = *iter;

                Range range;
                if (context->MapAxisToRange(axis, range))
                {
                    m_CurrentMappedInput.AddRange(range, context->GetConversions().Convert(range, fValue * context->GetSensitivity(range)));
                    break;
                }
            }
        }


        //
        // Dispatch input to all registered callbacks
        //
        void InputMapper::Dispatch() const
        {
#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            if (m_bChanged)
            {
#endif
                MappedInput input = m_CurrentMappedInput;
                for (std::multimap<int, InputCallback>::const_iterator iter = m_CallbackTable.begin(); iter != m_CallbackTable.end(); ++iter)
                {
                    iter->second(input);
                }
#ifdef UGE_EVENT_BASED_INPUT_DISPATCHING
            }
#endif
        }

        //
        // Add a callback to the dispatch table
        //
        void InputMapper::AddCallback(InputCallback callback, int priority)
        {
            m_CallbackTable.insert(std::make_pair(priority, callback));
        }


        //
        // Push an active input context onto the stack
        //
        void InputMapper::PushContext(const std::string& name)
        {
            std::map<std::string, InputContext*>::iterator iter = m_InputContexts.find(name);
            if (iter == m_InputContexts.end())
            {
                LOG_FATAL("Invalid input context pushed");
            }

            m_ActiveContexts.push_front(iter->second);
        }

        //
        // Pop the current input context off the stack
        //
        void InputMapper::PopContext()
        {
            if (m_ActiveContexts.empty())
            {
                LOG_FATAL("Cannot pop input context, no contexts active!");
            }

            m_ActiveContexts.pop_front();
        }


        //
        // Helper: map a button to an action in the active context(s)
        //
        bool InputMapper::MapButtonToAction(RawInput::Key button, Action& action) const
        {
            for (std::list<InputContext*>::const_iterator iter = m_ActiveContexts.begin(); iter != m_ActiveContexts.end(); ++iter)
            {
                const InputContext* context = *iter;

                if (context->MapButtonToAction(button, action))
                {
                    return true;
                }
            }

            return false;
        }

        bool InputMapper::MapButtonToAction(RawInput::MouseButton button, Action& action) const
        {
            for (std::list<InputContext*>::const_iterator iter = m_ActiveContexts.begin(); iter != m_ActiveContexts.end(); ++iter)
            {
                const InputContext* context = *iter;

                if (context->MapButtonToAction(button, action))
                {
                    return true;
                }
            }

            return false;
        }

        //
        // Helper: map a button to a state in the active context(s)
        //
        bool InputMapper::MapButtonToState(RawInput::Key button, State& state) const
        {
            for (std::list<InputContext*>::const_iterator iter = m_ActiveContexts.begin(); iter != m_ActiveContexts.end(); ++iter)
            {
                const InputContext* context = *iter;

                if (context->MapButtonToState(button, state))
                {
                    return true;
                }
            }

            return false;
        }

        bool InputMapper::MapButtonToState(RawInput::MouseButton button, State& state) const
        {
            for (std::list<InputContext*>::const_iterator iter = m_ActiveContexts.begin(); iter != m_ActiveContexts.end(); ++iter)
            {
                const InputContext* context = *iter;

                if (context->MapButtonToState(button, state))
                {
                    return true;
                }
            }

            return false;
        }

        //
        // Helper: eat all input mapped to a given button
        //
        void InputMapper::MapAndEatButton(RawInput::Key button)
        {
            Action action;
            State state;

            if (MapButtonToAction(button, action))
            {
                m_CurrentMappedInput.EatAction(action);
            }

            if (MapButtonToState(button, state))
            {
                m_CurrentMappedInput.EatState(state);
            }
        }

        void InputMapper::MapAndEatButton(RawInput::MouseButton button)
        {
            Action action;
            State state;

            if (MapButtonToAction(button, action))
            {
                m_CurrentMappedInput.EatAction(action);
            }

            if (MapButtonToState(button, state))
            {
                m_CurrentMappedInput.EatState(state);
            }
        }

    }
}
