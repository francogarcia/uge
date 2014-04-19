/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
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

#include "GameEngineStd.h"

#include "Keyboard.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringHash.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{
    namespace InputDevice
    {
        Keyboard::Keyboard()
        {

        }

        Keyboard::~Keyboard()
        {

        }

        bool Keyboard::vInit()
        {
            return true;
        }

        bool Keyboard::vDestroy()
        {
            return true;
        }

        bool Keyboard::vUpdate(unsigned long timeElapsed)
        {
            return true;
        }

        void Keyboard::StringToRawInputButton(const std::string& buttonName, uge::RawInput::Key& button)
        {
            //TODO: in the future, use compile-time hash (MSCV doesn't support constexpr so far).
            //std::size_t buttonNameHash = std::hash<std::string>()(buttonName);
            //switch (buttonNameHash)
            //{
            //case const_hash("KC_UNASSIGNED"):
            //    return uge::RawInput::Key::KC_KC_UNASSIGNED;
            //};
            // A sample implementation can be found commented in the end of the method.
            std::string upperButtonName = uge::StringToUpper(buttonName);
            if (upperButtonName == "KC_UNASSIGNED")
            {
                button = uge::RawInput::Key::KC_UNASSIGNED;
                return;
            }
            /*else*/if (upperButtonName == "KC_ESCAPE")
            {
                button = uge::RawInput::Key::KC_ESCAPE;
                return;
            }
            /*else*/if (upperButtonName == "KC_1")
            {
                button = uge::RawInput::Key::KC_1;
                return;
            }
            /*else*/if (upperButtonName == "KC_2")
            {
                button = uge::RawInput::Key::KC_2;
                return;
            }
            /*else*/if (upperButtonName == "KC_3")
            {
                button = uge::RawInput::Key::KC_3;
                return;
            }
            /*else*/if (upperButtonName == "KC_4")
            {
                button = uge::RawInput::Key::KC_4;
                return;
            }
            /*else*/if (upperButtonName == "KC_5")
            {
                button = uge::RawInput::Key::KC_5;
                return;
            }
            /*else*/if (upperButtonName == "KC_6")
            {
                button = uge::RawInput::Key::KC_6;
                return;
            }
            /*else*/if (upperButtonName == "KC_7")
            {
                button = uge::RawInput::Key::KC_7;
                return;
            }
            /*else*/if (upperButtonName == "KC_8")
            {
                button = uge::RawInput::Key::KC_8;
                return;
            }
            /*else*/if (upperButtonName == "KC_9")
            {
                button = uge::RawInput::Key::KC_9;
                return;
            }
            /*else*/if (upperButtonName == "KC_9")
            {
                button = RawInput::Key::KC_9;
                return;
            }
            /*else*/if (upperButtonName == "KC_0")
            {
                button = RawInput::Key::KC_0;
                return;
            }
            /*else*/if (upperButtonName == "KC_MINUS")
            {
                button = RawInput::Key::KC_MINUS;
                return;
            }
            /*else*/if (upperButtonName == "KC_EQUALS")
            {
                button = RawInput::Key::KC_EQUALS;
                return;
            }
            /*else*/if (upperButtonName == "KC_BACK")
            {
                button = RawInput::Key::KC_BACK;
                return;
            }
            /*else*/if (upperButtonName == "KC_TAB")
            {
                button = RawInput::Key::KC_TAB;
                return;
            }
            /*else*/if (upperButtonName == "KC_Q")
            {
                button = RawInput::Key::KC_Q;
                return;
            }
            /*else*/if (upperButtonName == "KC_W")
            {
                button = RawInput::Key::KC_W;
                return;
            }
            /*else*/if (upperButtonName == "KC_E")
            {
                button = RawInput::Key::KC_E;
                return;
            }
            /*else*/if (upperButtonName == "KC_R")
            {
                button = RawInput::Key::KC_R;
                return;
            }
            /*else*/if (upperButtonName == "KC_T")
            {
                button = RawInput::Key::KC_T;
                return;
            }
            /*else*/if (upperButtonName == "KC_Y")
            {
                button = RawInput::Key::KC_Y;
                return;
            }
            /*else*/if (upperButtonName == "KC_U")
            {
                button = RawInput::Key::KC_U;
                return;
            }
            /*else*/if (upperButtonName == "KC_I")
            {
                button = RawInput::Key::KC_I;
                return;
            }
            /*else*/if (upperButtonName == "KC_O")
            {
                button = RawInput::Key::KC_O;
                return;
            }
            /*else*/if (upperButtonName == "KC_P")
            {
                button = RawInput::Key::KC_P;
                return;
            }
            /*else*/if (upperButtonName == "KC_LBRACKET")
            {
                button = RawInput::Key::KC_LBRACKET;
                return;
            }
            /*else*/if (upperButtonName == "KC_RBRACKET")
            {
                button = RawInput::Key::KC_RBRACKET;
                return;
            }
            /*else*/if (upperButtonName == "KC_RETURN")
            {
                button = RawInput::Key::KC_RETURN;
                return;
            }
            /*else*/if (upperButtonName == "KC_LCONTROL")
            {
                button = RawInput::Key::KC_LCONTROL;
                return;
            }
            /*else*/if (upperButtonName == "KC_A")
            {
                button = RawInput::Key::KC_A;
                return;
            }
            /*else*/if (upperButtonName == "KC_S")
            {
                button = RawInput::Key::KC_S;
                return;
            }
            /*else*/if (upperButtonName == "KC_D")
            {
                button = RawInput::Key::KC_D;
                return;
            }
            /*else*/if (upperButtonName == "KC_F")
            {
                button = RawInput::Key::KC_F;
                return;
            }
            /*else*/if (upperButtonName == "KC_G")
            {
                button = RawInput::Key::KC_G;
                return;
            }
            /*else*/if (upperButtonName == "KC_H")
            {
                button = RawInput::Key::KC_H;
                return;
            }
            /*else*/if (upperButtonName == "KC_J")
            {
                button = RawInput::Key::KC_J;
                return;
            }
            /*else*/if (upperButtonName == "KC_K")
            {
                button = RawInput::Key::KC_K;
                return;
            }
            /*else*/if (upperButtonName == "KC_L")
            {
                button = RawInput::Key::KC_L;
                return;
            }
            /*else*/if (upperButtonName == "KC_SEMICOLON")
            {
                button = RawInput::Key::KC_SEMICOLON;
                return;
            }
            /*else*/if (upperButtonName == "KC_APOSTROPHE")
            {
                button = RawInput::Key::KC_APOSTROPHE;
                return;
            }
            /*else*/if (upperButtonName == "KC_GRAVE")
            {
                button = RawInput::Key::KC_GRAVE;
                return;
            }
            /*else*/if (upperButtonName == "KC_LSHIFT")
            {
                button = RawInput::Key::KC_LSHIFT;
                return;
            }
            /*else*/if (upperButtonName == "KC_BACKSLASH")
            {
                button = RawInput::Key::KC_BACKSLASH;
                return;
            }
            /*else*/if (upperButtonName == "KC_Z")
            {
                button = RawInput::Key::KC_Z;
                return;
            }
            /*else*/if (upperButtonName == "KC_X")
            {
                button = RawInput::Key::KC_X;
                return;
            }
            /*else*/if (upperButtonName == "KC_C")
            {
                button = RawInput::Key::KC_C;
                return;
            }
            /*else*/if (upperButtonName == "KC_V")
            {
                button = RawInput::Key::KC_V;
                return;
            }
            /*else*/if (upperButtonName == "KC_B")
            {
                button = RawInput::Key::KC_B;
                return;
            }
            /*else*/if (upperButtonName == "KC_N")
            {
                button = RawInput::Key::KC_N;
                return;
            }
            /*else*/if (upperButtonName == "KC_M")
            {
                button = RawInput::Key::KC_M;
                return;
            }
            /*else*/if (upperButtonName == "KC_COMMA")
            {
                button = RawInput::Key::KC_COMMA;
                return;
            }
            /*else*/if (upperButtonName == "KC_PERIOD")
            {
                button = RawInput::Key::KC_PERIOD;
                return;
            }
            /*else*/if (upperButtonName == "KC_SLASH")
            {
                button = RawInput::Key::KC_SLASH;
                return;
            }
            /*else*/if (upperButtonName == "KC_RSHIFT")
            {
                button = RawInput::Key::KC_RSHIFT;
                return;
            }
            /*else*/if (upperButtonName == "KC_MULTIPLY")
            {
                button = RawInput::Key::KC_MULTIPLY;
                return;
            }
            /*else*/if (upperButtonName == "KC_LMENU")
            {
                button = RawInput::Key::KC_LMENU;
                return;
            }
            /*else*/if (upperButtonName == "KC_SPACE")
            {
                button = RawInput::Key::KC_SPACE;
                return;
            }
            /*else*/if (upperButtonName == "KC_CAPITAL")
            {
                button = RawInput::Key::KC_CAPITAL;
                return;
            }
            /*else*/if (upperButtonName == "KC_F1")
            {
                button = RawInput::Key::KC_F1;
                return;
            }
            /*else*/if (upperButtonName == "KC_F2")
            {
                button = RawInput::Key::KC_F2;
                return;
            }
            /*else*/if (upperButtonName == "KC_F3")
            {
                button = RawInput::Key::KC_F3;
                return;
            }
            /*else*/if (upperButtonName == "KC_F4")
            {
                button = RawInput::Key::KC_F4;
                return;
            }
            /*else*/if (upperButtonName == "KC_F5")
            {
                button = RawInput::Key::KC_F5;
                return;
            }
            /*else*/if (upperButtonName == "KC_F6")
            {
                button = RawInput::Key::KC_F6;
                return;
            }
            /*else*/if (upperButtonName == "KC_F7")
            {
                button = RawInput::Key::KC_F7;
                return;
            }
            /*else*/if (upperButtonName == "KC_F8")
            {
                button = RawInput::Key::KC_F8;
                return;
            }
            /*else*/if (upperButtonName == "KC_F9")
            {
                button = RawInput::Key::KC_F9;
                return;
            }
            /*else*/if (upperButtonName == "KC_F10")
            {
                button = RawInput::Key::KC_F10;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMLOCK")
            {
                button = RawInput::Key::KC_NUMLOCK;
                return;
            }
            /*else*/if (upperButtonName == "KC_SCROLL")
            {
                button = RawInput::Key::KC_SCROLL;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD7")
            {
                button = RawInput::Key::KC_NUMPAD7;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD8")
            {
                button = RawInput::Key::KC_NUMPAD8;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD9")
            {
                button = RawInput::Key::KC_NUMPAD9;
                return;
            }
            /*else*/if (upperButtonName == "KC_SUBTRACT")
            {
                button = RawInput::Key::KC_SUBTRACT;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD4")
            {
                button = RawInput::Key::KC_NUMPAD4;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD5")
            {
                button = RawInput::Key::KC_NUMPAD5;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD6")
            {
                button = RawInput::Key::KC_NUMPAD6;
                return;
            }
            /*else*/if (upperButtonName == "KC_ADD")
            {
                button = RawInput::Key::KC_ADD;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD1")
            {
                button = RawInput::Key::KC_NUMPAD1;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD2")
            {
                button = RawInput::Key::KC_NUMPAD2;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD3")
            {
                button = RawInput::Key::KC_NUMPAD3;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPAD0")
            {
                button = RawInput::Key::KC_NUMPAD0;
                return;
            }
            /*else*/if (upperButtonName == "KC_DECIMAL")
            {
                button = RawInput::Key::KC_DECIMAL;
                return;
            }
            /*else*/if (upperButtonName == "KC_OEM_102")
            {
                button = RawInput::Key::KC_OEM_102;
                return;
            }
            /*else*/if (upperButtonName == "KC_F11")
            {
                button = RawInput::Key::KC_F11;
                return;
            }
            /*else*/if (upperButtonName == "KC_F12")
            {
                button = RawInput::Key::KC_F12;
                return;
            }
            /*else*/if (upperButtonName == "KC_F13")
            {
                button = RawInput::Key::KC_F13;
                return;
            }
            /*else*/if (upperButtonName == "KC_F14")
            {
                button = RawInput::Key::KC_F14;
                return;
            }
            /*else*/if (upperButtonName == "KC_F15")
            {
                button = RawInput::Key::KC_F15;
                return;
            }
            /*else*/if (upperButtonName == "KC_KANA")
            {
                button = RawInput::Key::KC_KANA;
                return;
            }
            /*else*/if (upperButtonName == "KC_ABNT_C1")
            {
                button = RawInput::Key::KC_ABNT_C1;
                return;
            }
            /*else*/if (upperButtonName == "KC_CONVERT")
            {
                button = RawInput::Key::KC_CONVERT;
                return;
            }
            /*else*/if (upperButtonName == "KC_NOCONVERT")
            {
                button = RawInput::Key::KC_NOCONVERT;
                return;
            }
            /*else*/if (upperButtonName == "KC_YEN")
            {
                button = RawInput::Key::KC_YEN;
                return;
            }
            /*else*/if (upperButtonName == "KC_ABNT_C2")
            {
                button = RawInput::Key::KC_ABNT_C2;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPADEQUALS")
            {
                button = RawInput::Key::KC_NUMPADEQUALS;
                return;
            }
            /*else*/if (upperButtonName == "KC_PREVTRACK")
            {
                button = RawInput::Key::KC_PREVTRACK;
                return;
            }
            /*else*/if (upperButtonName == "KC_AT")
            {
                button = RawInput::Key::KC_AT;
                return;
            }
            /*else*/if (upperButtonName == "KC_COLON")
            {
                button = RawInput::Key::KC_COLON;
                return;
            }
            /*else*/if (upperButtonName == "KC_UNDERLINE")
            {
                button = RawInput::Key::KC_UNDERLINE;
                return;
            }
            /*else*/if (upperButtonName == "KC_KANJI")
            {
                button = RawInput::Key::KC_KANJI;
                return;
            }
            /*else*/if (upperButtonName == "KC_STOP")
            {
                button = RawInput::Key::KC_STOP;
                return;
            }
            /*else*/if (upperButtonName == "KC_AX")
            {
                button = RawInput::Key::KC_AX;
                return;
            }
            /*else*/if (upperButtonName == "KC_UNLABELED")
            {
                button = RawInput::Key::KC_UNLABELED;
                return;
            }
            /*else*/if (upperButtonName == "KC_NEXTTRACK")
            {
                button = RawInput::Key::KC_NEXTTRACK;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPADENTER")
            {
                button = RawInput::Key::KC_NUMPADENTER;
                return;
            }
            /*else*/if (upperButtonName == "KC_RCONTROL")
            {
                button = RawInput::Key::KC_RCONTROL;
                return;
            }
            /*else*/if (upperButtonName == "KC_MUTE")
            {
                button = RawInput::Key::KC_MUTE;
                return;

            }
            /*else*/if (upperButtonName == "KC_CALCULATOR")
            {
                button = RawInput::Key::KC_CALCULATOR;
                return;
            }
            /*else*/if (upperButtonName == "KC_PLAYPAUSE")
            {
                button = RawInput::Key::KC_PLAYPAUSE;
                return;
            }
            /*else*/if (upperButtonName == "KC_MEDIASTOP")
            {
                button = RawInput::Key::KC_MEDIASTOP;
                return;
            }
            /*else*/if (upperButtonName == "KC_VOLUMEDOWN")
            {
                button = RawInput::Key::KC_VOLUMEDOWN;
                return;
            }
            /*else*/if (upperButtonName == "KC_VOLUMEUP")
            {
                button = RawInput::Key::KC_VOLUMEUP;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBHOME")
            {
                button = RawInput::Key::KC_WEBHOME;
                return;
            }
            /*else*/if (upperButtonName == "KC_NUMPADCOMMA")
            {
                button = RawInput::Key::KC_NUMPADCOMMA;
                return;
            }
            /*else*/if (upperButtonName == "KC_DIVIDE")
            {
                button = RawInput::Key::KC_DIVIDE;
                return;
            }
            /*else*/if (upperButtonName == "KC_SYSRQ")
            {
                button = RawInput::Key::KC_SYSRQ;
                return;
            }
            /*else*/if (upperButtonName == "KC_RMENU")
            {
                button = RawInput::Key::KC_RMENU;
                return;
            }
            /*else*/if (upperButtonName == "KC_PAUSE")
            {
                button = RawInput::Key::KC_PAUSE;
                return;
            }
            /*else*/if (upperButtonName == "KC_HOME")
            {
                button = RawInput::Key::KC_HOME;
                return;
            }
            /*else*/if (upperButtonName == "KC_UP")
            {
                button = RawInput::Key::KC_UP;
                return;
            }
            /*else*/if (upperButtonName == "KC_PGUP")
            {
                button = RawInput::Key::KC_PGUP;
                return;
            }
            /*else*/if (upperButtonName == "KC_LEFT")
            {
                button = RawInput::Key::KC_LEFT;
                return;
            }
            /*else*/if (upperButtonName == "KC_RIGHT")
            {
                button = RawInput::Key::KC_RIGHT;
                return;
            }
            /*else*/if (upperButtonName == "KC_END")
            {
                button = RawInput::Key::KC_END;
                return;
            }
            /*else*/if (upperButtonName == "KC_DOWN")
            {
                button = RawInput::Key::KC_DOWN;
                return;
            }
            /*else*/if (upperButtonName == "KC_PGDOWN")
            {
                button = RawInput::Key::KC_PGDOWN;
                return;
            }
            /*else*/if (upperButtonName == "KC_INSERT")
            {
                button = RawInput::Key::KC_INSERT;
                return;
            }
            /*else*/if (upperButtonName == "KC_DELETE")
            {
                button = RawInput::Key::KC_DELETE;
                return;
            }
            /*else*/if (upperButtonName == "KC_LWIN")
            {
                button = RawInput::Key::KC_LWIN;
                return;
            }
            /*else*/if (upperButtonName == "KC_RWIN")
            {
                button = RawInput::Key::KC_RWIN;
                return;
            }
            /*else*/if (upperButtonName == "KC_APPS")
            {
                button = RawInput::Key::KC_APPS;
                return;
            }
            /*else*/if (upperButtonName == "KC_POWER")
            {
                button = RawInput::Key::KC_POWER;
                return;
            }
            /*else*/if (upperButtonName == "KC_SLEEP")
            {
                button = RawInput::Key::KC_SLEEP;
                return;
            }
            /*else*/if (upperButtonName == "KC_WAKE")
            {
                button = RawInput::Key::KC_WAKE;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBSEARCH")
            {
                button = RawInput::Key::KC_WEBSEARCH;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBFAVORITES")
            {
                button = RawInput::Key::KC_WEBFAVORITES;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBREFRESH")
            {
                button = RawInput::Key::KC_WEBREFRESH;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBSTOP")
            {
                button = RawInput::Key::KC_WEBSTOP;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBFORWARD")
            {
                button = RawInput::Key::KC_WEBFORWARD;
                return;
            }
            /*else*/if (upperButtonName == "KC_WEBBACK")
            {
                button = RawInput::Key::KC_WEBBACK;
                return;
            }
            /*else*/if (upperButtonName == "KC_MYCOMPUTER")
            {
                button = RawInput::Key::KC_MYCOMPUTER;
                return;
            }
            /*else*/if (upperButtonName == "KC_MAIL")
            {
                button = RawInput::Key::KC_MAIL;
                return;
            }
            /*else*/if (upperButtonName == "KC_MEDIASELECT")
            {
                button = RawInput::Key::KC_MEDIASELECT;
                return;            }

            LOG_ERROR("Invalid key code!");
            button = RawInput::Key::KC_UNASSIGNED;

//            // TODO: switch to this:
//            std::string upperButtonName = StringToUpper(buttonName);
//            unsigned int buttonHash = StringHash(upperButtonName.c_str()).GetHash();
//            switch (buttonHash)
//            {
//                case StringHash("KC_UNASSIGNED").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_UNASSIGNED;
//                    return;
//                }
//                case StringHash("KC_ESCAPE").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_ESCAPE;
//                    return;
//                }
//                case StringHash("KC_1").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_1;
//                    return;
//                }
//                case StringHash("KC_2").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_2;
//                    return;
//                }
//                case StringHash("KC_3").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_3;
//                    return;
//                }
//                case StringHash("KC_4").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_4;
//                    return;
//                }
//                case StringHash("KC_5").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_5;
//                    return;
//                }
//                case StringHash("KC_6").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_6;
//                    return;
//                }
//                case StringHash("KC_7").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_7;
//                    return;
//                }
//                case StringHash("KC_8").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_8;
//                    return;
//                }
//                case StringHash("KC_9").GetHash():
//                {
//                    button = uge::RawInput::Key::KC_9;
//                    return;
//                }
//                case StringHash("KC_9").GetHash():
//                {
//                    button = RawInput::Key::KC_9;
//                    return;
//                }
//                case StringHash("KC_0").GetHash():
//                {
//                    button = RawInput::Key::KC_0;
//                    return;
//                }
//                case StringHash("KC_MINUS").GetHash():
//                {
//                    button = RawInput::Key::KC_MINUS;
//                    return;
//                }
//                case StringHash("KC_EQUALS").GetHash():
//                {
//                    button = RawInput::Key::KC_EQUALS;
//                    return;
//                }
//                case StringHash("KC_BACK").GetHash():
//                {
//                    button = RawInput::Key::KC_BACK;
//                    return;
//                }
//                case StringHash("KC_TAB").GetHash():
//                {
//                    button = RawInput::Key::KC_TAB;
//                    return;
//                }
//                case StringHash("KC_Q").GetHash():
//                {
//                    button = RawInput::Key::KC_Q;
//                    return;
//                }
//                case StringHash("KC_W").GetHash():
//                {
//                    button = RawInput::Key::KC_W;
//                    return;
//                }
//                case StringHash("KC_E").GetHash():
//                {
//                    button = RawInput::Key::KC_E;
//                    return;
//                }
//                case StringHash("KC_R").GetHash():
//                {
//                    button = RawInput::Key::KC_R;
//                    return;
//                }
//                case StringHash("KC_T").GetHash():
//                {
//                    button = RawInput::Key::KC_T;
//                    return;
//                }
//                case StringHash("KC_Y").GetHash():
//                {
//                    button = RawInput::Key::KC_Y;
//                    return;
//                }
//                case StringHash("KC_U").GetHash():
//                {
//                    button = RawInput::Key::KC_U;
//                    return;
//                }
//                case StringHash("KC_I").GetHash():
//                {
//                    button = RawInput::Key::KC_I;
//                    return;
//                }
//                case StringHash("KC_O").GetHash():
//                {
//                    button = RawInput::Key::KC_O;
//                    return;
//                }
//                case StringHash("KC_P").GetHash():
//                {
//                    button = RawInput::Key::KC_P;
//                    return;
//                }
//                case StringHash("KC_LBRACKET").GetHash():
//                {
//                    button = RawInput::Key::KC_LBRACKET;
//                    return;
//                }
//                case StringHash("KC_RBRACKET").GetHash():
//                {
//                    button = RawInput::Key::KC_RBRACKET;
//                    return;
//                }
//                case StringHash("KC_RETURN").GetHash():
//                {
//                    button = RawInput::Key::KC_RETURN;
//                    return;
//                }
//                case StringHash("KC_LCONTROL").GetHash():
//                {
//                    button = RawInput::Key::KC_LCONTROL;
//                    return;
//                }
//                case StringHash("KC_A").GetHash():
//                {
//                    button = RawInput::Key::KC_A;
//                    return;
//                }
//                case StringHash("KC_S").GetHash():
//                {
//                    button = RawInput::Key::KC_S;
//                    return;
//                }
//                case StringHash("KC_D").GetHash():
//                {
//                    button = RawInput::Key::KC_D;
//                    return;
//                }
//                case StringHash("KC_F").GetHash():
//                {
//                    button = RawInput::Key::KC_F;
//                    return;
//                }
//                case StringHash("KC_G").GetHash():
//                {
//                    button = RawInput::Key::KC_G;
//                    return;
//                }
//                case StringHash("KC_H").GetHash():
//                {
//                    button = RawInput::Key::KC_H;
//                    return;
//                }
//                case StringHash("KC_J").GetHash():
//                {
//                    button = RawInput::Key::KC_J;
//                    return;
//                }
//                case StringHash("KC_K").GetHash():
//                {
//                    button = RawInput::Key::KC_K;
//                    return;
//                }
//                case StringHash("KC_L").GetHash():
//                {
//                    button = RawInput::Key::KC_L;
//                    return;
//                }
//                case StringHash("KC_SEMICOLON").GetHash():
//                {
//                    button = RawInput::Key::KC_SEMICOLON;
//                    return;
//                }
//                case StringHash("KC_APOSTROPHE").GetHash():
//                {
//                    button = RawInput::Key::KC_APOSTROPHE;
//                    return;
//                }
//                case StringHash("KC_GRAVE").GetHash():
//                {
//                    button = RawInput::Key::KC_GRAVE;
//                    return;
//                }
//                case StringHash("KC_LSHIFT").GetHash():
//                {
//                    button = RawInput::Key::KC_LSHIFT;
//                    return;
//                }
//                case StringHash("KC_BACKSLASH").GetHash():
//                {
//                    button = RawInput::Key::KC_BACKSLASH;
//                    return;
//                }
//                case StringHash("KC_Z").GetHash():
//                {
//                    button = RawInput::Key::KC_Z;
//                    return;
//                }
//                case StringHash("KC_X").GetHash():
//                {
//                    button = RawInput::Key::KC_X;
//                    return;
//                }
//                case StringHash("KC_C").GetHash():
//                {
//                    button = RawInput::Key::KC_C;
//                    return;
//                }
//                case StringHash("KC_V").GetHash():
//                {
//                    button = RawInput::Key::KC_V;
//                    return;
//                }
//                case StringHash("KC_B").GetHash():
//                {
//                    button = RawInput::Key::KC_B;
//                    return;
//                }
//                case StringHash("KC_N").GetHash():
//                {
//                    button = RawInput::Key::KC_N;
//                    return;
//                }
//                case StringHash("KC_M").GetHash():
//                {
//                    button = RawInput::Key::KC_M;
//                    return;
//                }
//                case StringHash("KC_COMMA").GetHash():
//                {
//                    button = RawInput::Key::KC_COMMA;
//                    return;
//                }
//                case StringHash("KC_PERIOD").GetHash():
//                {
//                    button = RawInput::Key::KC_PERIOD;
//                    return;
//                }
//                case StringHash("KC_SLASH").GetHash():
//                {
//                    button = RawInput::Key::KC_SLASH;
//                    return;
//                }
//                case StringHash("KC_RSHIFT").GetHash():
//                {
//                    button = RawInput::Key::KC_RSHIFT;
//                    return;
//                }
//                case StringHash("KC_MULTIPLY").GetHash():
//                {
//                    button = RawInput::Key::KC_MULTIPLY;
//                    return;
//                }
//                case StringHash("KC_LMENU").GetHash():
//                {
//                    button = RawInput::Key::KC_LMENU;
//                    return;
//                }
//                case StringHash("KC_SPACE").GetHash():
//                {
//                    button = RawInput::Key::KC_SPACE;
//                    return;
//                }
//                case StringHash("KC_CAPITAL").GetHash():
//                {
//                    button = RawInput::Key::KC_CAPITAL;
//                    return;
//                }
//                case StringHash("KC_F1").GetHash():
//                {
//                    button = RawInput::Key::KC_F1;
//                    return;
//                }
//                case StringHash("KC_F2").GetHash():
//                {
//                    button = RawInput::Key::KC_F2;
//                    return;
//                }
//                case StringHash("KC_F3").GetHash():
//                {
//                    button = RawInput::Key::KC_F3;
//                    return;
//                }
//                case StringHash("KC_F4").GetHash():
//                {
//                    button = RawInput::Key::KC_F4;
//                    return;
//                }
//                case StringHash("KC_F5").GetHash():
//                {
//                    button = RawInput::Key::KC_F5;
//                    return;
//                }
//                case StringHash("KC_F6").GetHash():
//                {
//                    button = RawInput::Key::KC_F6;
//                    return;
//                }
//                case StringHash("KC_F7").GetHash():
//                {
//                    button = RawInput::Key::KC_F7;
//                    return;
//                }
//                case StringHash("KC_F8").GetHash():
//                {
//                    button = RawInput::Key::KC_F8;
//                    return;
//                }
//                case StringHash("KC_F9").GetHash():
//                {
//                    button = RawInput::Key::KC_F9;
//                    return;
//                }
//                case StringHash("KC_F10").GetHash():
//                {
//                    button = RawInput::Key::KC_F10;
//                    return;
//                }
//                case StringHash("KC_NUMLOCK").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMLOCK;
//                    return;
//                }
//                case StringHash("KC_SCROLL").GetHash():
//                {
//                    button = RawInput::Key::KC_SCROLL;
//                    return;
//                }
//                case StringHash("KC_NUMPAD7").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD7;
//                    return;
//                }
//                case StringHash("KC_NUMPAD8").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD8;
//                    return;
//                }
//                case StringHash("KC_NUMPAD9").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD9;
//                    return;
//                }
//                case StringHash("KC_SUBTRACT").GetHash():
//                {
//                    button = RawInput::Key::KC_SUBTRACT;
//                    return;
//                }
//                case StringHash("KC_NUMPAD4").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD4;
//                    return;
//                }
//                case StringHash("KC_NUMPAD5").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD5;
//                    return;
//                }
//                case StringHash("KC_NUMPAD6").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD6;
//                    return;
//                }
//                case StringHash("KC_ADD").GetHash():
//                {
//                    button = RawInput::Key::KC_ADD;
//                    return;
//                }
//                case StringHash("KC_NUMPAD1").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD1;
//                    return;
//                }
//                case StringHash("KC_NUMPAD2").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD2;
//                    return;
//                }
//                case StringHash("KC_NUMPAD3").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD3;
//                    return;
//                }
//                case StringHash("KC_NUMPAD0").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPAD0;
//                    return;
//                }
//                case StringHash("KC_DECIMAL").GetHash():
//                {
//                    button = RawInput::Key::KC_DECIMAL;
//                    return;
//                }
//                case StringHash("KC_OEM_102").GetHash():
//                {
//                    button = RawInput::Key::KC_OEM_102;
//                    return;
//                }
//                case StringHash("KC_F11").GetHash():
//                {
//                    button = RawInput::Key::KC_F11;
//                    return;
//                }
//                case StringHash("KC_F12").GetHash():
//                {
//                    button = RawInput::Key::KC_F12;
//                    return;
//                }
//                case StringHash("KC_F13").GetHash():
//                {
//                    button = RawInput::Key::KC_F13;
//                    return;
//                }
//                case StringHash("KC_F14").GetHash():
//                {
//                    button = RawInput::Key::KC_F14;
//                    return;
//                }
//                case StringHash("KC_F15").GetHash():
//                {
//                    button = RawInput::Key::KC_F15;
//                    return;
//                }
//                case StringHash("KC_KANA").GetHash():
//                {
//                    button = RawInput::Key::KC_KANA;
//                    return;
//                }
//                case StringHash("KC_ABNT_C1").GetHash():
//                {
//                    button = RawInput::Key::KC_ABNT_C1;
//                    return;
//                }
//                case StringHash("KC_CONVERT").GetHash():
//                {
//                    button = RawInput::Key::KC_CONVERT;
//                    return;
//                }
//                case StringHash("KC_NOCONVERT").GetHash():
//                {
//                    button = RawInput::Key::KC_NOCONVERT;
//                    return;
//                }
//                case StringHash("KC_YEN").GetHash():
//                {
//                    button = RawInput::Key::KC_YEN;
//                    return;
//                }
//                case StringHash("KC_ABNT_C2").GetHash():
//                {
//                    button = RawInput::Key::KC_ABNT_C2;
//                    return;
//                }
//                case StringHash("KC_NUMPADEQUALS").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPADEQUALS;
//                    return;
//                }
//                case StringHash("KC_PREVTRACK").GetHash():
//                {
//                    button = RawInput::Key::KC_PREVTRACK;
//                    return;
//                }
//                case StringHash("KC_AT").GetHash():
//                {
//                    button = RawInput::Key::KC_AT;
//                    return;
//                }
//                case StringHash("KC_COLON").GetHash():
//                {
//                    button = RawInput::Key::KC_COLON;
//                    return;
//                }
//                case StringHash("KC_UNDERLINE").GetHash():
//                {
//                    button = RawInput::Key::KC_UNDERLINE;
//                    return;
//                }
//                case StringHash("KC_KANJI").GetHash():
//                {
//                    button = RawInput::Key::KC_KANJI;
//                    return;
//                }
//                case StringHash("KC_STOP").GetHash():
//                {
//                    button = RawInput::Key::KC_STOP;
//                    return;
//                }
//                case StringHash("KC_AX").GetHash():
//                {
//                    button = RawInput::Key::KC_AX;
//                    return;
//                }
//                case StringHash("KC_UNLABELED").GetHash():
//                {
//                    button = RawInput::Key::KC_UNLABELED;
//                    return;
//                }
//                case StringHash("KC_NEXTTRACK").GetHash():
//                {
//                    button = RawInput::Key::KC_NEXTTRACK;
//                    return;
//                }
//                case StringHash("KC_NUMPADENTER").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPADENTER;
//                    return;
//                }
//                case StringHash("KC_RCONTROL").GetHash():
//                {
//                    button = RawInput::Key::KC_RCONTROL;
//                    return;
//                }
//                case StringHash("KC_MUTE").GetHash():
//                {
//                    button = RawInput::Key::KC_MUTE;
//                    return;
//
//                }
//                case StringHash("KC_CALCULATOR").GetHash():
//                {
//                    button = RawInput::Key::KC_CALCULATOR;
//                    return;
//                }
//                case StringHash("KC_PLAYPAUSE").GetHash():
//                {
//                    button = RawInput::Key::KC_PLAYPAUSE;
//                    return;
//                }
//                case StringHash("KC_MEDIASTOP").GetHash():
//                {
//                    button = RawInput::Key::KC_MEDIASTOP;
//                    return;
//                }
//                case StringHash("KC_VOLUMEDOWN").GetHash():
//                {
//                    button = RawInput::Key::KC_VOLUMEDOWN;
//                    return;
//                }
//                case StringHash("KC_VOLUMEUP").GetHash():
//                {
//                    button = RawInput::Key::KC_VOLUMEUP;
//                    return;
//                }
//                case StringHash("KC_WEBHOME").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBHOME;
//                    return;
//                }
//                case StringHash("KC_NUMPADCOMMA").GetHash():
//                {
//                    button = RawInput::Key::KC_NUMPADCOMMA;
//                    return;
//                }
//                case StringHash("KC_DIVIDE").GetHash():
//                {
//                    button = RawInput::Key::KC_DIVIDE;
//                    return;
//                }
//                case StringHash("KC_SYSRQ").GetHash():
//                {
//                    button = RawInput::Key::KC_SYSRQ;
//                    return;
//                }
//                case StringHash("KC_RMENU").GetHash():
//                {
//                    button = RawInput::Key::KC_RMENU;
//                    return;
//                }
//                case StringHash("KC_PAUSE").GetHash():
//                {
//                    button = RawInput::Key::KC_PAUSE;
//                    return;
//                }
//                case StringHash("KC_HOME").GetHash():
//                {
//                    button = RawInput::Key::KC_HOME;
//                    return;
//                }
//                case StringHash("KC_UP").GetHash():
//                {
//                    button = RawInput::Key::KC_UP;
//                    return;
//                }
//                case StringHash("KC_PGUP").GetHash():
//                {
//                    button = RawInput::Key::KC_PGUP;
//                    return;
//                }
//                case StringHash("KC_LEFT").GetHash():
//                {
//                    button = RawInput::Key::KC_LEFT;
//                    return;
//                }
//                case StringHash("KC_RIGHT").GetHash():
//                {
//                    button = RawInput::Key::KC_RIGHT;
//                    return;
//                }
//                case StringHash("KC_END").GetHash():
//                {
//                    button = RawInput::Key::KC_END;
//                    return;
//                }
//                case StringHash("KC_DOWN").GetHash():
//                {
//                    button = RawInput::Key::KC_DOWN;
//                    return;
//                }
//                case StringHash("KC_PGDOWN").GetHash():
//                {
//                    button = RawInput::Key::KC_PGDOWN;
//                    return;
//                }
//                case StringHash("KC_INSERT").GetHash():
//                {
//                    button = RawInput::Key::KC_INSERT;
//                    return;
//                }
//                case StringHash("KC_DELETE").GetHash():
//                {
//                    button = RawInput::Key::KC_DELETE;
//                    return;
//                }
//                case StringHash("KC_LWIN").GetHash():
//                {
//                    button = RawInput::Key::KC_LWIN;
//                    return;
//                }
//                case StringHash("KC_RWIN").GetHash():
//                {
//                    button = RawInput::Key::KC_RWIN;
//                    return;
//                }
//                case StringHash("KC_APPS").GetHash():
//                {
//                    button = RawInput::Key::KC_APPS;
//                    return;
//                }
//                case StringHash("KC_POWER").GetHash():
//                {
//                    button = RawInput::Key::KC_POWER;
//                    return;
//                }
//                case StringHash("KC_SLEEP").GetHash():
//                {
//                    button = RawInput::Key::KC_SLEEP;
//                    return;
//                }
//                case StringHash("KC_WAKE").GetHash():
//                {
//                    button = RawInput::Key::KC_WAKE;
//                    return;
//                }
//                case StringHash("KC_WEBSEARCH").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBSEARCH;
//                    return;
//                }
//                case StringHash("KC_WEBFAVORITES").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBFAVORITES;
//                    return;
//                }
//                case StringHash("KC_WEBREFRESH").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBREFRESH;
//                    return;
//                }
//                case StringHash("KC_WEBSTOP").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBSTOP;
//                    return;
//                }
//                case StringHash("KC_WEBFORWARD").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBFORWARD;
//                    return;
//                }
//                case StringHash("KC_WEBBACK").GetHash():
//                {
//                    button = RawInput::Key::KC_WEBBACK;
//                    return;
//                }
//                case StringHash("KC_MYCOMPUTER").GetHash():
//                {
//                    button = RawInput::Key::KC_MYCOMPUTER;
//                    return;
//                }
//                case StringHash("KC_MAIL").GetHash():
//                {
//                    button = RawInput::Key::KC_MAIL;
//                    return;
//                }
//                case StringHash("KC_MEDIASELECT").GetHash():
//                {
//                    button = RawInput::Key::KC_MEDIASELECT;
//                    return;
//                }
//            }
        }
    }
}
