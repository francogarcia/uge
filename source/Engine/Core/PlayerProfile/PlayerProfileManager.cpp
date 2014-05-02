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

#include "PlayerProfileManager.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    PlayerProfileManager::PlayerProfileManager()
        : m_pActiveProfile(nullptr)
    {

    }

    PlayerProfileManager::~PlayerProfileManager()
    {

    }

    bool PlayerProfileManager::Init(const std::string& profileListResourceFileName)
    {
        LOG_ASSERT(profileListResourceFileName != "" && "Invalid file name!");

        XMLFile xmlFile;
        xmlFile.OpenFile(profileListResourceFileName, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement();
             xmlElement.IsGood();
             xmlElement = xmlElement.GetNextSiblingElement())
        {
            std::string profileName;
            xmlElement.GetAttribute("name", &profileName);

            std::string profileResource;
            xmlElement.GetAttribute("resource", &profileResource);

            PlayerProfile playerProfile;
            if (!playerProfile.vInit(profileResource))
            {
                LOG_ERROR("Error loading the profile: " + profileResource);

                return false;
            }

            m_PlayerProfiles[profileName] = playerProfile;
        }

        xmlFile.CloseFile();

        return true;
    }

    bool PlayerProfileManager::Destroy()
    {
        m_PlayerProfiles.clear();

        return true;
    }

    const PlayerProfile& PlayerProfileManager::GetProfile(const std::string& profileName) const
    {
        const auto& findIt = m_PlayerProfiles.find(profileName);
        assert(findIt != m_PlayerProfiles.end() && "Profile not found!");

        return findIt->second;
    }

    std::vector<std::string> PlayerProfileManager::GetProfileNames() const
    {
        std::vector<std::string> profileNames;
        for (const auto& it : m_PlayerProfiles)
        {
            profileNames.push_back(it.first);
        }

        return profileNames;
    }

    void PlayerProfileManager::SetActiveProfile(const std::string& profileName)
    {
        m_pActiveProfile = &GetProfile(profileName);
    }
    
    const PlayerProfile& PlayerProfileManager::GetActiveProfile() const
    {
        assert(m_pActiveProfile != nullptr && "Not profile was chosen yet!");

        return *m_pActiveProfile;
    }
}
