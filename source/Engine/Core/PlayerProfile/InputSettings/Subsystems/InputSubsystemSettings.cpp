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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "GameEngineStd.h"

#include "InputSubsystemSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    InputSubsystemSettings::InputSubsystemSettings()
    {

    }

    InputSubsystemSettings::~InputSubsystemSettings()
    {

    }

    bool InputSubsystemSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        LoadInputSubsystem(pXMLData);

        return true;
    }

    const InputSubsystemSettings::InputSubsystemSettingsData& InputSubsystemSettings::GetInputSubsystemSettingsData() const
    {
        return m_InputSubsystemSettings;
    }

    bool InputSubsystemSettings::LoadInputSubsystem(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        pXMLData->GetAttributeLowerCase("name", &m_InputSubsystemSettings.name);
        pXMLData->GetAttributeLowerCase("stimuli", &m_InputSubsystemSettings.stimuli);

        XMLElement devicesElement = pXMLData->GetFirstChildElement("InputDevices");
        for (XMLElement xmlElement = devicesElement.GetFirstChildElement("InputDevice");
             xmlElement.IsGood();
             xmlElement = xmlElement.GetNextSiblingElement())
        {
            std::string inputDevice;
            xmlElement.GetAttributeLowerCase("device", &inputDevice);

            m_InputSubsystemSettings.devices.push_back(inputDevice);
        }

        XMLElement settingsElement = pXMLData->GetFirstChildElement("Settings");
        for (XMLElement xmlElement = settingsElement.GetFirstChildElement();
             xmlElement.IsGood();
             xmlElement = xmlElement.GetNextSiblingElement())
        {
            std::string key;
            key = xmlElement.GetElementNameLowerCase();

            std::string value;
            xmlElement.GetElementAsText(value);

            m_InputSubsystemSettings.settings.insert(std::make_pair(key, value));
        }

        return true;
    }
}
