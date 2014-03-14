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
