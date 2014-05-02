/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "GameEngineStd.h"

#include "GameplaySettings.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    GameplaySettings::GameplaySettings()
    {

    }

    GameplaySettings::~GameplaySettings()
    {

    }

    bool GameplaySettings::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("AutomationSpecialization");
        assert(xmlElement.IsGood() && "GameplaySettingsData is missing AutomationSpecialization!");
        if (!LoadAutomationSpecializations(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("EntitySpecialization");
        assert(xmlElement.IsGood() && "GameplaySettingsData is missing EntitySpecialization!");
        if (!LoadEntitySpecializations(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("EventSpecializations");
        assert(xmlElement.IsGood() && "GameplaySettingsData is missing EventSpecializations!");
        if (!LoadEventSpecializations(&xmlElement))
        {
            return false;
        }

        xmlElement = pXMLData->GetFirstChildElement("ProjectionSpecialization");
        assert(xmlElement.IsGood() && "GameplaySettingsData is missing ProjectionSpecialization!");
        if (!LoadProjectionSpecializations(&xmlElement))
        {
            return false;
        }

        return true;
    }

    const GameplaySettings::GameplaySettingsData& GameplaySettings::GetGameplaySettingsData() const
    {
        return m_GameplaySettings;
    }

    GameplaySettings::GameplaySettingsData& GameplaySettings::GetGameplaySettingsData()
    {
        return m_GameplaySettings;
    }

    bool GameplaySettings::LoadAutomationSpecializations(XMLElement* pXMLData)
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

        for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement("AutomationScript");
             xmlElement.IsGood(); xmlElement = xmlElement.GetNextSiblingElement())
        {
            std::string scriptResource;
            xmlElement.GetAttribute("resource", &scriptResource);

            m_GameplaySettings.automationSpecializationResources.push_back(scriptResource);
        }

        xmlFile.CloseFile();

        return true;
    }

    bool GameplaySettings::LoadEntitySpecializations(XMLElement* pXMLData)
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

        xmlRootElement.GetAttribute("resource", &m_GameplaySettings.entitySpecializationResource);

        xmlFile.CloseFile();

        return true;
    }

    bool GameplaySettings::LoadEventSpecializations(XMLElement* pXMLData)
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

            m_GameplaySettings.eventSpecializationResources.insert(std::make_pair(eventSpecializationName, eventSpecializationResource));
        }

        xmlFile.CloseFile();

        return true;
    }

    bool GameplaySettings::LoadProjectionSpecializations(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        std::string resource;
        pXMLData->GetAttribute("resource", &resource);

        // TODO: refactor and abstract projection settings.
        //XMLFile xmlFile;
        //xmlFile.OpenFile(resource, File::FileMode::FileReadOnly);
        //if (!xmlFile.IsGood())
        //{
        //    LOG_ERROR("XML file could not be opened!");

        //    return false;
        //}

        //XMLElement xmlRootElement(xmlFile.GetRootElement());
        //if (!xmlRootElement.IsGood())
        //{
        //    LOG_ERROR("Invalid Root in XML File!");

        //    return false;
        //}

        //xmlRootElement.GetAttribute("resource", &m_GameplaySettings.projectionSpecializationResource);

        //xmlFile.CloseFile();

        m_GameplaySettings.projectionSpecializationResource = resource;

        return true;
    }
}
