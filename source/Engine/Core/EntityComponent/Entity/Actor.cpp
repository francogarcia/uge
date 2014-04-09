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

/**
 * @file Actor.cpp
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "Actor.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    Actor::Actor(const ActorID id) : m_ActorID(id), m_ActorType("Uninitialized"),
        m_ActorResourceFileName("Uninitialized")
    {

    }

    Actor::~Actor()
    {
        assert(m_ActorComponents.empty());
    }

    void Actor::Init(XMLElement* pInitXMLData)
    {
        pInitXMLData->GetAttribute("type", &m_ActorType);
        pInitXMLData->GetAttribute("resource", &m_ActorResourceFileName);
    }

    void Actor::PostInit()
    {
        for (ActorComponentMap::iterator componentIt = m_ActorComponents.begin();
             componentIt != m_ActorComponents.end();
             ++componentIt)
        {
            componentIt->second->vPostInit();
        }
    }

    void Actor::Update(const unsigned long dt)
    {
        for (ActorComponentMap::iterator componentIt = m_ActorComponents.begin();
             componentIt != m_ActorComponents.end();
             ++componentIt)
        {
            componentIt->second->vUpdate(dt);
        }
    }

    void Actor::Destroy()
    {
        m_ActorComponents.clear();
    }

    const ActorID Actor::GetActorID() const
    {
        return m_ActorID;
    }

    const std::string Actor::GetActorType() const
    {
        return m_ActorType;
    }

    const ActorComponentMap* Actor::GetActorComponents()
    {
        return &m_ActorComponents;
    }

    void Actor::AddComponent(ActorComponentSharedPointer pComponent)
    {
        m_ActorComponents.insert(std::make_pair(pComponent->vGetID(), pComponent));
    }

    std::string Actor::SerializeActorToXML()
    {
        // TODO
        LOG_ERROR("Not implemented");

        return "";
    }

}
