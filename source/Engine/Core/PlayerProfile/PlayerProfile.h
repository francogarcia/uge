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

#include "GameplaySettings/GameplaySettings.h"
#include "GeneralSettings/GeneralSettings.h"
#include "InputSettings/InputSettings.h"
#include "OutputSettings/OutputSettings.h"

namespace uge
{

    class PlayerProfile
    {
    public:
        PlayerProfile();
        virtual ~PlayerProfile();

        virtual bool vInit(const std::string& profileResourceFileName);

        const std::string& GetProfileName() const;

        const GameplaySettings& GetGameplaySettings() const;
        const GeneralSettings& GetGeneralSettings() const;
        const InputSettings& GetInputSettings() const;
        const OutputSettings& GetOutputSettings() const;

        GameplaySettings& GetGameplaySettings();
        GeneralSettings& GetGeneralSettings();
        InputSettings& GetInputSettings();
        OutputSettings& GetOutputSettings();

    private:
        bool LoadGameplaySettings(XMLElement* pXMLData);
        bool LoadGeneralSettings(XMLElement* pXMLData);
        bool LoadInputSettings(XMLElement* pXMLData);
        bool LoadOutputSettings(XMLElement* pXMLData);

    protected:
        std::string m_ProfileName;

        GameplaySettings m_GameplaySettings;
        GeneralSettings m_GeneralSettings;
        InputSettings m_InputSettings;
        OutputSettings m_OutputSettings;
    };

}
