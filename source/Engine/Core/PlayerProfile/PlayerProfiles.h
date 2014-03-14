#pragma once

#include <Utilities/File/XMLFile.h>

#include "AuralPreferences.h"
#include "GameplayPreferences.h"
#include "GraphicalPreferences.h"
#include "InputPreferences.h"
#include "PlayerPreferences.h"

namespace uge
{
    class PlayerProfiles;

    class PlayerProfile
    {
    public:
        PlayerProfile();
        ~PlayerProfile();

        bool Init(const std::string& profileResourceFileName);

        const std::string& GetProfileName() const;

        const AuralPreferences& GetAuralPreferences() const;
        const GameplayPreferences& GetGameplayPreferences() const;
        const GraphicalPreferences& GetGraphicalPreferences() const;
        const InputPreferences& GetInputPreferences() const;
        const PlayerPreferences& GetPlayerPreferences() const;

    private:
        bool LoadGameplaySettings(XMLElement* pXMLData);
        bool LoadGeneralSettings(XMLElement* pXMLData);
        bool LoadInputSettings(XMLElement* pXMLData);
        bool LoadOutputSettings(XMLElement* pXMLData);

        bool LoadAuralPreferences(XMLElement* pXMLData);
        bool LoadGraphicalPreferences(XMLElement* pXMLData);
        bool LoadInputPreferences(XMLElement* pXMLData);
        bool LoadPlayerPreferences(XMLElement* pXMLData);

    private:
        std::string m_ProfileName;

        AuralPreferences m_AudioPreferences;
        GameplayPreferences m_GameplayPreferences;
        GraphicalPreferences m_GraphicsPreferences;
        InputPreferences m_InputPreferences;
        PlayerPreferences m_PlayerPreferences;
    };

    class PlayerProfiles
    {
    public:
        PlayerProfiles();
        ~PlayerProfiles();

        bool Init(const std::string& profileListResourceFileName);
        bool Destroy();
        
        const PlayerProfile& GetProfile(const std::string& profileName) const;
        std::vector<std::string> GetProfileNames() const;
        
        void SetCurrentProfile(const std::string& profileName);
        const PlayerProfile& GetCurrentProfile() const;

    private:
        std::map<std::string, PlayerProfile> m_PlayerProfiles;

        const PlayerProfile* m_pCurrentProfile;
    };
}
