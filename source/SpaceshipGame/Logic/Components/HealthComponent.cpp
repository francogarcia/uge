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

#include "HealthComponent.h"

namespace sg
{
    namespace Component
    {

        const char* HealthComponent::g_ComponentName = "HealthComponent";

        HealthComponent::HealthComponent()
            : m_HealthPoints(0), m_MaxHealthPoints(0)
        {

        }

        HealthComponent::~HealthComponent()
        {

        }

        bool HealthComponent::vInit(uge::XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            uge::XMLElement xmlElement = pInitXMLData->GetFirstChildElement("InitialHealthPoints");
            if (xmlElement.IsGood())
            {
                xmlElement.GetIntAttribute("value", &m_HealthPoints);

                uge::XMLElement xmlElement = pInitXMLData->GetFirstChildElement("MaximumHealthPoints");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetIntAttribute("value", &m_MaxHealthPoints);

                    return true;
                }
            }

            return false;
        }

        void HealthComponent::vPostInit()
        {

        }

        void HealthComponent::vUpdate(const unsigned long dt)
        {

        }

        void HealthComponent::vOnChange()
        {

        }

        const std::string HealthComponent::vGetName() const
        {
            return g_ComponentName;
        }

        int HealthComponent::GetHealthPoints() const
        {
            return m_HealthPoints;
        }

        void HealthComponent::SetHealthPoints(const int healthPoints)
        {
            m_HealthPoints = healthPoints;
        }

        void HealthComponent::IncrementHealthPoints(const int value)
        {
            m_HealthPoints += value;
        }

        void HealthComponent::DecrementHealthPoints(const int value)
        {
            m_HealthPoints -= value;
        }

        int HealthComponent::SetMaximumHealthPoints() const
        {
            return m_MaxHealthPoints;
        }

        void HealthComponent::SetMaximumHealthPoints(const int healthPoints)
        {
            m_MaxHealthPoints = healthPoints;
        }

    }
}
