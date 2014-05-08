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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "GameEngineStd.h"

#include "BaseGameApplication.h"

#include <Core/EntityComponent/Component/Implementation/LuaScriptComponent.h>

#include <Core/Events/EventManager.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Core/Script/Lua/ScriptResource.h>
#include <Core/Script/Lua/LuaStateManager.h>
#include <Core/Script/Lua/ScriptExports.h>
#include <Core/Script/Lua/ScriptTask.h>

#include <Engine/GameLogic/BaseGameLogic.h>

#include <Engine/GameView/GameView.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/System/Time.h>

namespace uge
{

    BaseGameApplication::BaseGameApplication() : GameApplication()
    {

    }

    BaseGameApplication::~BaseGameApplication()
    {

    }

    bool BaseGameApplication::vInit()
    {
        if (!GameApplication::vInit())
        {
            return false;
        }

        ClearRunningData();

        if (!vInitPlayerProfiles())
        {
            return false;
        }

        SetGameDirectories();

        if (!vInitEventManager())
        {
            return false;
        }

        if (!vInitResourceCache())
        {
            return false;
        }

        if (!vInitOutputSystems())
        {
            return false;
        }

        if (!vInitGameLogic())
        {
            return false;
        }

        if (!vInitLuaScripting())
        {
            return false;
        }

        vRegisterGameEvents();
        vPreloadResources();

        m_bIsRunning = true;

        return true;
    }

    bool BaseGameApplication::vDestroy()
    {
        vUnregisterGameEvents();

        m_Views.clear();

        m_pGameLogic->vDestroy();

        lua::ScriptExports::Unregister();
        lua::LuaStateManager::Destroy();

        if (!m_OutputManager.vDestroy())
        {
            return false;
        }

        if (!m_Resources.Destroy())
        {
            return false;
        }

        if (!m_PlayerProfiles.Destroy())
        {
            return false;
        }

        // Must be the last method to be called.
        return GameApplication::vDestroy();
    }

    bool BaseGameApplication::vRun()
    {
        // Main game loop.
        Time::TimePoint startTime = Time::GetTime();

        while (true)
        {
            Time::TimePoint currentTime = Time::GetTime();
            unsigned long deltaNanoseconds = Time::GetDeltaAsNanoseconds(currentTime, startTime);
            startTime = currentTime;

            // FIXME : fix current time.
            if (!vUpdate(0u, deltaNanoseconds))
            {
                return true;
            }

            if (!vRender(deltaNanoseconds))
            {
                return true;
            }

            //std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        // Should never reach this.
        return false;
    }

    bool BaseGameApplication::vUpdate(const unsigned long timeNow, const unsigned long timeElapsed)
    {
        IEventManager::Get()->vUpdate(IEventManager::kINFINITE);

        m_pGameLogic->vOnUpdate(timeNow, timeElapsed);

        // Update all views.
        m_OutputManager.vUpdate(timeElapsed);
        for (const auto& gameView : m_Views)
        {
            gameView->vOnUpdate(timeElapsed);
        }

        return true;
    }

    bool BaseGameApplication::vRender(const unsigned long timeElapsed)
    {
        if (!m_OutputManager.vPreRender())
        {
            return false;
        }

        // Render all game views.
        for (const auto& gameView : m_Views)
        {
            gameView->vOnRender(0u, timeElapsed);
        }

        if (!m_OutputManager.vPostRender())
        {
            return false;
        }

        return true;
    }

    void BaseGameApplication::vRegisterGameEvents()
    {

    }

    void BaseGameApplication::vUnregisterGameEvents()
    {

    }

    void BaseGameApplication::ClearRunningData()
    {
        m_bQuitRequested = false;
        m_bIsQuitting = false;
        m_bIsRunning = false;
    }

    void BaseGameApplication::SetGameDirectories()
    {
        // TODO: fetch this from a configuration file.
        m_GameDirectory = L"data/";
        m_GameSaveDirectory = L"./";
        m_GameTitle = L"UGE Game";
    }

    bool BaseGameApplication::vInitPlayerProfiles()
    {
        return m_PlayerProfiles.Init("data/config/player_profiles/player_profiles.xml");
    }

    bool BaseGameApplication::vInitResourceCache()
    {
        const std::string resourceFileName = "data/data.zip";
        int resourceCacheSizeMB = 100; // 100MB
#if _DEBUG
        IResourceFile* pResourceFile = LIB_NEW ZipFileDevelopmentResource(resourceFileName, "./", ZipFileDevelopmentResource::Mode::Editor);
#else
        IResourceFile* pResourceFile = LIB_NEW ZipFileResource(resourceFileName);
#endif

        return m_Resources.Init(resourceCacheSizeMB, pResourceFile);
    }

    void BaseGameApplication::vPreloadResources()
    {

    }

    bool BaseGameApplication::vInitLuaScripting()
    {
        if (!lua::LuaStateManager::Create())
        {
            LOG_FATAL("Could create the Lua scripting system!");

            return false;
        }
        else
        {
            // Load the Lua pre-initializaion file into the resource cache.
            const char* SCRIPT_PRE_INIT_FILE = "data/scripts/PreInit.lua";
            Resource resource(SCRIPT_PRE_INIT_FILE);
            // This do the loading. The file won't be used it, but it will be loaded.
            ResourceHandleSharedPointer pResourceHandle = m_Resources.GetResourceHandle(&resource);

            lua::ScriptExports::Register();
            lua::ScriptTask::RegisterScriptClass();
            Component::LuaScriptComponent::RegisterScriptFunctions();
        }

        return true;
    }

    bool BaseGameApplication::vInitEventManager()
    {
        std::string eventManagerName("Global Event Manager");
        const bool bIsEventManagerGlobal = true;

        m_pEventManager = LIB_NEW EventManager(eventManagerName, bIsEventManagerGlobal);
        if (m_pEventManager == nullptr)
        {
            LOG_ASSERT("Could not create the event manager!");

            return false;
        }

        return true;
    }

    bool BaseGameApplication::vInitGameLogic()
    {
        m_pGameLogic = vCreateGameLogic();
        if (m_pGameLogic == nullptr)
        {
            LOG_ASSERT("Could not create the game logic!");

            return false;
        }

        return m_pGameLogic->vInit();
    }

    GameViewID BaseGameApplication::vAddGameView(IGameViewSharedPointer pGameView, ActorID actorID)
    {
        GameViewID gameViewID = m_Views.size() + 1;
        m_Views.push_back(pGameView);
        
        pGameView->vInit(m_pGameLogic->vGetScene());
        pGameView->vOnAttach(gameViewID, actorID);
        pGameView->vOnRestore();

        return gameViewID;
    }

    void BaseGameApplication::vRemoveGameView(IGameViewSharedPointer pGameView)
    {
        m_Views.remove(pGameView);

        pGameView->vDestroy();
    }

    std::wstring BaseGameApplication::vGetGameTitle() const
    {
        return m_GameTitle;
    }

    std::wstring BaseGameApplication::vGetGameDirectory() const
    {
        return m_GameDirectory;
    }

    std::wstring BaseGameApplication::vGetGameSaveDirectory() const
    {
        return m_GameSaveDirectory;
    }

    ResourceCache* BaseGameApplication::vGetResourceCache()
    {
        return &(m_Resources.GetResourceCache());
    }

}
