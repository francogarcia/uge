/* Data-driven input mapper. */

#include "GameEngineStd.h"

#include <Utilities/Debug/Logger.h>

#include <Core/Controller/InputMapping/InputMapper.h>
#include <Core/Controller/InputMapping/RawInputConstantsParser.h>

#include <IO/Input/InputDevice/Implementation/OIS/OISMouse.h>
#include <IO/Input/InputDevice/Implementation/OIS/OISKeyboard.h>

#include "OgreBase.h" // For a quick IOS window.

/* XML Files */

/* input_context_list.xml

<?xml version="1.0" encoding="UTF-8"?>
<InputContexts resource="data/game/commands/input_context_list.xml">
  <InputContext name="game_commands">
    <Commands resource="data/game/commands/game_commands.xml"/>
    <InputMapping resource="data/game/commands/default_command_mapping.xml"/>
  </InputContext>
</InputContexts>

*/

/* game_commands.xml

<?xml version="1.0" encoding="UTF-8"?>
<Commands resource="data/game/commands/game_commands.xml">
  <Actions>
    <Action name="jump"/>
    <Action name="fire"/>
  </Actions>
  <States>
    <State name="run"/>
  </States>
  <Ranges>
    <Range name="accelerate"/>
  </Ranges>
</Commands>

*/

/* default_command_mapping.xml

<?xml version="1.0" encoding="UTF-8"?>
<Commands resource="data/game/commands/game_commands.xml">
  <Actions>
    <Action game_command_name="jump" input_value="KC_1"/>
    <Action game_command_name="fire" input_value="KC_2"/>
  </Actions>
  <States>
    <State game_command_name="run" input_value="KC_3"/>
  </States>
  <Ranges>
    <Range game_command_name="accelerate" input_value="RAW_INPUT_AXIS_MOUSE_X">
      <Axis name="x"/>
      <InputRange minimum_value="-1000.0f" maximum_value="1000.0f"/>
      <OutputRange minimum_value="-1.0f" maximum_value="1.0f"/>
      <Sensitivity value="50.0f"/>
    </Range>
  </Ranges>
</Commands>

*/

/* Program */


enum class uge::InputMapping::Action : unsigned int
{
    Jump,
    Fire,
    Shout
};

enum class uge::InputMapping::State : unsigned int
{
    Run
};

enum class uge::InputMapping::Range : unsigned int
{
    AccelerateX,
    AccelerateY
};

void InputCallback(uge::InputMapping::MappedInput& inputs)
{
    bool bState = inputs.IsStateEnabled(uge::InputMapping::State::Run);
    if (bState)
    {
        std::cout << "Running!" << std::endl;
    }

    bool bRange = inputs.IsRangeEnabled(uge::InputMapping::Range::AccelerateX);
    if (bRange)
    {
        float fRange = inputs.GetRangeValue(uge::InputMapping::Range::AccelerateX);
        std::cout << "Range X = " << fRange << std::endl;
    }

    bRange = inputs.IsRangeEnabled(uge::InputMapping::Range::AccelerateY);
    if (bRange)
    {
        float fRange = inputs.GetRangeValue(uge::InputMapping::Range::AccelerateY);
        std::cout << "Range Y = " << fRange << std::endl;
    }

    bool bAction = inputs.IsActionEnabled(uge::InputMapping::Action::Jump);
    if (bAction)
    {
        std::cout << "Jumping!" << std::endl;
    }

    bAction = inputs.IsActionEnabled(uge::InputMapping::Action::Fire);
    if (bAction)
    {
        std::cout << "Firing!" << std::endl;
    }

    bAction = inputs.IsActionEnabled(uge::InputMapping::Action::Shout);
    if (bAction)
    {
        std::cout << "Shouting!" << std::endl;
    }
}

class Test : public OgreBase
{
public:
    Test() : m_InputMapper()
    {
        uge::InputMapping::RawInputToInputTypeCallbacks callbacks;
        callbacks.StringToRawInputButton = uge::InputDevice::Keyboard::StringToRawInputButton;
        callbacks.StringToRawInputMouseButton = uge::InputDevice::Mouse::StringToRawInputMouseButton;
        callbacks.StringToRawInputAxis = uge::InputDevice::Mouse::StringToRawInputMouseAxis;

        m_InputMapper.Init("data/game/commands/input_context_list.xml", callbacks);

        m_InputMapper.PushContext("game_commands");
        m_InputMapper.AddCallback(InputCallback, 0);
    }

    virtual bool keyPressed(const OIS::KeyEvent& keyEvent) override
    {
        switch (keyEvent.key)
        {
            case OIS::KC_ESCAPE:
            {
                std::cout << "[ESC pressed]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_ESCAPE, true, false);

                break;
            }

            case OIS::KC_1:
            {
                std::cout << "[1 pressed]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_1, true, false);

                break;
            }

            case OIS::KC_2:
            {
                std::cout << "[2 pressed]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_2, true, false);

                break;
            }

            case OIS::KC_3:
            {
                std::cout << "[3 pressed]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_3, true, false);

                break;
            }

            
        }

        return true;
    }

    virtual bool keyReleased(const OIS::KeyEvent& keyEvent) override
    {
        switch (keyEvent.key)
        {
            case OIS::KC_ESCAPE:
            {
                std::cout << "[ESC released]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_ESCAPE, false, true);

                break;
            }

            case OIS::KC_1:
            {
                std::cout << "[1 released]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_1, false, false);

                break;
            }

            case OIS::KC_2:
            {
                std::cout << "[2 released]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_2, false, false);

                break;
            }

            case OIS::KC_3:
            {
                std::cout << "[3 released]" << std::endl;
                m_InputMapper.SetRawButtonState(uge::RawInputButton::KC_3, false, false);

                break;
            }
        }

        return true;
    }

    virtual bool mouseMoved(const OIS::MouseEvent& mouseEvent) override
    {
        return true;
    }

    virtual bool mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID) override
    {
        return true;
    }

    virtual bool mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID) override
    {
        return true;
    }

    virtual bool frameStarted(const Ogre::FrameEvent& frameEvent)
    {
        m_InputMapper.Dispatch();
        m_InputMapper.Clear();

        return true;
    }

private:
    uge::InputMapping::InputMapper m_InputMapper;
};

int main(int argc, char* argv[])
{
    uge::debug::log::Init("data/debug/LogConfig.xml");

    Test test;
    test.Init();
    test.Run();

    uge::debug::log::Destroy();

    return 0;
}
