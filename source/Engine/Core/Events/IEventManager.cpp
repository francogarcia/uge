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

#include "GameEngineStd.h"

#include "IEventManager.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    static IEventManager* g_pEventMgr = nullptr;
    GenericObjectFactory<IEventData, EventType> g_eventFactory;

    IEventManager* IEventManager::Get()
    {
        assert(g_pEventMgr && "Invalid event manager!");
        return g_pEventMgr;
    }

    IEventManager::IEventManager(std::string name, bool bIsGlobal)
    {
        if (bIsGlobal)
        {
            if (g_pEventMgr)
            {
                LOG_ERROR("Attempting to create two global event managers! The old one will be destroyed and overwritten with this one.");
                delete g_pEventMgr;
            }

            g_pEventMgr = this;
        }
    }

    IEventManager::~IEventManager()
    {
        if (g_pEventMgr == this)
        {
            g_pEventMgr = nullptr;
        }
    }

}
