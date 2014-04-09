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

#include "DamageSoakingComponent.h"

namespace sg
{
    namespace Component
    {

        const char* DamageSoakingComponent::g_ComponentName = "DamageSoakingComponent";

        DamageSoakingComponent::DamageSoakingComponent()
            : m_CurrentProtection(0), m_MaxProtection(0)
        {

        }

        DamageSoakingComponent::~DamageSoakingComponent()
        {

        }

        bool DamageSoakingComponent::vInit(uge::XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            uge::XMLElement xmlElement = pInitXMLData->GetFirstChildElement("InitialProtection");
            if (xmlElement.IsGood())
            {
                xmlElement.GetIntAttribute("value", &m_CurrentProtection);

                uge::XMLElement xmlElement = pInitXMLData->GetFirstChildElement("MaximumProtection");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetIntAttribute("value", &m_MaxProtection);

                    return true;
                }
            }

            return false;
        }

        void DamageSoakingComponent::vPostInit()
        {

        }

        void DamageSoakingComponent::vUpdate(const unsigned long dt)
        {

        }

        void DamageSoakingComponent::vOnChange()
        {

        }

        const std::string DamageSoakingComponent::vGetName() const
        {
            return g_ComponentName;
        }

        int DamageSoakingComponent::GetCurrentProtection() const
        {
            return m_CurrentProtection;
        }

        void DamageSoakingComponent::SetCurrentProtection(const int value)
        {
            m_CurrentProtection = value;
        }

        void DamageSoakingComponent::IncrementProtection(const int value)
        {
            m_CurrentProtection += value;
        }

        void DamageSoakingComponent::DecrementProtection(const int value)
        {
            m_CurrentProtection -= value;
        }

        int DamageSoakingComponent::GetMaximumProtection() const
        {
            return m_MaxProtection;
        }

        void DamageSoakingComponent::SetMaximumProtection(const int value)
        {
            m_MaxProtection = value;
        }

    }
}
