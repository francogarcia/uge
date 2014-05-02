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

#include "OutputSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    OutputSettings::OutputSettings()
    {

    }

    OutputSettings::~OutputSettings()
    {

    }

    bool OutputSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("OutputSubsystems");
        assert(xmlElement.IsGood() && "OutputSettings is missing OutputSubsystems!");
        if (!LoadOutputSubsystems(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("TextSettings");
        assert(xmlElement.IsGood() && "OutputSettings is missing TextSettings!");
        if (!LoadTextSettings(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("WindowSettings");
        assert(xmlElement.IsGood() && "OutputSettings is missing WindowSettings!");
        if (!LoadWindowSettings(&xmlElement))
        {
            return false;
        }

        return true;
    }

    const OutputSettings::OutputSettingsData& OutputSettings::GetOutputSettingsData() const
    {
        return m_OutputSettingsData;
    }

    OutputSettings::OutputSettingsData& OutputSettings::GetOutputSettingsData()
    {
        return m_OutputSettingsData;
    }

    bool OutputSettings::LoadOutputSubsystems(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        if (!xmlFile.IsGood())
        {
            LOG_ERROR("XML file could not be opened!");

            return false;
        }

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        if (!xmlRootElement.IsGood())
        {
            LOG_ERROR("Invalid Root in XML File!");

            return false;
        }

        for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement("OutputSubsystem");
             xmlElement.IsGood(); xmlElement = xmlElement.GetNextSiblingElement())
        {
            OutputSubsystemSettings outputSubsystem;
            outputSubsystem.vInit(&xmlElement);

            m_OutputSettingsData.subsystems.insert(std::make_pair(outputSubsystem.GetOutputSubsystemSettingsData().name, outputSubsystem));
        }

        xmlFile.CloseFile();

        return true;
    }

    bool OutputSettings::LoadTextSettings(XMLElement* pXMLData)
    {
        return m_OutputSettingsData.text.vInit(pXMLData);
    }

    bool OutputSettings::LoadWindowSettings(XMLElement* pXMLData)
    {
        return m_OutputSettingsData.window.vInit(pXMLData);
    }
}
