#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class AuralPreferences
    {
    public:
        struct AudioSettings
        {
            bool bIsEnabled;
            float fVolume;
        };        

        AuralPreferences();
        virtual ~AuralPreferences();

        virtual bool vInit(XMLElement* pXMLData);

        const AuralPreferences::AudioSettings& GetMusicSettings() const;
        const AuralPreferences::AudioSettings& GetSFXSettings() const;
        const AuralPreferences::AudioSettings& GetSpeechSettings() const;

    protected:
        AuralPreferences::AudioSettings m_MusicSettings;
        AuralPreferences::AudioSettings m_SfxSettings;
        AuralPreferences::AudioSettings m_SpeechSettings;
    };
}
