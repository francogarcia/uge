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

#include "GameEngineStd.h"

#include "BaseGameState.h"

#include <Engine/GameLogic/BaseGameLogic.h>

namespace uge
{

    namespace GameState
    {

        BaseGameState::BaseGameState()
            : m_LifeTime(0u),
              m_pGameLogic(nullptr)
        {

        }

        BaseGameState::~BaseGameState()
        {

        }

        bool BaseGameState::vInit(BaseGameLogic* pGameLogic)
        {
            assert(pGameLogic != nullptr && "Invalid game logic!");

            m_pGameLogic = pGameLogic;
            m_LifeTime = 0u;

            return true;
        }
        
        bool BaseGameState::vDestroy()
        {
            m_pGameLogic = nullptr;

            return true;
        }

        bool BaseGameState::vOnUpdate(unsigned long timeElapsed)
        {
            m_LifeTime += timeElapsed;

            return true;
        }

        bool BaseGameState::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const char* Uninitialized::g_Name = "Uninitialized";

        Uninitialized::Uninitialized()
        {

        }

        Uninitialized::~Uninitialized()
        {

        }

        bool Uninitialized::vInit(BaseGameLogic* pGameLogic)
        {
            return true;
        }

        bool Uninitialized::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Uninitialized::vDestroy()
        {
            return true;
        }

        bool Uninitialized::vOnUpdate(unsigned long timeElapsed)
        {
            return BaseGameState::vOnUpdate(timeElapsed);
        }

        bool Uninitialized::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string Uninitialized::vGetName() const
        {
            return g_Name;
        }

        const char* Initializing::g_Name = "Initializing";

        Initializing::Initializing()
        {

        }

        Initializing::~Initializing()
        {

        }

        bool Initializing::vInit(BaseGameLogic* pGameLogic)
        {
            return BaseGameState::vInit(pGameLogic);
        }

        bool Initializing::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Initializing::vDestroy()
        {
            return BaseGameState::vDestroy();
        }

        bool Initializing::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = BaseGameState::vOnUpdate(timeElapsed);

            m_pGameLogic->vChangeGameState(Running::g_Name);

            return bSuccess;
        }

        bool Initializing::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string Initializing::vGetName() const
        {
            return g_Name;
        }

        const char* Running::g_Name = "Running";

        Running::Running()
        {

        }

        Running::~Running()
        {

        }

        bool Running::vInit(BaseGameLogic* pGameLogic)
        {
            return BaseGameState::vInit(pGameLogic);
        }

        bool Running::vTailorToProfile(const std::string& xmlResourceFilename)
        {
            return true;
        }

        bool Running::vDestroy()
        {
            return BaseGameState::vDestroy();
        }

        bool Running::vOnUpdate(unsigned long timeElapsed)
        {
            bool bSuccess = BaseGameState::vOnUpdate(timeElapsed);

            unsigned long timeElapsedMs = timeElapsed * 1000;
            TaskManager* pTaskManager = m_pGameLogic->GetTaskManager();
            pTaskManager->UpdateTasks(timeElapsedMs);

            IPhysicsSharedPointer pPhysics = m_pGameLogic->vGetPhysics();
            if (pPhysics)
            {
                pPhysics->vUpdate(timeElapsed);
                pPhysics->vSyncVisibleScene();
            }

            return bSuccess;
        }

        bool Running::vOnRender(unsigned long timeElapsed)
        {
            return true;
        }

        const std::string Running::vGetName() const
        {
            return g_Name;
        }

    }

}
