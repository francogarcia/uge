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
 */

#include "PongGameStd.h"

#include "PongGameController.h"

#include <Core/Events/IEventManager.h>

#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "../Events/PongEvents.h"

PongGameController::PongGameController(const uge::GraphicalPreferences::WindowSettings& windowSettings, size_t windowHandle)
    : m_WindowSettings(windowSettings),
      m_WindowHandle(windowHandle),
      m_Keyboard(m_InputMapper, windowHandle),
      m_Mouse(m_InputMapper, windowSettings, windowHandle)
{

}

PongGameController::~PongGameController()
{

}

bool PongGameController::vInit()
{
    if (!uge::GameController::vInit())
    {
        return false;
    }

    m_Keyboard.vInit();
    AddInputDevice(&m_Keyboard);

    m_Mouse.vInit();
    m_Mouse.vSetWindowSize(m_WindowSettings.width, m_WindowSettings.height);
    AddInputDevice(&m_Mouse);

    m_LastPlayer1MoveUp = false;
    m_LastPlayer1MoveDown = false;

    m_LastPlayer2MoveUp = false;
    m_LastPlayer2MoveDown = false;

    return true;
}

bool PongGameController::vDestroy()
{
    if (!uge::GameController::vDestroy())
    {
        return false;
    }

    return true;
}

bool PongGameController::vUpdate(unsigned long timeElapsed)
{
    // Need to capture/update each device.
    //m_Keyboard.vUpdate(timeElapsed);

    if (!uge::GameController::vUpdate(timeElapsed))
    {
        return false;
    }

    return true;
}

void PongGameController::PongGameInputCallback(uge::InputMapping::MappedInput& inputs)
{
    bool bState = inputs.IsStateEnabled(uge::InputMapping::State::Player1MoveUp);
    if (bState != m_LastPlayer1MoveUp)
    {
        if (bState)
        {
            std::shared_ptr<EvtData_Move_Paddle> pEvent(LIB_NEW EvtData_Move_Paddle(m_ActorID, "Up"));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }
        else
        {
            std::shared_ptr<EvtData_Stop_Paddle> pEvent(LIB_NEW EvtData_Stop_Paddle(m_ActorID));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }

        m_LastPlayer1MoveUp = bState;
    }

    bState = inputs.IsStateEnabled(uge::InputMapping::State::Player1MoveDown);
    if (bState != m_LastPlayer1MoveDown)
    {
        if (bState)
        {
            std::shared_ptr<EvtData_Move_Paddle> pEvent(LIB_NEW EvtData_Move_Paddle(m_ActorID, "Down"));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }
        else
        {
            std::shared_ptr<EvtData_Stop_Paddle> pEvent(LIB_NEW EvtData_Stop_Paddle(m_ActorID));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }

        m_LastPlayer1MoveDown = bState;
    }

    bState = inputs.IsStateEnabled(uge::InputMapping::State::Player2MoveUp);
    if (bState != m_LastPlayer2MoveUp)
    {
        if (bState)
        {
            std::shared_ptr<EvtData_Move_Paddle> pEvent(LIB_NEW EvtData_Move_Paddle(m_ActorID + 1, "Up"));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }
        else
        {
            std::shared_ptr<EvtData_Stop_Paddle> pEvent(LIB_NEW EvtData_Stop_Paddle(m_ActorID + 1));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }

        m_LastPlayer2MoveUp = bState;
    }

    bState = inputs.IsStateEnabled(uge::InputMapping::State::Player2MoveDown);
    if (bState != m_LastPlayer2MoveDown)
    {
        if (bState)
        {
            std::shared_ptr<EvtData_Move_Paddle> pEvent(LIB_NEW EvtData_Move_Paddle(m_ActorID + 1, "Down"));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }
        else
        {
            std::shared_ptr<EvtData_Stop_Paddle> pEvent(LIB_NEW EvtData_Stop_Paddle(m_ActorID + 1));
            uge::IEventManager::Get()->vQueueEvent(pEvent);
        }

        m_LastPlayer2MoveDown = bState;
    }
}

const std::string PongGameController::vGetInputContextListFilename()
{
    return std::string("data/game/commands/input_context_list.xml");
}

const uge::InputMapping::RawInputToInputTypeCallbacks PongGameController::vGetInputConverterDelegates()
{
    uge::InputMapping::RawInputToInputTypeCallbacks callbacks;
    callbacks.StringToRawInputButton = &uge::InputDevice::Keyboard::StringToRawInputButton;
    callbacks.StringToRawInputMouseButton = &uge::InputDevice::Mouse::StringToRawInputMouseButton;
    callbacks.StringToRawInputMouseAxis = &uge::InputDevice::Mouse::StringToRawInputMouseAxis;

    return callbacks;
}

const std::vector<std::string> PongGameController::vGetInputContexts()
{
    std::vector<std::string> inputContexts;
    inputContexts.push_back("game_commands");

    return inputContexts;
}

std::vector<uge::GameController::MappedInputDelegate> PongGameController::vGetMappedInputDelegates()
{
    std::vector<uge::GameController::MappedInputDelegate> mappedInputCallbacks;

    uge::GameController::MappedInputDelegate mappedInputDelegate;
    mappedInputDelegate.callback = fastdelegate::MakeDelegate(this, &PongGameController::PongGameInputCallback);
    mappedInputDelegate.priority = 0;

    mappedInputCallbacks.push_back(mappedInputDelegate);

    return mappedInputCallbacks;
}
