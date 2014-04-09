/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#pragma once
//========================================================================
// ScriptTask.h
//
// Part of the GameCode4 Application
//
// GameCode4 is the sample application that encapsulates much of the source code
// discussed in "Game Coding Complete - 4th Edition" by Mike McShaffry and David
// "Rez" Graham, published by Charles River Media.
// ISBN-10: 1133776574 | ISBN-13: 978-1133776574
//
// If this source code has found it's way to you, and you think it has helped you
// in any way, do the authors a favor and buy a new copy of the book - there are
// detailed explanations in it that compliment this code well. Buy a copy at Amazon.com
// by clicking here:
//    http://www.amazon.com/gp/product/1133776574/ref=olp_product_details?ie=UTF8&me=&seller=
//
// There's a companion web site at http://www.mcshaffry.com/GameCode/
//
// The source code is managed and maintained through Google Code:
//    http://code.google.com/p/gamecode4/
//
// (c) Copyright 2012 Michael L. McShaffry and David Graham
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser GPL v3
// as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
// http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
//
// You should have received a copy of the GNU Lesser GPL v3
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//========================================================================


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
