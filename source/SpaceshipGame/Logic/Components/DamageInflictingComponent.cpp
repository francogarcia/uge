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

#include "SpaceshipGameStd.h"

#include "DamageInflictingComponent.h"

namespace sg
{
    namespace Component
    {

        const char* DamageInflictingComponent::g_ComponentName = "DamageInflictingComponent";

        DamageInflictingComponent::DamageInflictingComponent()
            : m_DamageOutput(0)
        {

        }

        DamageInflictingComponent::~DamageInflictingComponent()
        {

        }

        bool DamageInflictingComponent::vInit(uge::XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            uge::XMLElement xmlElement = pInitXMLData->GetFirstChildElement("DamageOutput");
            if (xmlElement.IsGood())
            {
                xmlElement.GetIntAttribute("value", &m_DamageOutput);

                return true;
            }

            return false;
        }

        void DamageInflictingComponent::vPostInit()
        {

        }

        void DamageInflictingComponent::vUpdate(const unsigned long dt)
        {

        }

        void DamageInflictingComponent::vOnChange()
        {

        }

        const std::string DamageInflictingComponent::vGetName() const
        {
            return g_ComponentName;
        }

        int DamageInflictingComponent::GetDamageOutput() const
        {
            return m_DamageOutput;
        }

        void DamageInflictingComponent::SetDamageOutput(const int damageOutput)
        {
            m_DamageOutput = damageOutput;
        }

    }
}
