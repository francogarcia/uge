#include "GameEngineStd.h"

#include "OISKeyboard.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{
    namespace InputDevice
    {
        OISKeyboard::OISKeyboard(InputMapping::InputMapper& inputMapper, size_t windowHandle)
            : m_InputMapper(inputMapper),
              m_OIS(windowHandle),
              m_pKeyboard(nullptr)
        {

        }

        OISKeyboard::~OISKeyboard()
        {

        }

        bool OISKeyboard::vInit()
        {
            if (!m_OIS.Init())
            {
                return false;
            }

            m_pKeyboard = static_cast<OIS::Keyboard*>(m_OIS.CreateInputObject(OIS::OISKeyboard, true));
            assert(m_pKeyboard != nullptr);

            m_pKeyboard->setEventCallback(this);

            // TODO : handle window resizing.
            //windowResized(m_pWindow);

            return true;
        }

        bool OISKeyboard::vDestroy()
        {
            m_OIS.DestroyInputObject(m_pKeyboard);

            return true;
        }

        bool OISKeyboard::vUpdate(unsigned long timeElapsed)
        {
            m_pKeyboard->capture();

            return true;
        }

        bool OISKeyboard::keyPressed(const OIS::KeyEvent& keyEvent)
        {
            RawInput::Key key = FromOIS(keyEvent.key);
            m_InputMapper.SetRawButtonState(key, true, false);

            return true;
        }

        bool OISKeyboard::keyReleased(const OIS::KeyEvent& keyEvent)
        {
            RawInput::Key key = FromOIS(keyEvent.key);
            m_InputMapper.SetRawButtonState(key, false, true);

            return true;
        }

        RawInput::Key OISKeyboard::FromOIS(const OIS::KeyCode& key)
        {
            switch (key)
            {
                case OIS::KC_UNASSIGNED:
                    return RawInput::Key::KC_UNASSIGNED;

                case OIS::KC_ESCAPE:
                    return RawInput::Key::KC_ESCAPE;

                case OIS::KC_1:
                    return RawInput::Key::KC_1;

                case OIS::KC_2:
                    return RawInput::Key::KC_2;

                case OIS::KC_3:
                    return RawInput::Key::KC_3;

                case OIS::KC_4:
                    return RawInput::Key::KC_4;

                case OIS::KC_5:
                    return RawInput::Key::KC_5;

                case OIS::KC_6:
                    return RawInput::Key::KC_6;

                case OIS::KC_7:
                    return RawInput::Key::KC_7;

                case OIS::KC_8:
                    return RawInput::Key::KC_8;

                case OIS::KC_9:
                    return RawInput::Key::KC_9;

                case OIS::KC_0:
                    return RawInput::Key::KC_0;

                case OIS::KC_MINUS:
                    return RawInput::Key::KC_MINUS;

                case OIS::KC_EQUALS:
                    return RawInput::Key::KC_EQUALS;

                case OIS::KC_BACK:
                    return RawInput::Key::KC_BACK;

                case OIS::KC_TAB:
                    return RawInput::Key::KC_TAB;

                case OIS::KC_Q:
                    return RawInput::Key::KC_Q;

                case OIS::KC_W:
                    return RawInput::Key::KC_W;

                case OIS::KC_E:
                    return RawInput::Key::KC_E;

                case OIS::KC_R:
                    return RawInput::Key::KC_R;

                case OIS::KC_T:
                    return RawInput::Key::KC_T;

                case OIS::KC_Y:
                    return RawInput::Key::KC_Y;

                case OIS::KC_U:
                    return RawInput::Key::KC_U;

                case OIS::KC_I:
                    return RawInput::Key::KC_I;

                case OIS::KC_O:
                    return RawInput::Key::KC_O;

                case OIS::KC_P:
                    return RawInput::Key::KC_P;

                case OIS::KC_LBRACKET:
                    return RawInput::Key::KC_LBRACKET;

                case OIS::KC_RBRACKET:
                    return RawInput::Key::KC_RBRACKET;

                case OIS::KC_RETURN:
                    return RawInput::Key::KC_RETURN;

                case OIS::KC_LCONTROL:
                    return RawInput::Key::KC_LCONTROL;

                case OIS::KC_A:
                    return RawInput::Key::KC_A;

                case OIS::KC_S:
                    return RawInput::Key::KC_S;

                case OIS::KC_D:
                    return RawInput::Key::KC_D;

                case OIS::KC_F:
                    return RawInput::Key::KC_F;

                case OIS::KC_G:
                    return RawInput::Key::KC_G;

                case OIS::KC_H:
                    return RawInput::Key::KC_H;

                case OIS::KC_J:
                    return RawInput::Key::KC_J;

                case OIS::KC_K:
                    return RawInput::Key::KC_K;

                case OIS::KC_L:
                    return RawInput::Key::KC_L;

                case OIS::KC_SEMICOLON:
                    return RawInput::Key::KC_SEMICOLON;

                case OIS::KC_APOSTROPHE:
                    return RawInput::Key::KC_APOSTROPHE;

                case OIS::KC_GRAVE:
                    return RawInput::Key::KC_GRAVE;

                case OIS::KC_LSHIFT:
                    return RawInput::Key::KC_LSHIFT;

                case OIS::KC_BACKSLASH:
                    return RawInput::Key::KC_BACKSLASH;

                case OIS::KC_Z:
                    return RawInput::Key::KC_Z;

                case OIS::KC_X:
                    return RawInput::Key::KC_X;

                case OIS::KC_C:
                    return RawInput::Key::KC_C;

                case OIS::KC_V:
                    return RawInput::Key::KC_V;

                case OIS::KC_B:
                    return RawInput::Key::KC_B;

                case OIS::KC_N:
                    return RawInput::Key::KC_N;

                case OIS::KC_M:
                    return RawInput::Key::KC_M;

                case OIS::KC_COMMA:
                    return RawInput::Key::KC_COMMA;

                case OIS::KC_PERIOD:
                    return RawInput::Key::KC_PERIOD;

                case OIS::KC_SLASH:
                    return RawInput::Key::KC_SLASH;

                case OIS::KC_RSHIFT:
                    return RawInput::Key::KC_RSHIFT;

                case OIS::KC_MULTIPLY:
                    return RawInput::Key::KC_MULTIPLY;

                case OIS::KC_LMENU:
                    return RawInput::Key::KC_LMENU;

                case OIS::KC_SPACE:
                    return RawInput::Key::KC_SPACE;

                case OIS::KC_CAPITAL:
                    return RawInput::Key::KC_CAPITAL;

                case OIS::KC_F1:
                    return RawInput::Key::KC_F1;

                case OIS::KC_F2:
                    return RawInput::Key::KC_F2;

                case OIS::KC_F3:
                    return RawInput::Key::KC_F3;

                case OIS::KC_F4:
                    return RawInput::Key::KC_F4;

                case OIS::KC_F5:
                    return RawInput::Key::KC_F5;

                case OIS::KC_F6:
                    return RawInput::Key::KC_F6;

                case OIS::KC_F7:
                    return RawInput::Key::KC_F7;

                case OIS::KC_F8:
                    return RawInput::Key::KC_F8;

                case OIS::KC_F9:
                    return RawInput::Key::KC_F9;

                case OIS::KC_F10:
                    return RawInput::Key::KC_F10;

                case OIS::KC_NUMLOCK:
                    return RawInput::Key::KC_NUMLOCK;

                case OIS::KC_SCROLL:
                    return RawInput::Key::KC_SCROLL;

                case OIS::KC_NUMPAD7:
                    return RawInput::Key::KC_NUMPAD7;

                case OIS::KC_NUMPAD8:
                    return RawInput::Key::KC_NUMPAD8;

                case OIS::KC_NUMPAD9:
                    return RawInput::Key::KC_NUMPAD9;

                case OIS::KC_SUBTRACT:
                    return RawInput::Key::KC_SUBTRACT;

                case OIS::KC_NUMPAD4:
                    return RawInput::Key::KC_NUMPAD4;

                case OIS::KC_NUMPAD5:
                    return RawInput::Key::KC_NUMPAD5;

                case OIS::KC_NUMPAD6:
                    return RawInput::Key::KC_NUMPAD6;

                case OIS::KC_ADD:
                    return RawInput::Key::KC_ADD;

                case OIS::KC_NUMPAD1:
                    return RawInput::Key::KC_NUMPAD1;

                case OIS::KC_NUMPAD2:
                    return RawInput::Key::KC_NUMPAD2;

                case OIS::KC_NUMPAD3:
                    return RawInput::Key::KC_NUMPAD3;

                case OIS::KC_NUMPAD0:
                    return RawInput::Key::KC_NUMPAD0;

                case OIS::KC_DECIMAL:
                    return RawInput::Key::KC_DECIMAL;

                case OIS::KC_OEM_102:
                    return RawInput::Key::KC_OEM_102;

                case OIS::KC_F11:
                    return RawInput::Key::KC_F11;

                case OIS::KC_F12:
                    return RawInput::Key::KC_F12;

                case OIS::KC_F13:
                    return RawInput::Key::KC_F13;

                case OIS::KC_F14:
                    return RawInput::Key::KC_F14;

                case OIS::KC_F15:
                    return RawInput::Key::KC_F15;

                case OIS::KC_KANA:
                    return RawInput::Key::KC_KANA;

                case OIS::KC_ABNT_C1:
                    return RawInput::Key::KC_ABNT_C1;

                case OIS::KC_CONVERT:
                    return RawInput::Key::KC_CONVERT;

                case OIS::KC_NOCONVERT:
                    return RawInput::Key::KC_NOCONVERT;

                case OIS::KC_YEN:
                    return RawInput::Key::KC_YEN;

                case OIS::KC_ABNT_C2:
                    return RawInput::Key::KC_ABNT_C2;

                case OIS::KC_NUMPADEQUALS:
                    return RawInput::Key::KC_NUMPADEQUALS;

                case OIS::KC_PREVTRACK:
                    return RawInput::Key::KC_PREVTRACK;

                case OIS::KC_AT:
                    return RawInput::Key::KC_AT;

                case OIS::KC_COLON:
                    return RawInput::Key::KC_COLON;

                case OIS::KC_UNDERLINE:
                    return RawInput::Key::KC_UNDERLINE;

                case OIS::KC_KANJI:
                    return RawInput::Key::KC_KANJI;

                case OIS::KC_STOP:
                    return RawInput::Key::KC_STOP;

                case OIS::KC_AX:
                    return RawInput::Key::KC_AX;

                case OIS::KC_UNLABELED:
                    return RawInput::Key::KC_UNLABELED;

                case OIS::KC_NEXTTRACK:
                    return RawInput::Key::KC_NEXTTRACK;

                case OIS::KC_NUMPADENTER:
                    return RawInput::Key::KC_NUMPADENTER;

                case OIS::KC_RCONTROL:
                    return RawInput::Key::KC_RCONTROL;

                case OIS::KC_MUTE:
                    return RawInput::Key::KC_MUTE;

                case OIS::KC_CALCULATOR:
                    return RawInput::Key::KC_CALCULATOR;

                case OIS::KC_PLAYPAUSE:
                    return RawInput::Key::KC_PLAYPAUSE;

                case OIS::KC_MEDIASTOP:
                    return RawInput::Key::KC_MEDIASTOP;

                case OIS::KC_VOLUMEDOWN:
                    return RawInput::Key::KC_VOLUMEDOWN;

                case OIS::KC_VOLUMEUP:
                    return RawInput::Key::KC_VOLUMEUP;

                case OIS::KC_WEBHOME:
                    return RawInput::Key::KC_WEBHOME;

                case OIS::KC_NUMPADCOMMA:
                    return RawInput::Key::KC_NUMPADCOMMA;

                case OIS::KC_DIVIDE:
                    return RawInput::Key::KC_DIVIDE;

                case OIS::KC_SYSRQ:
                    return RawInput::Key::KC_SYSRQ;

                case OIS::KC_RMENU:
                    return RawInput::Key::KC_RMENU;

                case OIS::KC_PAUSE:
                    return RawInput::Key::KC_PAUSE;

                case OIS::KC_HOME:
                    return RawInput::Key::KC_HOME;

                case OIS::KC_UP:
                    return RawInput::Key::KC_UP;

                case OIS::KC_PGUP:
                    return RawInput::Key::KC_PGUP;

                case OIS::KC_LEFT:
                    return RawInput::Key::KC_LEFT;

                case OIS::KC_RIGHT:
                    return RawInput::Key::KC_RIGHT;

                case OIS::KC_END:
                    return RawInput::Key::KC_END;

                case OIS::KC_DOWN:
                    return RawInput::Key::KC_DOWN;

                case OIS::KC_PGDOWN:
                    return RawInput::Key::KC_PGDOWN;

                case OIS::KC_INSERT:
                    return RawInput::Key::KC_INSERT;

                case OIS::KC_DELETE:
                    return RawInput::Key::KC_DELETE;

                case OIS::KC_LWIN:
                    return RawInput::Key::KC_LWIN;

                case OIS::KC_RWIN:
                    return RawInput::Key::KC_RWIN;

                case OIS::KC_APPS:
                    return RawInput::Key::KC_APPS;

                case OIS::KC_POWER:
                    return RawInput::Key::KC_POWER;

                case OIS::KC_SLEEP:
                    return RawInput::Key::KC_SLEEP;

                case OIS::KC_WAKE:
                    return RawInput::Key::KC_WAKE;

                case OIS::KC_WEBSEARCH:
                    return RawInput::Key::KC_WEBSEARCH;

                case OIS::KC_WEBFAVORITES:
                    return RawInput::Key::KC_WEBFAVORITES;

                case OIS::KC_WEBREFRESH:
                    return RawInput::Key::KC_WEBREFRESH;

                case OIS::KC_WEBSTOP:
                    return RawInput::Key::KC_WEBSTOP;

                case OIS::KC_WEBFORWARD:
                    return RawInput::Key::KC_WEBFORWARD;

                case OIS::KC_WEBBACK:
                    return RawInput::Key::KC_WEBBACK;

                case OIS::KC_MYCOMPUTER:
                    return RawInput::Key::KC_MYCOMPUTER;

                case OIS::KC_MAIL:
                    return RawInput::Key::KC_MAIL;

                case OIS::KC_MEDIASELECT:
                    return RawInput::Key::KC_MEDIASELECT;
            }

            LOG_ERROR("Invalid key code!");
            return RawInput::Key::KC_UNASSIGNED;
        }

        OIS::KeyCode OISKeyboard::ToOIS(const RawInput::Key& key)
        {
            switch (key)
            {
                case RawInput::Key::KC_UNASSIGNED:
                    return OIS::KC_UNASSIGNED;

                case RawInput::Key::KC_ESCAPE:
                    return OIS::KC_ESCAPE;

                case RawInput::Key::KC_1:
                    return OIS::KC_1;

                case RawInput::Key::KC_2:
                    return OIS::KC_2;

                case RawInput::Key::KC_3:
                    return OIS::KC_3;

                case RawInput::Key::KC_4:
                    return OIS::KC_4;

                case RawInput::Key::KC_5:
                    return OIS::KC_5;

                case RawInput::Key::KC_6:
                    return OIS::KC_6;

                case RawInput::Key::KC_7:
                    return OIS::KC_7;

                case RawInput::Key::KC_8:
                    return OIS::KC_8;

                case RawInput::Key::KC_9:
                    return OIS::KC_9;

                case RawInput::Key::KC_0:
                    return OIS::KC_0;

                case RawInput::Key::KC_MINUS:
                    return OIS::KC_MINUS;

                case RawInput::Key::KC_EQUALS:
                    return OIS::KC_EQUALS;

                case RawInput::Key::KC_BACK:
                    return OIS::KC_BACK;

                case RawInput::Key::KC_TAB:
                    return OIS::KC_TAB;

                case RawInput::Key::KC_Q:
                    return OIS::KC_Q;

                case RawInput::Key::KC_W:
                    return OIS::KC_W;

                case RawInput::Key::KC_E:
                    return OIS::KC_E;

                case RawInput::Key::KC_R:
                    return OIS::KC_R;

                case RawInput::Key::KC_T:
                    return OIS::KC_T;

                case RawInput::Key::KC_Y:
                    return OIS::KC_Y;

                case RawInput::Key::KC_U:
                    return OIS::KC_U;

                case RawInput::Key::KC_I:
                    return OIS::KC_I;

                case RawInput::Key::KC_O:
                    return OIS::KC_O;

                case RawInput::Key::KC_P:
                    return OIS::KC_P;

                case RawInput::Key::KC_LBRACKET:
                    return OIS::KC_LBRACKET;

                case RawInput::Key::KC_RBRACKET:
                    return OIS::KC_RBRACKET;

                case RawInput::Key::KC_RETURN:
                    return OIS::KC_RETURN;

                case RawInput::Key::KC_LCONTROL:
                    return OIS::KC_LCONTROL;

                case RawInput::Key::KC_A:
                    return OIS::KC_A;

                case RawInput::Key::KC_S:
                    return OIS::KC_S;

                case RawInput::Key::KC_D:
                    return OIS::KC_D;

                case RawInput::Key::KC_F:
                    return OIS::KC_F;

                case RawInput::Key::KC_G:
                    return OIS::KC_G;

                case RawInput::Key::KC_H:
                    return OIS::KC_H;

                case RawInput::Key::KC_J:
                    return OIS::KC_J;

                case RawInput::Key::KC_K:
                    return OIS::KC_K;

                case RawInput::Key::KC_L:
                    return OIS::KC_L;

                case RawInput::Key::KC_SEMICOLON:
                    return OIS::KC_SEMICOLON;

                case RawInput::Key::KC_APOSTROPHE:
                    return OIS::KC_APOSTROPHE;

                case RawInput::Key::KC_GRAVE:
                    return OIS::KC_GRAVE;

                case RawInput::Key::KC_LSHIFT:
                    return OIS::KC_LSHIFT;

                case RawInput::Key::KC_BACKSLASH:
                    return OIS::KC_BACKSLASH;

                case RawInput::Key::KC_Z:
                    return OIS::KC_Z;

                case RawInput::Key::KC_X:
                    return OIS::KC_X;

                case RawInput::Key::KC_C:
                    return OIS::KC_C;

                case RawInput::Key::KC_V:
                    return OIS::KC_V;

                case RawInput::Key::KC_B:
                    return OIS::KC_B;

                case RawInput::Key::KC_N:
                    return OIS::KC_N;

                case RawInput::Key::KC_M:
                    return OIS::KC_M;

                case RawInput::Key::KC_COMMA:
                    return OIS::KC_COMMA;

                case RawInput::Key::KC_PERIOD:
                    return OIS::KC_PERIOD;

                case RawInput::Key::KC_SLASH:
                    return OIS::KC_SLASH;

                case RawInput::Key::KC_RSHIFT:
                    return OIS::KC_RSHIFT;

                case RawInput::Key::KC_MULTIPLY:
                    return OIS::KC_MULTIPLY;

                case RawInput::Key::KC_LMENU:
                    return OIS::KC_LMENU;

                case RawInput::Key::KC_SPACE:
                    return OIS::KC_SPACE;

                case RawInput::Key::KC_CAPITAL:
                    return OIS::KC_CAPITAL;

                case RawInput::Key::KC_F1:
                    return OIS::KC_F1;

                case RawInput::Key::KC_F2:
                    return OIS::KC_F2;

                case RawInput::Key::KC_F3:
                    return OIS::KC_F3;

                case RawInput::Key::KC_F4:
                    return OIS::KC_F4;

                case RawInput::Key::KC_F5:
                    return OIS::KC_F5;

                case RawInput::Key::KC_F6:
                    return OIS::KC_F6;

                case RawInput::Key::KC_F7:
                    return OIS::KC_F7;

                case RawInput::Key::KC_F8:
                    return OIS::KC_F8;

                case RawInput::Key::KC_F9:
                    return OIS::KC_F9;

                case RawInput::Key::KC_F10:
                    return OIS::KC_F10;

                case RawInput::Key::KC_NUMLOCK:
                    return OIS::KC_NUMLOCK;

                case RawInput::Key::KC_SCROLL:
                    return OIS::KC_SCROLL;

                case RawInput::Key::KC_NUMPAD7:
                    return OIS::KC_NUMPAD7;

                case RawInput::Key::KC_NUMPAD8:
                    return OIS::KC_NUMPAD8;

                case RawInput::Key::KC_NUMPAD9:
                    return OIS::KC_NUMPAD9;

                case RawInput::Key::KC_SUBTRACT:
                    return OIS::KC_SUBTRACT;

                case RawInput::Key::KC_NUMPAD4:
                    return OIS::KC_NUMPAD4;

                case RawInput::Key::KC_NUMPAD5:
                    return OIS::KC_NUMPAD5;

                case RawInput::Key::KC_NUMPAD6:
                    return OIS::KC_NUMPAD6;

                case RawInput::Key::KC_ADD:
                    return OIS::KC_ADD;

                case RawInput::Key::KC_NUMPAD1:
                    return OIS::KC_NUMPAD1;

                case RawInput::Key::KC_NUMPAD2:
                    return OIS::KC_NUMPAD2;

                case RawInput::Key::KC_NUMPAD3:
                    return OIS::KC_NUMPAD3;

                case RawInput::Key::KC_NUMPAD0:
                    return OIS::KC_NUMPAD0;

                case RawInput::Key::KC_DECIMAL:
                    return OIS::KC_DECIMAL;

                case RawInput::Key::KC_OEM_102:
                    return OIS::KC_OEM_102;

                case RawInput::Key::KC_F11:
                    return OIS::KC_F11;

                case RawInput::Key::KC_F12:
                    return OIS::KC_F12;

                case RawInput::Key::KC_F13:
                    return OIS::KC_F13;

                case RawInput::Key::KC_F14:
                    return OIS::KC_F14;

                case RawInput::Key::KC_F15:
                    return OIS::KC_F15;

                case RawInput::Key::KC_KANA:
                    return OIS::KC_KANA;

                case RawInput::Key::KC_ABNT_C1:
                    return OIS::KC_ABNT_C1;

                case RawInput::Key::KC_CONVERT:
                    return OIS::KC_CONVERT;

                case RawInput::Key::KC_NOCONVERT:
                    return OIS::KC_NOCONVERT;

                case RawInput::Key::KC_YEN:
                    return OIS::KC_YEN;

                case RawInput::Key::KC_ABNT_C2:
                    return OIS::KC_ABNT_C2;

                case RawInput::Key::KC_NUMPADEQUALS:
                    return OIS::KC_NUMPADEQUALS;

                case RawInput::Key::KC_PREVTRACK:
                    return OIS::KC_PREVTRACK;

                case RawInput::Key::KC_AT:
                    return OIS::KC_AT;

                case RawInput::Key::KC_COLON:
                    return OIS::KC_COLON;

                case RawInput::Key::KC_UNDERLINE:
                    return OIS::KC_UNDERLINE;

                case RawInput::Key::KC_KANJI:
                    return OIS::KC_KANJI;

                case RawInput::Key::KC_STOP:
                    return OIS::KC_STOP;

                case RawInput::Key::KC_AX:
                    return OIS::KC_AX;

                case RawInput::Key::KC_UNLABELED:
                    return OIS::KC_UNLABELED;

                case RawInput::Key::KC_NEXTTRACK:
                    return OIS::KC_NEXTTRACK;

                case RawInput::Key::KC_NUMPADENTER:
                    return OIS::KC_NUMPADENTER;

                case RawInput::Key::KC_RCONTROL:
                    return OIS::KC_RCONTROL;

                case RawInput::Key::KC_MUTE:
                    return OIS::KC_MUTE;

                case RawInput::Key::KC_CALCULATOR:
                    return OIS::KC_CALCULATOR;

                case RawInput::Key::KC_PLAYPAUSE:
                    return OIS::KC_PLAYPAUSE;

                case RawInput::Key::KC_MEDIASTOP:
                    return OIS::KC_MEDIASTOP;

                case RawInput::Key::KC_VOLUMEDOWN:
                    return OIS::KC_VOLUMEDOWN;

                case RawInput::Key::KC_VOLUMEUP:
                    return OIS::KC_VOLUMEUP;

                case RawInput::Key::KC_WEBHOME:
                    return OIS::KC_WEBHOME;

                case RawInput::Key::KC_NUMPADCOMMA:
                    return OIS::KC_NUMPADCOMMA;

                case RawInput::Key::KC_DIVIDE:
                    return OIS::KC_DIVIDE;

                case RawInput::Key::KC_SYSRQ:
                    return OIS::KC_SYSRQ;

                case RawInput::Key::KC_RMENU:
                    return OIS::KC_RMENU;

                case RawInput::Key::KC_PAUSE:
                    return OIS::KC_PAUSE;

                case RawInput::Key::KC_HOME:
                    return OIS::KC_HOME;

                case RawInput::Key::KC_UP:
                    return OIS::KC_UP;

                case RawInput::Key::KC_PGUP:
                    return OIS::KC_PGUP;

                case RawInput::Key::KC_LEFT:
                    return OIS::KC_LEFT;

                case RawInput::Key::KC_RIGHT:
                    return OIS::KC_RIGHT;

                case RawInput::Key::KC_END:
                    return OIS::KC_END;

                case RawInput::Key::KC_DOWN:
                    return OIS::KC_DOWN;

                case RawInput::Key::KC_PGDOWN:
                    return OIS::KC_PGDOWN;

                case RawInput::Key::KC_INSERT:
                    return OIS::KC_INSERT;

                case RawInput::Key::KC_DELETE:
                    return OIS::KC_DELETE;

                case RawInput::Key::KC_LWIN:
                    return OIS::KC_LWIN;

                case RawInput::Key::KC_RWIN:
                    return OIS::KC_RWIN;

                case RawInput::Key::KC_APPS:
                    return OIS::KC_APPS;

                case RawInput::Key::KC_POWER:
                    return OIS::KC_POWER;

                case RawInput::Key::KC_SLEEP:
                    return OIS::KC_SLEEP;

                case RawInput::Key::KC_WAKE:
                    return OIS::KC_WAKE;

                case RawInput::Key::KC_WEBSEARCH:
                    return OIS::KC_WEBSEARCH;

                case RawInput::Key::KC_WEBFAVORITES:
                    return OIS::KC_WEBFAVORITES;

                case RawInput::Key::KC_WEBREFRESH:
                    return OIS::KC_WEBREFRESH;

                case RawInput::Key::KC_WEBSTOP:
                    return OIS::KC_WEBSTOP;

                case RawInput::Key::KC_WEBFORWARD:
                    return OIS::KC_WEBFORWARD;

                case RawInput::Key::KC_WEBBACK:
                    return OIS::KC_WEBBACK;

                case RawInput::Key::KC_MYCOMPUTER:
                    return OIS::KC_MYCOMPUTER;

                case RawInput::Key::KC_MAIL:
                    return OIS::KC_MAIL;

                case RawInput::Key::KC_MEDIASELECT:
                    return OIS::KC_MEDIASELECT;
            }

            LOG_ERROR("Invalid key code!");
            return OIS::KC_UNASSIGNED;
        }
    }
}
