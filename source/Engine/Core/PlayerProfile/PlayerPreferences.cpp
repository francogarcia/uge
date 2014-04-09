/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

#include "GameEngineStd.h"

#include "PlayerPreferences.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    PlayerPreferences::PlayerPreferences()
    {

    }

    PlayerPreferences::~PlayerPreferences()
    {

    }

    bool PlayerPreferences::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        pXMLData->GetAttribute("player_name", &m_PlayerName);

        XMLElement xmlElement = pXMLData->GetFirstChildElement("Language");
        if (xmlElement.IsGood())
        {
            xmlElement.GetAttribute("name", &m_Language);

            return true;
        }

        return false;
    }

    const std::string& PlayerPreferences::GetPlayerName() const
    {
        return m_PlayerName;
    }

    const std::string& PlayerPreferences::GetLanguage() const
    {
        return m_Language;
    }
}
