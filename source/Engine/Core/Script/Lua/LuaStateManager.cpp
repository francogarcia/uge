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

#include "GameEngineStd.h"

#include "LuaStateManager.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{

    LuaStateManager* LuaStateManager::s_pSingleton = nullptr;

    bool LuaStateManager::Create()
    {
        if (s_pSingleton)
        {
            LOG_ERROR("Overwriting LuaStateManager singleton");
            SAFE_DELETE(s_pSingleton);
        }

        s_pSingleton = LIB_NEW LuaStateManager;
        if (s_pSingleton)
        {
            return s_pSingleton->vInit();
        }

        return false;
    }

    void LuaStateManager::Destroy()
    {
        assert(s_pSingleton);
        SAFE_DELETE(s_pSingleton);
    }

    LuaStateManager* LuaStateManager::Get()
    {
        LOG_ASSERT(s_pSingleton && "LuaStateManager was not created!");

        return s_pSingleton;
    }

    LuaStateManager::LuaStateManager() : m_pLuaState(nullptr)
    {

    }

    LuaStateManager::~LuaStateManager()
    {
        if (m_pLuaState != nullptr)
        {
            LuaPlus::LuaState::Destroy(m_pLuaState);
            m_pLuaState = nullptr;
        }
    }

    bool LuaStateManager::vInit()
    {
        const bool bUseStandardLibrary = true;
        m_pLuaState = LuaPlus::LuaState::Create(bUseStandardLibrary);
        if (m_pLuaState == nullptr)
        {
            return false;
        }

        // register functions // FIXME vExecuteFile, vExectureString
        m_pLuaState->GetGlobals().RegisterDirect("ExecuteFile", (*this), &LuaStateManager::vExecuteFile);
        m_pLuaState->GetGlobals().RegisterDirect("ExecuteString", (*this), &LuaStateManager::vExecuteString);

        return true;
    }

    void LuaStateManager::vExecuteFile(const char* pScriptFile)
    {
        int result = m_pLuaState->DoFile(pScriptFile);
        if (result != 0)
        {
            SetError(result);
        }
    }

    void LuaStateManager::vExecuteString(const char* pScriptString)
    {
        int result = 0;

        // Most strings are passed straight through to the Lua interpreter
        if (strlen(pScriptString) <= 1 || pScriptString[0] != '=')
        {
            result = m_pLuaState->DoString(pScriptString);
            if (result != 0)
            {
                SetError(result);
            }
        }
        else
        {
            // If the string starts with '=', wrap the statement in the print() function.
            std::string buffer("print(");
            buffer += (pScriptString + 1);
            buffer += ")";
            result = m_pLuaState->DoString(buffer.c_str());
            if (result != 0)
            {
                SetError(result);
            }
        }
    }

    void LuaStateManager::SetError(int errorNum)
    {
        // Note: If we get an error, we're hosed because LuaPlus throws an exception.  So if this function
        // is called and the error at the bottom triggers, you might as well pack it in.

        LuaPlus::LuaStackObject stackObj(m_pLuaState, -1);
        const char* pError = stackObj.GetString();
        if (pError)
        {
            m_LastError = pError;
            ClearStack();
        }
        else
        {
            m_LastError = "Unknown Lua parse error";
        }

        LOG_ERROR(m_LastError);
    }

    void LuaStateManager::ClearStack()
    {
        m_pLuaState->SetTop(0);
    }

    LuaPlus::LuaObject LuaStateManager::GetGlobalVars()
    {
        assert(m_pLuaState && "Invalid Lua State!");

        return m_pLuaState->GetGlobals();
    }

    LuaPlus::LuaState* LuaStateManager::GetLuaState() const
    {
        return m_pLuaState;
    }

    LuaPlus::LuaObject LuaStateManager::CreatePath(const char* pPath, bool bIgnoreLastElement)
    {
        std::vector<std::string> splitPath;

        SplitString(pPath, splitPath, '.');
        if (bIgnoreLastElement)
        {
            splitPath.pop_back();
        }

        LuaPlus::LuaObject context = GetGlobalVars();
        for (auto it = splitPath.begin(); it != splitPath.end(); ++it)
        {
            // make sure we still have a valid context
            if (context.IsNil())
            {
                LOG_ERROR("Something broke in CreatePath(); bailing out (element == " + (*it) + ")");
                return context;  // this will be nil
            }

            // grab whatever exists for this element
            const std::string& element = (*it);
            LuaPlus::LuaObject curr = context.GetByName(element.c_str());

            if (!curr.IsTable())
            {
                // if the element is not a table and not nil, we clobber it
                if (!curr.IsNil())
                {
                    LOG_WARNING("Overwriting element '" + element + "' in table");
                    context.SetNil(element.c_str());
                }

                // element is either nil or was clobbered so add the new table
                context.CreateTable(element.c_str());
            }

            context = context.GetByName(element.c_str());
        }

        // if we get here, we have created the path
        return context;
    }

    void LuaStateManager::ConvertVec3ToTable(const Vector3& vec, LuaPlus::LuaObject& outLuaTable) const
    {
        outLuaTable.AssignNewTable(GetLuaState());
        outLuaTable.SetNumber("x", vec.x);
        outLuaTable.SetNumber("y", vec.y);
        outLuaTable.SetNumber("z", vec.z);
    }

    void LuaStateManager::ConvertTableToVec3(const LuaPlus::LuaObject& luaTable, Vector3& outVec3) const
    {
        LuaPlus::LuaObject temp;

        // x
        temp = luaTable.Get("x");
        if (temp.IsNumber())
        {
            outVec3.x = temp.GetFloat();
        }
        else
        {
            LOG_ERROR("luaTable.x is not a number");
        }

        // y
        temp = luaTable.Get("y");
        if (temp.IsNumber())
        {
            outVec3.y = temp.GetFloat();
        }
        else
        {
            LOG_ERROR("luaTable.y is not a number");
        }

        // z
        temp = luaTable.Get("z");
        if (temp.IsNumber())
        {
            outVec3.z = temp.GetFloat();
        }
        else
        {
            LOG_ERROR("luaTable.z is not a number");
        }
    }

}
