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

#include "GameEngineStd.h"

#include "GameController.h"

#include <Core/EntityComponent/Entity/Actor.h>

namespace uge
{
    GameController::GameController()
    {

    }

    GameController::~GameController()
    {

    }

    bool GameController::vInit()
    {
        uge::InputMapping::RawInputToInputTypeCallbacks callbacks = vGetInputConverterDelegates();
        const std::string& inputContextListFilename = vGetInputContextListFilename();
        m_InputMapper.Init(inputContextListFilename, callbacks);

        std::vector<std::string> inputContexts = vGetInputContexts();
        for (const std::string& contextFilename : inputContexts)
        {
            AddInputContext(contextFilename);
        }

        std::vector<MappedInputDelegate>& inputCallbacks = vGetMappedInputDelegates();
        for (const MappedInputDelegate& inputCallback : inputCallbacks)
        {
            m_InputMapper.AddCallback(inputCallback.callback, inputCallback.priority);
        }

        m_ActorID = Actor::NULL_ACTOR_ID;

        return true;
    }

    bool GameController::vDestroy()
    {
        m_InputMapper.Destroy();

        for (auto pDeviceIt = m_Devices.begin(), pDevicesEnd = m_Devices.end(); pDeviceIt != pDevicesEnd; ++pDeviceIt)
        {
            (*pDeviceIt)->vDestroy();
        }
        m_Devices.clear();

        return true;
    }

    bool GameController::vUpdate(unsigned long timeElapsed)
    {
        for (auto& inputDevice : m_Devices)
        {
            inputDevice->vUpdate(timeElapsed);
        }

        m_InputMapper.Dispatch();
        m_InputMapper.Clear();

        return true;
    }

    void GameController::AddInputDevice(InputDevice::IInputDevice* pInputDevice)
    {
        m_Devices.push_back(pInputDevice);
    }

    void GameController::RemoveInputDevice(InputDevice::IInputDevice* pInputDevice)
    {
        for (auto pDeviceIt = m_Devices.begin(), pDevicesEnd = m_Devices.end(); pDeviceIt != pDevicesEnd; ++pDeviceIt)
        {
            if (pInputDevice == *pDeviceIt)
            {
                m_Devices.erase(pDeviceIt);

                return;
            }
        }
    }

    void GameController::AddMappedInputCallback(InputMapping::InputCallback callback, int priority)
    {
        m_InputMapper.AddCallback(callback, priority);
    }

    void GameController::AddInputContext(const std::string& inputContextFilename)
    {
        m_InputMapper.PushContext(inputContextFilename);
    }

    void GameController::SetControlledActorID(ActorID actorID)
    {
        m_ActorID = actorID;
    }
}
