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
