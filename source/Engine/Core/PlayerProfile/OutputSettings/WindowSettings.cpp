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

#include "WindowSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    WindowSettings::WindowSettings()
    {

    }

    WindowSettings::~WindowSettings()
    {

    }

    bool WindowSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        if (!LoadWindowSettings(pXMLData))
        {
            return false;
        }

        return true;
    }

    const WindowSettings::WindowSettingsData& WindowSettings::GetWindowSettingsData() const
    {
        return m_WindowSettings;
    }

    WindowSettings::WindowSettingsData& WindowSettings::GetWindowSettingsData()
    {
        return m_WindowSettings;
    }

    bool WindowSettings::LoadWindowSettings(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        XMLElement propertiesElement = xmlRootElement.GetFirstChildElement("Properties");
        if (!propertiesElement.IsGood())
        {
            xmlFile.CloseFile();

            return false;
        }

        propertiesElement.GetUnsignedIntAttribute("width", &m_WindowSettings.width);
        propertiesElement.GetUnsignedIntAttribute("height", &m_WindowSettings.height);
        propertiesElement.GetUnsignedIntAttribute("pixel_depth", &m_WindowSettings.pixelDepth);
        propertiesElement.GetBoolAttribute("vsync", &m_WindowSettings.bVSync);
        propertiesElement.GetBoolAttribute("fullscreen", &m_WindowSettings.bFullScreen);

        xmlFile.CloseFile();

        return true;
    }
}
