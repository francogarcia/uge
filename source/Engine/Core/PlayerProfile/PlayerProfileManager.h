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

#include "PlayerProfile.h"

namespace uge
{
    class PlayerProfileManager
    {
    public:
        PlayerProfileManager();
        ~PlayerProfileManager();

        bool Init(const std::string& profileListResourceFileName);
        bool Destroy();
        
        const PlayerProfile& GetProfile(const std::string& profileName) const;
        std::vector<std::string> GetProfileNames() const;
        
        void SetActiveProfile(const std::string& profileName);
        const PlayerProfile& GetActiveProfile() const;

    private:
        std::map<std::string, PlayerProfile> m_PlayerProfiles;

        const PlayerProfile* m_pActiveProfile;
    };
}
