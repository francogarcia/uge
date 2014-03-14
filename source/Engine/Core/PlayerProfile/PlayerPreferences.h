#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class PlayerPreferences
    {
    public:
        PlayerPreferences();
        virtual ~PlayerPreferences();

        virtual bool vInit(XMLElement* pXMLData);

        const std::string& GetPlayerName() const;
        const std::string& GetLanguage() const;

    protected:
        std::string m_PlayerName;
        std::string m_Language;
    };
}
