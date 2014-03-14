//
// Input Mapping Demo
// By Mike Lewis, June 2011
// http://scribblings-by-apoch.googlecode.com/
//
// Wrapper class for managing input contexts
//

#include "GameEngineStd.h"

#include "InputContext.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/File/XMLFile.h>

namespace uge
{

    namespace InputMapping
    {

        //
        // Construct and initialize an input context given data in a file
        //
        InputContext::InputContext(const GameCommand& gameCommands,
                                   const std::string& inputContextFilename,
                                   const RawInputToInputTypeCallbacks& callbacks)
            : m_Conversions()
        {
            XMLFile inputContextFile;
            if (!inputContextFile.OpenFile(inputContextFilename, File::FileMode::FileReadOnly))
            {
                LOG_FATAL("ERROR: Could not load the input context file.");
            }

            XMLElement xmlRootElement(inputContextFile.GetRootElement());
            assert(xmlRootElement.IsGood());
            // Read all actions.
            XMLElement actionElements(xmlRootElement.GetFirstChildElement("Actions"));
            for (XMLElement actionElement = actionElements.GetFirstChildElement();
                 actionElement.IsGood();
                 actionElement = actionElement.GetNextSiblingElement())
            {
                std::string actionName;
                actionElement.GetAttribute("game_command_name", &actionName);

                std::string inputValue;
                actionElement.GetAttribute("input_value", &inputValue);

                std::string inputDevice;
                actionElement.GetAttribute("device", &inputDevice);
                if (inputDevice == "keyboard")
                {
                    // TODO / FIXME : use this when MSVC fixes the bug.
                    //RawInput::Key buttonID = callbacks.StringToRawInputButton(inputValue);
                    RawInput::Key buttonID;
                    callbacks.StringToRawInputButton(inputValue, buttonID);
                    Action action = gameCommands.GetAction(actionName);
                    m_ActionButtons[buttonID] = action;
                }
                else if (inputDevice == "mouse")
                {
                    RawInput::MouseButton buttonID;
                    callbacks.StringToRawInputMouseButton(inputValue, buttonID);
                    Action action = gameCommands.GetAction(actionName);
                    m_ActionMouseButtons[buttonID] = action;
                }
            }

            // Read all states.
            XMLElement stateElements(xmlRootElement.GetFirstChildElement("States"));
            for (XMLElement stateElement = stateElements.GetFirstChildElement();
                 stateElement.IsGood();
                 stateElement = stateElement.GetNextSiblingElement())
            {
                std::string stateName;
                stateElement.GetAttribute("game_command_name", &stateName);

                std::string inputValue;
                stateElement.GetAttribute("input_value", &inputValue);

                std::string inputDevice;
                stateElement.GetAttribute("device", &inputDevice);
                if (inputDevice == "keyboard")
                {
                    // TODO / FIXME : use this when MSVC fixes the bug.
                    //RawInput::Key buttonID = callbacks.StringToRawInputButton(inputValue);
                    RawInput::Key buttonID;
                    callbacks.StringToRawInputButton(inputValue, buttonID);
                    State state = gameCommands.GetState(stateName);
                    m_StateButtons[buttonID] = state;
                }
                else if (inputDevice == "mouse")
                {
                    RawInput::MouseButton buttonID;
                    callbacks.StringToRawInputMouseButton(inputValue, buttonID);
                    State state = gameCommands.GetState(stateName);
                    m_StateMouseButtons[buttonID] = state;
                }
            }

            // Read all ranges.
            XMLElement rangeElements(xmlRootElement.GetFirstChildElement("Ranges"));
            for (XMLElement rangeElement = rangeElements.GetFirstChildElement();
                 rangeElement.IsGood();
                 rangeElement = rangeElement.GetNextSiblingElement())
            {
                std::string rangeName;
                rangeElement.GetAttribute("game_command_name", &rangeName);

                std::string inputValue;
                rangeElement.GetAttribute("input_value", &inputValue);

                std::string inputDevice;
                rangeElement.GetAttribute("device", &inputDevice);

                XMLElement inputAxisElement(rangeElement.GetFirstChildElement("Axis"));
                assert(inputAxisElement.IsGood());
                std::string inputAxis;
                inputAxisElement.GetAttribute("name", &inputAxis);

                if (inputDevice == "mouse")
                {
                    // TODO / FIXME : use this when MSVC fixes the bug.
                    //RawInput::MouseAxis axis = callbacks.StringToRawInputAxis(inputValue);
                    RawInput::MouseAxis axis;
                    callbacks.StringToRawInputMouseAxis(inputValue, axis);
                    Range range = gameCommands.GetRange(rangeName);
                    m_RangeMouseAxes[axis] = range;

                    // Ranges.
                    m_Conversions.AddConverter(range, rangeElement);

                    XMLElement sensitivityElement(rangeElement.GetFirstChildElement("Sensitivity"));
                    assert(sensitivityElement.IsGood());
                    float fSensitivity;
                    sensitivityElement.GetFloatAttribute("value", &fSensitivity);
                    m_SensitivityMap[range] = fSensitivity;
                }
            }

            inputContextFile.CloseFile();
        }

        //
        // Destruct and clean up an input context
        //
        InputContext::~InputContext()
        {

        }


        //
        // Attempt to map a raw button to an action
        //
        bool InputContext::MapButtonToAction(RawInput::Key button, Action& out) const
        {
            std::map<RawInput::Key, Action>::const_iterator iter = m_ActionButtons.find(button);
            if (iter == m_ActionButtons.end())
            {
                return false;
            }

            out = iter->second;
            return true;
        }

        bool InputContext::MapButtonToAction(RawInput::MouseButton button, Action& out) const
        {
            std::map<RawInput::MouseButton, Action>::const_iterator iter = m_ActionMouseButtons.find(button);
            if (iter == m_ActionMouseButtons.end())
            {
                return false;
            }

            out = iter->second;
            return true;
        }

        //
        // Attempt to map a raw button to a state
        //
        bool InputContext::MapButtonToState(RawInput::Key button, State& out) const
        {
            std::map<RawInput::Key, State>::const_iterator iter = m_StateButtons.find(button);
            if (iter == m_StateButtons.end())
            {
                return false;
            }

            out = iter->second;
            return true;
        }

        bool InputContext::MapButtonToState(RawInput::MouseButton button, State& out) const
        {
            std::map<RawInput::MouseButton, State>::const_iterator iter = m_StateMouseButtons.find(button);
            if (iter == m_StateMouseButtons.end())
            {
                return false;
            }

            out = iter->second;
            return true;
        }

        //
        // Attempt to map a raw axis to a range
        //
        bool InputContext::MapAxisToRange(RawInput::MouseAxis axis, Range& out) const
        {
            std::map<RawInput::MouseAxis, Range>::const_iterator iter = m_RangeMouseAxes.find(axis);
            if (iter == m_RangeMouseAxes.end())
            {
                return false;
            }

            out = iter->second;
            return true;
        }


        //
        // Retrieve the sensitivity associated with a given range
        //
        float InputContext::GetSensitivity(Range range) const
        {
            std::map<Range, float>::const_iterator iter = m_SensitivityMap.find(range);
            if (iter == m_SensitivityMap.end())
            {
                return 1.0;
            }

            return iter->second;
        }

        const RangeConverter& InputContext::GetConversions() const
        {
            return m_Conversions;
        }
    }

}
