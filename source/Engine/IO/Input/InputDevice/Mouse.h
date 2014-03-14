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
