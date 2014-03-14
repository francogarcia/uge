#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class InputPreferences
    {
    public:
        InputPreferences();
        virtual ~InputPreferences();

        virtual bool vInit(XMLElement* pXMLData);

        const std::string& GetInputMappingFile() const;

    protected:
        std::string m_InputMappingFile;
    };
}
