#include <Utilities/File/XMLFile.h>

/* file: XMLFile.xml
    <?xml version="1.0" encoding="UTF-8"?>
    <rootElement>
      <foo string="value">
          <bar>
            <foobar>Some text value</foobar>
          </bar>
      </foo>
      <quux string="abc" wstring="стур" int="-1" uint="100" float="1.23" double="-1.23" boolean="true"/>
    </rootElement>
 */

int main()
{
#ifdef _DEBUG
    int debugFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    debugFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
    _CrtSetDbgFlag(debugFlag);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    {
#endif
        uge::XMLFile xmlFile;
        if (!xmlFile.OpenFile("XMLFile.xml", uge::File::FileMode::FileReadOnly))
        {
            std::cerr << "Could not load the file." << std::endl;

            exit(EXIT_FAILURE);
        }

        uge::XMLElement xmlRootElement(xmlFile.GetRootElement());
        if (!xmlRootElement.IsGood())
        {
            std::cerr << "Could not read the root element from the file." << std::endl;

            exit(EXIT_FAILURE);
        }
        std::cout << "Root Element: " << xmlRootElement.GetElementName() << std::endl;

        uge::XMLElement xmlElement(xmlRootElement.GetFirstChildElement("foo"));
        if (!xmlElement.IsGood())
        {
            std::cerr << "Could not read the element from the file." << std::endl;

            exit(EXIT_FAILURE);
        }
        std::cout << "Element name: " << xmlElement.GetElementName() << std::endl;

        std::string textValue("");
        if (!xmlElement.GetAttribute("string", &textValue))
        {
            std::cerr << "Could not fetch an attribute from the file." << std::endl;

            exit(EXIT_FAILURE);
        }
        std::cout << "std::string (text in between tags): " << textValue << std::endl;

        uge::XMLElement foobarElement(xmlRootElement.GetFirstChildElement("foo"));
        foobarElement = foobarElement.GetFirstChildElement("bar").GetFirstChildElement("foobar");
        std::string value("");
        foobarElement.GetElementAsText(value);
        std::cout << "Element name: " << foobarElement.GetElementName() << " - Element value: " << value << std::endl;

        uge::XMLElement quux(xmlRootElement.GetLastChildElement("quux"));
        std::cout << "Element name: " << quux.GetElementName() << std::endl;

        std::string stringAttribute("");
        quux.GetAttribute("string", &stringAttribute);
        std::cout << "std::string: " << stringAttribute << std::endl;

        std::wstring wstringAttribute(L"");
        quux.GetAttribute(L"wstring", &wstringAttribute);
        std::wcout << "std::wstring: " << wstringAttribute << std::endl;

        int intAttribute = 0;
        quux.GetIntAttribute("int", &intAttribute);
        std::wcout << "int: " << intAttribute << std::endl;

        unsigned int uintAttribute = 0;
        quux.GetUnsignedIntAttribute("uint", &uintAttribute);
        std::wcout << "uint: " << uintAttribute << std::endl;

        float fFloatAttribute = 0.0f;
        quux.GetFloatAttribute("float", &fFloatAttribute);
        std::wcout << "float: " << fFloatAttribute << std::endl;

        double fDoubleAttribute = 0.0;
        quux.GetDoubleAttribute("double", &fDoubleAttribute);
        std::wcout << "double: " << fDoubleAttribute << std::endl;

        bool boolAttribute = false;
        quux.GetBoolAttribute("boolean", &boolAttribute);
        std::wcout << "bool: " << boolAttribute << std::endl;

        xmlFile.CloseFile();

#ifdef _DEBUG
    }
    std::cerr << "Memory Leaks? " << ((_CrtDumpMemoryLeaks() == 1) ? "yes" : "no") << std::endl;

#endif

    return 0;
}
