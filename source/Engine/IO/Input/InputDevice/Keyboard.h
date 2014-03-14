#pragma once

#include "IInputDevice.h"

namespace uge
{
    namespace InputDevice
    {
        class Keyboard : public IInputDevice
        {
        public:
            Keyboard();
            virtual ~Keyboard();

            virtual bool vInit() override;
            virtual bool vDestroy() override;

            virtual bool vUpdate(unsigned long timeElapsed) override;

            static void StringToRawInputButton(const std::string& buttonName, uge::RawInput::Key& button);
        };
    }
}
