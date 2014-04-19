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
 */

#include "SpaceshipGameStd.h"

#include "ActorFactory.h"

#include "DamageInflictingComponent.h"
#include "DamageSoakingComponent.h"
#include "HealthComponent.h"

namespace sg
{

    ActorFactory::ActorFactory() : uge::ActorFactory()
    {
        RegisterComponents();
    }

    ActorFactory::~ActorFactory()
    {

    }

    void ActorFactory::RegisterComponents()
    {
        m_ComponentFactory.Register<Component::DamageInflictingComponent>(uge::Component::GetComponentID(Component::DamageInflictingComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::DamageSoakingComponent>(uge::Component::GetComponentID(Component::DamageSoakingComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::HealthComponent>(uge::Component::GetComponentID(Component::HealthComponent::g_ComponentName));
    }

}
