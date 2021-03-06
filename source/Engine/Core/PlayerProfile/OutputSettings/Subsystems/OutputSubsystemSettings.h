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
    class OutputSubsystemSettings
    {
    public:
        struct OutputSubsystemSettingsData
        {
            std::vector<std::string> devices;
            std::string name;
            std::string stimuli;
            std::map<std::string, std::string> settings;
        };

        OutputSubsystemSettings();
        virtual ~OutputSubsystemSettings();

        virtual bool vInit(XMLElement* pXMLData);

        const OutputSubsystemSettings::OutputSubsystemSettingsData& GetOutputSubsystemSettingsData() const;
        OutputSubsystemSettings::OutputSubsystemSettingsData& GetOutputSubsystemSettingsData();

    private:
        bool LoadOutputSubsystem(XMLElement* pXMLData);

    protected:
        OutputSubsystemSettings::OutputSubsystemSettingsData m_OutputSubsystemSettings;
    };
}
