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

#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class GraphicalSettings
    {
    public:
        struct WindowSettings
        {
            unsigned int width;
            unsigned int height;
            unsigned int pixelDepth;
            bool bVSync;
            bool bFullScreen;
        };

        struct RendererSettings
        {
            std::string name;
        };

        struct TextSettings
        {
            std::string fontName;
            unsigned int fontSize;
            bool bUseSubtitles;
        };

        GraphicalSettings();
        virtual ~GraphicalSettings();

        virtual bool vInit(XMLElement* pXMLData);

        const GraphicalSettings::WindowSettings& GetWindowSettings() const;
        const GraphicalSettings::RendererSettings& GetRendererSettings() const;
        const GraphicalSettings::TextSettings& GetTextSettings() const;

        // Allow window to be resized.
        GraphicalSettings::WindowSettings& GetWindowSettings();

    protected:
        GraphicalSettings::WindowSettings m_WindowSettings;
        GraphicalSettings::RendererSettings m_RendererSettings;
        GraphicalSettings::TextSettings m_TextSettings;
    };
}
