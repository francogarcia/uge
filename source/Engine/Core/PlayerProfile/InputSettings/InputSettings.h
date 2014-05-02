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

#include "Subsystems/InputSubsystemSettings.h"

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class InputSettings
    {
    public:
        struct InputSettingsData
        {
            std::string mappingResource;
            std::map<std::string, InputSubsystemSettings> subsystems;
        };

        InputSettings();
        virtual ~InputSettings();

        virtual bool vInit(XMLElement* pXMLData);

        const InputSettings::InputSettingsData& GetInputSettingsData() const;
        InputSettings::InputSettingsData& GetInputSettingsData();

    private:
        bool LoadInputSubsystemsSettings(XMLElement* pXMLData);
        bool LoadInputMappingSettings(XMLElement* pXMLData);

    protected:
        InputSettings::InputSettingsData m_InputSettings;
    };
}
