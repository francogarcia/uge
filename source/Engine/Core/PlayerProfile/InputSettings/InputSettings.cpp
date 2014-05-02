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

#include "InputSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    InputSettings::InputSettings()
    {

    }

    InputSettings::~InputSettings()
    {

    }

    bool InputSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("InputSubsystems");
        assert(xmlElement.IsGood() && "InputSettings is missing InputSubsystems!");
        if (!LoadInputSubsystemsSettings(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("InputMapping");
        assert(xmlElement.IsGood() && "InputSettings is missing InputMapping!");
        if (!LoadInputMappingSettings(&xmlElement))
        {
            return false;
        }

        return true;
    }

    const InputSettings::InputSettingsData& InputSettings::GetInputSettingsData() const
    {
        return m_InputSettings;
    }

    InputSettings::InputSettingsData& InputSettings::GetInputSettingsData()
    {
        return m_InputSettings;
    }

    bool InputSettings::LoadInputSubsystemsSettings(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement("InputSubsystem");
             xmlElement.IsGood();
             xmlElement = xmlElement.GetNextSiblingElement())
        {
            InputSubsystemSettings inputSubsystem;
            inputSubsystem.vInit(&xmlElement);

            m_InputSettings.subsystems.insert(std::make_pair(inputSubsystem.GetInputSubsystemSettingsData().name, inputSubsystem));
        }

        xmlFile.CloseFile();

        return true;
    }

    bool InputSettings::LoadInputMappingSettings(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        return pXMLData->GetAttribute("resource", &m_InputSettings.mappingResource);
    }
}
