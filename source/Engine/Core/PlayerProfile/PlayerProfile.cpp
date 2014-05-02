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

#include "PlayerProfile.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    PlayerProfile::PlayerProfile()
    {

    }

    PlayerProfile::~PlayerProfile()
    {

    }

    bool PlayerProfile::vInit(const std::string& profileResourceFileName)
    {
        LOG_ASSERT((profileResourceFileName != "") && "Invalid XML file");

        XMLFile xmlFile;
        xmlFile.OpenFile(profileResourceFileName, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        xmlRootElement.GetAttribute("name", &m_ProfileName);

        XMLElement xmlElement = xmlRootElement.GetFirstChildElement("GameplaySettings");
        assert(xmlElement.IsGood() && "XML profile is missing GameplaySettings!");
        if (!LoadGameplaySettings(&xmlElement))
        {
            xmlFile.CloseFile();

            return false;
        }

        xmlElement = xmlRootElement.GetFirstChildElement("GeneralSettings");
        assert(xmlElement.IsGood() && "XML profile is missing GeneralSettings!");
        if (!LoadGeneralSettings(&xmlElement))
        {
            xmlFile.CloseFile();

            return false;
        }

        xmlElement = xmlRootElement.GetFirstChildElement("InputSettings");
        assert(xmlElement.IsGood() && "XML profile is missing InputSettings!");
        if (!LoadInputSettings(&xmlElement))
        {
            xmlFile.CloseFile();

            return false;
        }

        xmlElement = xmlRootElement.GetFirstChildElement("OutputSettings");
        assert(xmlElement.IsGood() && "XML profile is missing OutputSettings!");
        if (!LoadOutputSettings(&xmlElement))
        {
            xmlFile.CloseFile();

            return false;
        }

        xmlFile.CloseFile();

        return true;
    }

    const std::string& PlayerProfile::GetProfileName() const
    {
        return m_ProfileName;
    }

    const GameplaySettings& PlayerProfile::GetGameplaySettings() const
    {
        return m_GameplaySettings;
    }

    const GeneralSettings& PlayerProfile::GetGeneralSettings() const
    {
        return m_GeneralSettings;
    }

    const InputSettings& PlayerProfile::GetInputSettings() const
    {
        return m_InputSettings;
    }

    const OutputSettings& PlayerProfile::GetOutputSettings() const
    {
        return m_OutputSettings;
    }

    GameplaySettings& PlayerProfile::GetGameplaySettings()
    {
        return m_GameplaySettings;
    }

    GeneralSettings& PlayerProfile::GetGeneralSettings()
    {
        return m_GeneralSettings;
    }

    InputSettings& PlayerProfile::GetInputSettings()
    {
        return m_InputSettings;
    }

    OutputSettings& PlayerProfile::GetOutputSettings()
    {
        return m_OutputSettings;
    }

    bool PlayerProfile::LoadGameplaySettings(XMLElement* pXMLData)
    {
        return m_GameplaySettings.vInit(pXMLData);
    }

    bool PlayerProfile::LoadGeneralSettings(XMLElement* pXMLData)
    {
        return m_GeneralSettings.vInit(pXMLData);
    }

    bool PlayerProfile::LoadInputSettings(XMLElement* pXMLData)
    {
        return m_InputSettings.vInit(pXMLData);
    }

    bool PlayerProfile::LoadOutputSettings(XMLElement* pXMLData)
    {
        return m_OutputSettings.vInit(pXMLData);
    }
}
