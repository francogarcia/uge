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

#include "SpaceshipGameStd.h"

#include "GameController.h"

#include <Core/Events/IEventManager.h>

#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "../../../Logic/Events/GameEvents.h"

namespace sg
{

    GameController::GameController(const uge::WindowSettings& windowSettings, size_t windowHandle)
        : m_WindowSettings(windowSettings),
          m_WindowHandle(windowHandle),
          m_Keyboard(m_InputMapper, windowHandle),
          m_Mouse(m_InputMapper, windowSettings, windowHandle)
    {

    }

    GameController::~GameController()
    {

    }

    bool GameController::vInit()
    {
        if (!uge::GameController::vInit())
        {
            return false;
        }

        m_Keyboard.vInit();
        AddInputDevice(&m_Keyboard);

        uge::WindowSettings::WindowSettingsData window = m_WindowSettings.GetWindowSettingsData();
        m_Mouse.vInit();
        m_Mouse.vSetWindowSize(window.width, window.height);
        AddInputDevice(&m_Mouse);

        m_LastPlayerMoveLeft = false;
        m_LastPlayerMoveRight = false;

        return true;
    }

    bool GameController::vDestroy()
    {
        if (!uge::GameController::vDestroy())
        {
            return false;
        }

        return true;
    }

    bool GameController::vUpdate(unsigned long timeElapsed)
    {
        if (!uge::GameController::vUpdate(timeElapsed))
        {
            return false;
        }

        return true;
    }

    void GameController::InputCallback(uge::InputMapping::MappedInput& inputs)
    {
        bool bState = inputs.IsStateEnabled(uge::InputMapping::State::PlayerMoveLeft);
        if (bState != m_LastPlayerMoveLeft)
        {
            if (bState)
            {
                std::shared_ptr<sg::MoveActor> pEvent(LIB_NEW sg::MoveActor(m_ActorID, sg::MoveActor::Direction::Left));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }
            else
            {
                std::shared_ptr<sg::StopActor> pEvent(LIB_NEW sg::StopActor(m_ActorID));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }

            m_LastPlayerMoveLeft = bState;
        }

        bState = inputs.IsStateEnabled(uge::InputMapping::State::PlayerMoveRight);
        if (bState != m_LastPlayerMoveRight)
        {
            if (bState)
            {
                std::shared_ptr<sg::MoveActor> pEvent(LIB_NEW sg::MoveActor(m_ActorID, sg::MoveActor::Direction::Right));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }
            else
            {
                std::shared_ptr<sg::StopActor> pEvent(LIB_NEW sg::StopActor(m_ActorID));
                uge::IEventManager::Get()->vQueueEvent(pEvent);
            }

            m_LastPlayerMoveRight = bState;
        }

        if (inputs.IsActionEnabled(uge::InputMapping::Action::FireBullet))
        {
            std::shared_ptr<sg::FireProjectile> pEvent(
                LIB_NEW sg::FireProjectile(m_ActorID, FireProjectile::Type::Bullet));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }

        if (inputs.IsActionEnabled(uge::InputMapping::Action::FireBomb))
        {
            std::shared_ptr<sg::FireProjectile> pEvent(
                LIB_NEW sg::FireProjectile(m_ActorID, FireProjectile::Type::Bomb));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }
    }

    const std::string GameController::vGetInputContextListFilename()
    {
        return std::string("data/game/commands/input_context_list.xml");
    }

    const uge::InputMapping::RawInputToInputTypeCallbacks GameController::vGetInputConverterDelegates()
    {
        uge::InputMapping::RawInputToInputTypeCallbacks callbacks;
        callbacks.StringToRawInputButton = &uge::InputDevice::Keyboard::StringToRawInputButton;
        callbacks.StringToRawInputMouseButton = &uge::InputDevice::Mouse::StringToRawInputMouseButton;
        callbacks.StringToRawInputMouseAxis = &uge::InputDevice::Mouse::StringToRawInputMouseAxis;

        return callbacks;
    }

    const std::vector<std::string> GameController::vGetInputContexts()
    {
        std::vector<std::string> inputContexts;
        inputContexts.push_back("game_commands");

        return inputContexts;
    }

    std::vector<uge::GameController::MappedInputDelegate> GameController::vGetMappedInputDelegates()
    {
        std::vector<uge::GameController::MappedInputDelegate> mappedInputCallbacks;

        uge::GameController::MappedInputDelegate mappedInputDelegate;
        mappedInputDelegate.callback = fastdelegate::MakeDelegate(this, &GameController::InputCallback);
        mappedInputDelegate.priority = 0;

        mappedInputCallbacks.push_back(mappedInputDelegate);

        return mappedInputCallbacks;
    }

}
