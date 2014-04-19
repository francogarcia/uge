/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once


#include <Core/Task/Task.h>
#include "LuaStateManager.h"

namespace uge
{

    //---------------------------------------------------------------------------------------------------------------------
    // ScriptTask                                                   - Chapter 12, page 370
    //---------------------------------------------------------------------------------------------------------------------
    class ScriptTask : public Task
    {
    public:
        static void RegisterScriptClass();

    protected:
        // Task interface
        virtual void vOnInit() override;
        virtual void vOnUpdate(const unsigned long deltaMs) override;
        virtual void vOnSuccess() override;
        virtual void vOnFail() override;
        virtual void vOnAbort() override;

    private:
        // private helpers
        static void RegisterScriptClassFunctions(LuaPlus::LuaObject& metaTableObj);
        static LuaPlus::LuaObject CreateFromScript(LuaPlus::LuaObject self, LuaPlus::LuaObject constructionData, LuaPlus::LuaObject originalSubClass);
        virtual bool BuildCppDataFromScript(LuaPlus::LuaObject scriptClass, LuaPlus::LuaObject constructionData);

        // These are needed because the base-class version of these functions are all const and LuaPlus can't deal
        // with registering const functions.
        bool ScriptIsAlive();
        bool ScriptIsDead();
        bool ScriptIsPaused();

        // This wrapper function is needed so we can translate a Lua script object to something C++ can use.
        void ScriptAttachChild(LuaPlus::LuaObject child);

        // don't allow construction outside of this class
        explicit ScriptTask();

        unsigned long m_Frequency;
        unsigned long m_Time;
        LuaPlus::LuaObject m_ScriptInitFunction;
        LuaPlus::LuaObject m_ScriptUpdateFunction;
        LuaPlus::LuaObject m_ScriptSuccessFunction;
        LuaPlus::LuaObject m_ScriptFailFunction;
        LuaPlus::LuaObject m_ScriptAbortFunction;
        // The Lua instance of the class.
        LuaPlus::LuaObject m_Self;
    };

}
