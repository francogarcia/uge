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

#include "GeneralSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    GeneralSettings::GeneralSettings()
    {

    }

    GeneralSettings::~GeneralSettings()
    {

    }

    bool GeneralSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("PlayerPreferences");
        assert(xmlElement.IsGood() && "GeneralSettings is missing PlayerPreferences!");
        if (!LoadPlayerPreferences(&xmlElement))
        {
            return false;
        }

        return true;
    }

    const GeneralSettings::GeneralSettingsData& GeneralSettings::GetGeneralSettingsData() const
    {
        return m_GeneralSettings;
    }

    bool GeneralSettings::LoadPlayerPreferences(XMLElement* pXMLData)
    {
        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");
        
        XMLElement xmlElement = xmlRootElement.GetFirstChildElement("Language");
        if (!xmlElement.GetAttributeLowerCase("name", &m_GeneralSettings.language))
        {
            return false;
        }

        xmlFile.CloseFile();

        return true;
    }
}
