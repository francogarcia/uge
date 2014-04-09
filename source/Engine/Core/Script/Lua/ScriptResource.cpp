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

//========================================================================
// XmlResource.cpp : Defines a simple resource cache
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

#include "GameEngineStd.h"

#include "ScriptResource.h"
#include "LuaStateManager.h"

#include <Utilities/Debug/Logger.h>
#include <Engine/GameApplication/GameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>

namespace uge
{

    std::string LuaScriptResourceLoader::vGetPattern()
    {
        return "*.lua";
    }

    bool LuaScriptResourceLoader::vUseRawFile()
    {
        return false;
    }

    bool LuaScriptResourceLoader::vDiscardRawBufferAfterLoad()
    {
        return true;
    }

    bool LuaScriptResourceLoader::vAddNullZero()
    {
        return true;
    }

    unsigned int LuaScriptResourceLoader::vGetLoadedResourceSize(char* pRawBuffer, unsigned int rawSize)
    {
        return rawSize;
    }

    bool LuaScriptResourceLoader::vLoadResource(char* pRawBuffer, unsigned int rawSize, ResourceHandleSharedPointer pResourceHandle)
    {
        if (rawSize <= 0)
        {
            return false;
        }

        // Runs the lua script if possible or whilst initializing the game.
        if ((g_pApp->GetGameLogic() == nullptr) || (g_pApp->GetGameLogic()->CanRunLua()))
        {
            LuaStateManager::Get()->vExecuteString(pRawBuffer);
        }

        return true;
    }

    IResourceLoaderSharedPointer LuaScriptResourceLoader::CreateLoader()
    {
        return std::shared_ptr<IResourceLoader>(LIB_NEW LuaScriptResourceLoader());
    }

}
