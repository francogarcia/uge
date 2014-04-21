/*
 * (c) Copyright 2014 Franco Eusébio Garcia
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#pragma once

#include "LuaStateManager.h"

namespace uge
{
    namespace lua
    {
        class CppInheritable
        {
        protected:
            typedef LuaPlus::LuaObject(*CreateFromLuaScriptDelegate)(LuaPlus::LuaObject, LuaPlus::LuaObject, LuaPlus::LuaObject);
            typedef void (*RegisterLuaClassFunctions)(LuaPlus::LuaObject& metaTable);

            CppInheritable();

            virtual ~CppInheritable();

            static void RegisterLuaScriptClass(const char* const pClassName,
                                               CreateFromLuaScriptDelegate creationDelegate,
                                               RegisterLuaClassFunctions functionRegisterDelegate);

            static LuaPlus::LuaObject CreateCppFromLuaScript(CppInheritable* pObject,
                                                             const char* const pClassName,
                                                             LuaPlus::LuaObject self,
                                                             LuaPlus::LuaObject constructionData,
                                                             LuaPlus::LuaObject subclass);

            virtual bool vBuildCppDataFromScript(LuaPlus::LuaObject scriptClass,
                                                 LuaPlus::LuaObject constructionData) = 0;

        protected:
            LuaPlus::LuaObject m_Self;
        };
    }
}
