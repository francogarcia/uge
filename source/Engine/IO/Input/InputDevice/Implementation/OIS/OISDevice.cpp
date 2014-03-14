#include "GameEngineStd.h"

#include "OISDevice.h"

namespace uge
{
    namespace InputDevice
    {
        OISDevice::OISDevice(size_t windowHandle)
            : m_WindowHandle(windowHandle),
              m_pInputManager(nullptr)
        {

        }

        OISDevice::~OISDevice()
        {

        }

        bool OISDevice::Init()
        {
            if (m_pInputManager != nullptr)
            {
                return true;
            }

            // OIS
            OIS::ParamList paramList;

            // Window handle.
            std::ostringstream windowHandleStr;
            windowHandleStr << m_WindowHandle;
            paramList.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

            // TODO: this should be read from a configuration file.
            // Don't allow IOS to block the cursor.
#ifdef OIS_WIN32_PLATFORM
            paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
            paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
            paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
            paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
            paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
            paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
            paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
            paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

            m_pInputManager = OIS::InputManager::createInputSystem(paramList);

            return true;
        }

        bool OISDevice::Destroy()
        {
            OIS::InputManager::destroyInputSystem(m_pInputManager);
            m_pInputManager = nullptr;

            return true;
        }

        OIS::Object* OISDevice::CreateInputObject(OIS::Type type, bool bBufferMode)
        {
            assert(m_pInputManager != nullptr && "Input manager was not initialized!");

            return m_pInputManager->createInputObject(type, bBufferMode);
        }

        void OISDevice::DestroyInputObject(OIS::Object* pObject)
        {
            assert(pObject != nullptr && "Invalid OIS object!");

            m_pInputManager->destroyInputObject(pObject);
            pObject = nullptr;
        }
    }
}