#pragma once

namespace uge
{
    namespace InputDevice
    {
        class OISDevice
        {
        public:
            OISDevice(size_t windowHandle);
            virtual ~OISDevice();

            bool Init();
            bool Destroy();

            OIS::Object* CreateInputObject(OIS::Type type, bool bBufferMode);
            void DestroyInputObject(OIS::Object* pObject);

        protected:
            size_t m_WindowHandle;

            // OIS
            OIS::InputManager* m_pInputManager;
        };
    }
}
