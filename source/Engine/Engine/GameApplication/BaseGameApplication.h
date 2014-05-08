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

#pragma once

#include "GameApplication.h"

#include <Core/Events/Event.h>
#include <Core/Events/EventManager.h>
#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/IPhysics.h>

#include <Core/PlayerProfile/PlayerProfileManager.h>

#include <Engine/GameSystem/OutputManager.h>
#include <Engine/GameSystem/ResourceSystem.h>

#include <Engine/GameView/IGameView.h>

#include <IO/Output/OutputSystemFactory.h>

namespace uge
{

    class BaseGameApplication : public GameApplication
    {
    public:
        /**
         *  Constructor.
         */
        BaseGameApplication();

        /**
         *  Destructor.
         */
        virtual ~BaseGameApplication();

        virtual bool vInit() override;
        virtual bool vDestroy() override;
        virtual bool vRun() override;

        virtual BaseGameLogic* vCreateGameLogic() = 0;

        virtual GameViewID vAddGameView(IGameViewSharedPointer pGameView, ActorID actorID = Actor::NULL_ACTOR_ID) override;
        virtual void vRemoveGameView(IGameViewSharedPointer pGameView) override;

        virtual std::wstring vGetGameTitle() const override;

        virtual std::wstring vGetGameDirectory() const override;

        virtual std::wstring vGetGameSaveDirectory() const override;

        virtual ResourceCache* vGetResourceCache() override;

    protected:
        virtual bool vUpdate(const unsigned long timeNow, const unsigned long timeElapsed);

        virtual bool vRender(const unsigned long timeElapsed);

        virtual void vPreloadResources();

        virtual void vRegisterGameEvents() override;
        virtual void vUnregisterGameEvents() override;

    private:

        void ClearRunningData();

        void SetGameDirectories();

    protected:
        // For use with the default vInit() method.
        virtual bool vInitPlayerProfiles();

        virtual bool vInitResourceCache();

        virtual bool vInitLuaScripting();

        virtual bool vInitEventManager();

        virtual bool vInitGameLogic();

        virtual bool vInitOutputSystemFactory();

        virtual bool vInitOutputSystems() = 0;

    protected:
        /// Game systems.
        OutputManager m_OutputManager;
        ResourceSystem m_Resources;

        OutputSystemFactory* m_pOutputSystemFactory;

        /// Player profiles.
        PlayerProfileManager m_PlayerProfiles;

        IGameViewList m_Views;
    };

}
