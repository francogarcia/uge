#include "GameEngineStd.h"

#include "GameplayPreferences.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    GameplayPreferences::GameplayPreferences()
    {

    }

    GameplayPreferences::~GameplayPreferences()
    {

    }

    bool GameplayPreferences::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("EntitySpecialization");
        assert(xmlElement.IsGood() && "GameplaySettings is missing EntitySpecialization!");
        if (!LoadEntitySpecializations(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("EventSpecializations");
        assert(xmlElement.IsGood() && "GameplaySettings is missing EventSpecializations!");
        if (!LoadEventSpecializations(&xmlElement))
        {
            return false;
        }

        return true;

        //XMLElement xmlElement = pXMLData->GetFirstChildElement("EntitySpecialization");
        //if (xmlElement.IsGood())
        //{
        //    xmlElement.GetAttribute("resource", &m_GameplaySettings.entitySpecializationFileName);

        //    return true;
        //}

        //return false;
    }

    const GameplayPreferences::GameplaySettings& GameplayPreferences::GetGameplaySettings() const
    {
        return m_GameplaySettings;
    }

    bool GameplayPreferences::LoadEntitySpecializations(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        if (!xmlFile.IsGood())
        {
            LOG_ERROR("XML file could not be opened!");

            return false;
        }

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        if (!xmlRootElement.IsGood())
        {
            LOG_ERROR("Invalid Root in XML File!");

            return false;
        }

        xmlRootElement.GetAttribute("resource", &m_GameplaySettings.entitySpecializationFileName);

        xmlFile.CloseFile();

        return true;
    }

    bool GameplayPreferences::LoadEventSpecializations(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        XMLFile xmlFile;
        xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        if (!xmlFile.IsGood())
        {
            LOG_ERROR("XML file could not be opened!");

            return false;
        }

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        if (!xmlRootElement.IsGood())
        {
            LOG_ERROR("Invalid Root in XML File!");

            return false;
        }

        for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement("EventSpecialization");
             xmlElement.IsGood(); xmlElement = xmlElement.GetNextSiblingElement())
        {
            std::string eventSpecializationName;
            xmlElement.GetAttribute("name", &eventSpecializationName);

            std::string eventSpecializationResource;
            xmlElement.GetAttribute("resource", &eventSpecializationResource);

            m_GameplaySettings.eventSpecializationFileNames.insert(std::make_pair(eventSpecializationName, eventSpecializationResource));
        }

        xmlFile.CloseFile();

        return true;
    }
}
