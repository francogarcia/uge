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

#include "AuralPreferences.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    AuralPreferences::AuralPreferences()
    {

    }

    AuralPreferences::~AuralPreferences()
    {

    }

    bool AuralPreferences::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("Settings");
        if (xmlElement.IsGood())
        {
            std::string type;
            xmlElement.GetAttribute("type", &type);

            xmlElement = pXMLData->GetFirstChildElement("Music");
            if (xmlElement.IsGood())
            {
                xmlElement.GetBoolAttribute("enabled", &m_MusicSettings.bIsEnabled);
                xmlElement.GetFloatAttribute("volume", &m_MusicSettings.fVolume);

                xmlElement = pXMLData->GetFirstChildElement("SFX");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetBoolAttribute("enabled", &m_SfxSettings.bIsEnabled);
                    xmlElement.GetFloatAttribute("volume", &m_SfxSettings.fVolume);

                    xmlElement = pXMLData->GetFirstChildElement("Speech");
                    if (xmlElement.IsGood())
                    {
                        xmlElement.GetBoolAttribute("enabled", &m_SpeechSettings.bIsEnabled);
                        xmlElement.GetFloatAttribute("volume", &m_SpeechSettings.fVolume);

                        return true;
                    }
                }
            }
        }

        return false;
    }

    const AuralPreferences::AudioSettings& AuralPreferences::GetMusicSettings() const
    {
        return m_MusicSettings;
    }

    const AuralPreferences::AudioSettings& AuralPreferences::GetSFXSettings() const
    {
        return m_SfxSettings;
    }

    const AuralPreferences::AudioSettings& AuralPreferences::GetSpeechSettings() const
    {
        return m_SpeechSettings;
    }

}
