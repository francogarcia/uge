#include "GameEngineStd.h"

#include "PlayerProfiles.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    PlayerProfile::PlayerProfile()
    {

    }

    PlayerProfile::~PlayerProfile()
    {

    }

    bool PlayerProfile::Init(const std::string& profileResourceFileName)
    {
        LOG_ASSERT((profileResourceFileName != "") && "Invalid XML file");

        bool bSuccess = true;

        XMLFile xmlFile;
        xmlFile.OpenFile(profileResourceFileName, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        xmlRootElement.GetAttribute("name", &m_ProfileName);

        XMLElement xmlElement = xmlRootElement.GetFirstChildElement("GeneralSettings");
        assert(xmlElement.IsGood() && "XML profile is missing GeneralSettings!");
        bSuccess &= LoadGeneralSettings(&xmlElement);

        xmlElement = xmlRootElement.GetFirstChildElement("InputSettings");
        assert(xmlElement.IsGood() && "XML profile is missing InputSettings!");
        bSuccess &= LoadInputSettings(&xmlElement);

        xmlElement = xmlRootElement.GetFirstChildElement("OutputSettings");
        assert(xmlElement.IsGood() && "XML profile is missing OutputSettings!");
        bSuccess &= LoadOutputSettings(&xmlElement);

        xmlElement = xmlRootElement.GetFirstChildElement("GameplaySettings");
        assert(xmlElement.IsGood() && "XML profile is missing GameplaySettings!");
        bSuccess &= LoadGameplaySettings(&xmlElement);

        xmlFile.CloseFile();

        return bSuccess;
    }

    const std::string& PlayerProfile::GetProfileName() const
    {
        return m_ProfileName;
    }

    const AuralPreferences& PlayerProfile::GetAuralPreferences() const
    {
        return m_AudioPreferences;
    }

    const GameplayPreferences& PlayerProfile::GetGameplayPreferences() const
    {
        return m_GameplayPreferences;
    }

    const GraphicalPreferences& PlayerProfile::GetGraphicalPreferences() const
    {
        return m_GraphicsPreferences;
    }

    const InputPreferences& PlayerProfile::GetInputPreferences() const
    {
        return m_InputPreferences;
    }

    const PlayerPreferences& PlayerProfile::GetPlayerPreferences() const
    {
        return m_PlayerPreferences;
    }

    bool PlayerProfile::LoadGameplaySettings(XMLElement* pXMLData)
    {
        return m_GameplayPreferences.vInit(pXMLData);
    }

    bool PlayerProfile::LoadGeneralSettings(XMLElement* pXMLData)
    {
        XMLElement xmlElement = pXMLData->GetFirstChildElement("Preferences");
        assert(xmlElement.IsGood() && "GeneralSettings is missing Preferences!");

        std::string resource;
        xmlElement.GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        bool bSuccess = m_PlayerPreferences.vInit(&xmlRootElement);

        xmlFile.CloseFile();

        return bSuccess;
    }

    bool PlayerProfile::LoadInputSettings(XMLElement* pXMLData)
    {
        XMLElement xmlElement = pXMLData->GetFirstChildElement("Mapping");
        assert(xmlElement.IsGood() && "InputSettings is missing Mapping!");

        std::string resource;
        xmlElement.GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        bool bSuccess = LoadInputPreferences(&xmlRootElement);

        xmlFile.CloseFile();

        return bSuccess;
    }

    bool PlayerProfile::LoadOutputSettings(XMLElement* pXMLData)
    {
        bool bSuccess = true;

        XMLElement xmlElement = pXMLData->GetFirstChildElement("PrimaryOutput");
        assert(xmlElement.IsGood() && "OutputSettings is missing PrimaryOutput!");

        std::string primaryOutputType;
        xmlElement.GetAttribute("type", &primaryOutputType);
        if (primaryOutputType == "graphical")
        {
            LoadGraphicalPreferences(&xmlElement);
        }
        else if (primaryOutputType == "aural")
        {
            LoadAuralPreferences(&xmlElement);
        }
        else
        {
            LOG_ERROR("The profile is missing the PrimaryOutput!");

            bSuccess = false;
        }

        xmlElement = pXMLData->GetFirstChildElement("SecondaryOutput");
        if (xmlElement.IsGood())
        {
            std::string secondaryOutputType;
            xmlElement.GetAttribute("type", &secondaryOutputType);
            LOG_ASSERT(primaryOutputType != secondaryOutputType && "Output types must be different!");

            if (secondaryOutputType == "graphical")
            {
                LoadGraphicalPreferences(&xmlElement);
            }
            else if (secondaryOutputType == "aural")
            {
                LoadAuralPreferences(&xmlElement);
            }
        }
        else
        {
            LOG_WARNING("OutputSettings is missing SecondaryOutput.");
        }

        return bSuccess;
    }

    bool PlayerProfile::LoadAuralPreferences(XMLElement* pXMLData)
    {
        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        bool bSuccess = m_AudioPreferences.vInit(&xmlRootElement);

        xmlFile.CloseFile();

        return bSuccess;
    }

    bool PlayerProfile::LoadGraphicalPreferences(XMLElement* pXMLData)
    {
        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        assert(xmlFile.IsGood() && "XML file could not be opened!");

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        bool bSuccess = m_GraphicsPreferences.vInit(&xmlRootElement);

        xmlFile.CloseFile();

        return bSuccess;
    }

    bool PlayerProfile::LoadInputPreferences(XMLElement* pXMLData)
    {
        return m_InputPreferences.vInit(pXMLData);
    }

    bool PlayerProfile::LoadPlayerPreferences(XMLElement* pXMLData)
    {
        return m_PlayerPreferences.vInit(pXMLData);
    }

    // Player profile

    PlayerProfiles::PlayerProfiles()
        : m_pCurrentProfile(nullptr)
    {

    }

    PlayerProfiles::~PlayerProfiles()
    {

    }

    bool PlayerProfiles::Init(const std::string& profileListResourceFileName)
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
            if (!playerProfile.Init(profileResource))
            {
                LOG_ERROR("Error loading the profile: " + profileResource);

                return false;
            }

            m_PlayerProfiles[profileName] = playerProfile;
        }

        xmlFile.CloseFile();

        return true;
    }

    bool PlayerProfiles::Destroy()
    {
        m_PlayerProfiles.clear();

        return true;
    }

    const PlayerProfile& PlayerProfiles::GetProfile(const std::string& profileName) const
    {
        const auto& findIt = m_PlayerProfiles.find(profileName);
        assert(findIt != m_PlayerProfiles.end() && "Profile not found!");

        return findIt->second;
    }

    std::vector<std::string> PlayerProfiles::GetProfileNames() const
    {
        std::vector<std::string> profileNames;
        for (const auto& it : m_PlayerProfiles)
        {
            profileNames.push_back(it.first);
        }

        return profileNames;
    }

    void PlayerProfiles::SetCurrentProfile(const std::string& profileName)
    {
        m_pCurrentProfile = &GetProfile(profileName);
    }
    
    const PlayerProfile& PlayerProfiles::GetCurrentProfile() const
    {
        assert(m_pCurrentProfile != nullptr && "Not profile was chosen yet!");

        return *m_pCurrentProfile;
    }
}
