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

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>
#include <Core/Physics/PhysicsEvents.h>

namespace sg
{

class EvtData_Restart_Game : public uge::BaseEventData
{
public:
    static const uge::EventType sk_EventType;

    explicit EvtData_Restart_Game()
    {

    }

    virtual const uge::EventType& vGetEventType() const override
    {
        return sk_EventType;
    }

    virtual uge::IEventDataSharedPointer vCopy() const override
    {
        return uge::IEventDataSharedPointer(LIB_NEW EvtData_Restart_Game());
    }

    virtual void vSerialize(std::ostrstream& out) const override
    {

    }

    virtual void vDeserialize(std::istrstream& in) override
    {

    }

    virtual const char* vGetName() const override
    {
        return "EvtData_Restart_Game";
    }
};

}
