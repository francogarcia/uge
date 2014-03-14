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
