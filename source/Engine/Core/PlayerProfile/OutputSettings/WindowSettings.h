/*
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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
    class WindowSettings
    {
    public:
        struct WindowSettingsData
        {
            unsigned int width;
            unsigned int height;
            unsigned int pixelDepth;
            bool bVSync;
            bool bFullScreen;
        };

        WindowSettings();
        virtual ~WindowSettings();

        virtual bool vInit(XMLElement* pXMLData);

        const WindowSettings::WindowSettingsData& GetWindowSettingsData() const;
        WindowSettings::WindowSettingsData& GetWindowSettingsData();

    private:
        bool LoadWindowSettings(XMLElement* pXMLData);

    protected:
        WindowSettings::WindowSettingsData m_WindowSettings;
    };
}
