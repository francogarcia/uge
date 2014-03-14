#pragma once

#include <Core/PlayerProfile/GraphicalPreferences.h>

#include <IO/Input/InputDevice/Mouse.h>

#include "OISDevice.h"

namespace uge
{
    namespace InputDevice
    {
        class OISMouse : public Mouse, public OIS::MouseListener
        {
        public:
            OISMouse(InputMapping::InputMapper& inputMapper, const GraphicalPreferences::WindowSettings& windowSettings, size_t windowHandle);
            virtual ~OISMouse();

            virtual bool vInit() override;
            virtual bool vDestroy() override;

            virtual bool vUpdate(unsigned long timeElapsed) override;

            virtual void vSetWindowSize(unsigned int windowWidth, unsigned int windowHeight) override;

            // IOS
        protected:
            virtual bool mouseMoved(const OIS::MouseEvent& mouseEvent);

            virtual bool mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID);

            virtual bool mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonID);

        private:
            static RawInput::MouseButton FromOIS(const OIS::MouseButtonID& buttonID);
            static OIS::MouseButtonID ToOIS(const RawInput::MouseButton& button);

        private:
            GraphicalPreferences::WindowSettings m_WindowSettings;

            InputMapping::InputMapper& m_InputMapper;

            // OIS
            OISDevice m_OIS;
            OIS::Mouse* m_pMouse;

            int m_LastX;
            int m_LastY;
        };
    }
}
