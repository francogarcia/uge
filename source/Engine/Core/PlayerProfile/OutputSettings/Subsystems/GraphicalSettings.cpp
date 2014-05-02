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

#include "GraphicalSettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    GraphicalSettings::GraphicalSettings()
    {

    }

    GraphicalSettings::~GraphicalSettings()
    {

    }

    bool GraphicalSettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("Window");
        if (xmlElement.IsGood())
        {
            xmlElement.GetUnsignedIntAttribute("width", &m_WindowSettings.width);
            xmlElement.GetUnsignedIntAttribute("height", &m_WindowSettings.height);
            xmlElement.GetUnsignedIntAttribute("pixel_depth", &m_WindowSettings.pixelDepth);
            xmlElement.GetBoolAttribute("vsync", &m_WindowSettings.bVSync);
            xmlElement.GetBoolAttribute("fullscreen", &m_WindowSettings.bFullScreen);

            xmlElement = pXMLData->GetFirstChildElement("Renderer");
            if (xmlElement.IsGood())
            {
                xmlElement.GetAttribute("name", &m_RendererSettings.name);

                xmlElement = pXMLData->GetFirstChildElement("Text");
                if (xmlElement.IsGood())
                {
                    XMLElement textElement = xmlElement.GetFirstChildElement("Font");
                    if (xmlElement.IsGood())
                    {
                        textElement.GetAttribute("resource", &m_TextSettings.fontName);
                        textElement.GetUnsignedIntAttribute("size", &m_TextSettings.fontSize);

                        XMLElement subtitlesElement = xmlElement.GetFirstChildElement("Subtitles");
                        if (xmlElement.IsGood())
                        {
                            subtitlesElement.GetBoolAttribute("enabled", &m_TextSettings.bUseSubtitles);

                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    const GraphicalSettings::WindowSettings& GraphicalSettings::GetWindowSettings() const
    {
        return m_WindowSettings;
    }

    const GraphicalSettings::RendererSettings& GraphicalSettings::GetRendererSettings() const
    {
        return m_RendererSettings;
    }

    const GraphicalSettings::TextSettings& GraphicalSettings::GetTextSettings() const
    {
        return m_TextSettings;
    }

    GraphicalSettings::WindowSettings& GraphicalSettings::GetWindowSettings()
    {
        return m_WindowSettings;
    }

}
