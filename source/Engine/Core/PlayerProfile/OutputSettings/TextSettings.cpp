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

#include "TextSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    TextSettings::TextSettings()
    {

    }

    TextSettings::~TextSettings()
    {

    }

    bool TextSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        if (!LoadTextSettings(pXMLData))
        {
            return false;
        }

        return true;
    }

    const TextSettings::TextSettingsData& TextSettings::GetTextSettingsData() const
    {
        return m_TextSettings;
    }

    TextSettings::TextSettingsData& TextSettings::GetTextSettingsData()
    {
        return m_TextSettings;
    }

    bool TextSettings::LoadTextSettings(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        XMLElement textElement = xmlRootElement.GetFirstChildElement("Font");
        if (!textElement.IsGood())
        {
            xmlFile.CloseFile();

            return false;
        }

        textElement.GetAttribute("resource", &m_TextSettings.fontName);
        textElement.GetUnsignedIntAttribute("size", &m_TextSettings.fontSize);

        XMLElement subtitlesElement = xmlRootElement.GetFirstChildElement("Subtitles");
        if (!subtitlesElement.IsGood())
        {
            xmlFile.CloseFile();

            return false;
        }

        subtitlesElement.GetBoolAttribute("enabled", &m_TextSettings.bUseSubtitles);

        xmlFile.CloseFile();

        return true;
    }

}
