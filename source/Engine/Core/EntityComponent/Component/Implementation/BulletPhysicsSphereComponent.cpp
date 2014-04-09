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

#include "BulletPhysicsSphereComponent.h"

namespace uge
{

    namespace Component
    {

        const char* BulletPhysicsSphereComponent::g_ComponentName = "BulletPhysicsSphereComponent";

        BulletPhysicsSphereComponent::BulletPhysicsSphereComponent()
        {

        }

        BulletPhysicsSphereComponent::~BulletPhysicsSphereComponent()
        {

        }

        void BulletPhysicsSphereComponent::vCreateShape()
        {
            m_pPhysics->vAddSphere(m_RigidBodyLocalScale.x, GetOwner(), m_Density, m_Material);
        }

        const std::string BulletPhysicsSphereComponent::vGetName() const
        {
            return g_ComponentName;
        }

    }

}
