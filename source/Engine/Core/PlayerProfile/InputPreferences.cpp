#include "GameEngineStd.h"

#include "InputPreferences.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    InputPreferences::InputPreferences()
    {

    }

    InputPreferences::~InputPreferences()
    {

    }

    bool InputPreferences::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        pXMLData->GetAttribute("resource", &m_InputMappingFile);

        return true;
    }

    const std::string& InputPreferences::GetInputMappingFile() const
    {
        return m_InputMappingFile;
    }
}
