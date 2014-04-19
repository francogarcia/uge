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
 */

#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class GraphicalPreferences
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

        GraphicalPreferences();
        virtual ~GraphicalPreferences();

        virtual bool vInit(XMLElement* pXMLData);

        const GraphicalPreferences::WindowSettings& GetWindowSettings() const;
        const GraphicalPreferences::RendererSettings& GetRendererSettings() const;
        const GraphicalPreferences::TextSettings& GetTextSettings() const;

        // Allow window to be resized.
        GraphicalPreferences::WindowSettings& GetWindowSettings();

    protected:
        GraphicalPreferences::WindowSettings m_WindowSettings;
        GraphicalPreferences::RendererSettings m_RendererSettings;
        GraphicalPreferences::TextSettings m_TextSettings;
    };
}
