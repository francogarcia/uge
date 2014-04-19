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

#pragma once

#include <Core/EntityComponent/Entity/Actor.h>

#include <Engine/GameView/IGameView.h>

namespace uge
{

    class BaseGameLogic;
    class IEventManager;
    class ResourceCache;

    class GameApplication;
    // TODO / FIXME : remove this global variable.
    extern GameApplication* g_pApp;

    /**
     * @class GameEngine
     *  Defines a overloadable engine for 2D games.
     */
    class GameApplication
    {
    public:
        /**
         *  Constructor.
         */
        GameApplication();

        /**
         *  Destructor.
         */
        virtual ~GameApplication();

        virtual bool vInit();

        virtual bool vDestroy();

        virtual bool vRun() = 0;

        virtual BaseGameLogic* vCreateGameLogic() = 0;

        virtual GameViewID vAddGameView(IGameViewSharedPointer pGameView, ActorID actorID = Actor::NULL_ACTOR_ID) = 0;
        virtual void vRemoveGameView(IGameViewSharedPointer pGameView) = 0;

        virtual std::wstring vGetGameTitle() const = 0;
        virtual std::wstring vGetGameDirectory() const = 0;
        virtual std::wstring vGetGameSaveDirectory() const = 0;

        void AbortGame();
        void SetQuitting(bool bIsQuitting);
        bool IsRunning() const;

        IEventManager* GetEventManager();
        BaseGameLogic* GetGameLogic();

        virtual ResourceCache* vGetResourceCache() = 0;

    protected:
        virtual void vRegisterGameEvents();
        virtual void vUnregisterGameEvents();

    private:
        void RegisterEngineEvents();

    protected:
        std::wstring m_GameTitle;
        std::wstring m_GameDirectory;
        std::wstring m_GameSaveDirectory;

        BaseGameLogic* m_pGameLogic;
        IEventManager* m_pEventManager;

        bool m_bIsRunning;
        bool m_bQuitRequested;
        bool m_bIsQuitting;
    };

}
