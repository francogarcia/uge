/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "GameApplication.h"

#include <Utilities/Debug/Logger.h>

#include <Engine/GameLogic/BaseGameLogic.h>

#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptExports.h>
#include <Core/Script/Lua/ScriptTask.h>

#include <Core/Resource/ResourceCache.h>

namespace uge
{

    GameApplication* g_pApp = nullptr;

    GameApplication::GameApplication() :
        m_pEventManager(nullptr), m_pGameLogic(nullptr),
        m_bIsQuitting(false), m_bIsRunning(false), m_bQuitRequested(false)
    {
        g_pApp = this;
    }

    GameApplication::~GameApplication()
    {
        vDestroy();
    }

    bool GameApplication::vInit()
    {
        m_pEventManager = nullptr;
        m_pGameLogic = nullptr;
        m_bIsQuitting = false;
        m_bIsRunning = false;
        m_bQuitRequested = false;

        return true;
    }

    bool GameApplication::vDestroy()
    {
        // Deleting in the reverse order of creation.
        SAFE_DELETE(m_pGameLogic);
        SAFE_DELETE(m_pEventManager);

        m_bIsRunning = false;
        m_bIsQuitting = true;
        m_bQuitRequested = true;

        return true;
    }

    IEventManager* GameApplication::GetEventManager()
    {
        assert((m_pEventManager != nullptr) && "Event Manager was not initialized!");

        return m_pEventManager;
    }

    BaseGameLogic* GameApplication::GetGameLogic()
    {
        assert((m_pGameLogic != nullptr) && "Game logic was not initialized!");

        return m_pGameLogic;
    }

    void GameApplication::AbortGame()
    {
        m_bIsQuitting = true;
    }

    void GameApplication::SetQuitting(bool bIsQuitting)
    {
        m_bIsQuitting = bIsQuitting;
    }

    bool GameApplication::IsRunning() const
    {
        return m_bIsRunning;
    }

    void GameApplication::vRegisterGameEvents()
    {

    }

    void GameApplication::vUnregisterGameEvents()
    {

    }

    void GameApplication::RegisterEngineEvents()
    {

    }

}
