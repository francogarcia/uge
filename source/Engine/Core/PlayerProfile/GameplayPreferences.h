#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class GameplayPreferences
    {
    public:
        struct GameplaySettings
        {
            std::string entitySpecializationFileName;
            std::map<std::string, std::string> eventSpecializationFileNames;
        };

        GameplayPreferences();
        virtual ~GameplayPreferences();

        virtual bool vInit(XMLElement* pXMLData);

        const GameplayPreferences::GameplaySettings& GetGameplaySettings() const;

    private:
        bool LoadEntitySpecializations(XMLElement* pXMLData);
        bool LoadEventSpecializations(XMLElement* pXMLData);

    protected:
        GameplayPreferences::GameplaySettings m_GameplaySettings;
    };
}
