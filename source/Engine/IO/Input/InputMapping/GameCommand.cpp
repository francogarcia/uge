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

#include "GameCommand.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/File/XMLFile.h>

namespace uge
{

    namespace InputMapping
    {

        GameCommand::GameCommand()
        {

        }

        GameCommand::~GameCommand()
        {

        }

        void GameCommand::Init(const std::string& gameCommandListFilename)
        {
            XMLFile gameCommandList;
            if (!gameCommandList.OpenFile(gameCommandListFilename, File::FileMode::FileReadOnly))
            {
                LOG_FATAL(std::string("ERROR: Could not load the input context file: " + gameCommandListFilename + "."));
            }

            XMLElement xmlRootElement(gameCommandList.GetRootElement());
            assert(xmlRootElement.IsGood());
            // Read all actions.
            XMLElement actionElements(xmlRootElement.GetFirstChildElement("Actions"));
            for (XMLElement actionElement = actionElements.GetFirstChildElement();
                 actionElement.IsGood();
                 actionElement = actionElement.GetNextSiblingElement())
            {
                std::string actionName;
                actionElement.GetAttribute("name", &actionName);

                Action action = static_cast<Action>(m_Actions.size());
                m_Actions[actionName] = action;
            }

            // Read all states.
            XMLElement stateElements(xmlRootElement.GetFirstChildElement("States"));
            for (XMLElement stateElement = stateElements.GetFirstChildElement();
                 stateElement.IsGood();
                 stateElement = stateElement.GetNextSiblingElement())
            {
                std::string stateName;
                stateElement.GetAttribute("name", &stateName);

                State state = static_cast<State>(m_States.size());
                m_States[stateName] = state;
            }

            // Read all ranges.
            XMLElement rangeElements(xmlRootElement.GetFirstChildElement("Ranges"));
            for (XMLElement rangeElement = rangeElements.GetFirstChildElement();
                 rangeElement.IsGood();
                 rangeElement = rangeElement.GetNextSiblingElement())
            {
                std::string rangeName;
                rangeElement.GetAttribute("name", &rangeName);

                Range range = static_cast<Range>(m_Ranges.size());
                m_Ranges[rangeName] = range;
            }

            gameCommandList.CloseFile();
        }

        Action GameCommand::GetAction(const std::string& actionName) const
        {
            assert(m_Actions.find(actionName) != m_Actions.end());

            return m_Actions.find(actionName)->second;
        }

        State GameCommand::GetState(const std::string& stateName) const
        {
            assert(m_States.find(stateName) != m_States.end());

            return m_States.find(stateName)->second;
        }

        Range GameCommand::GetRange(const std::string& rangeName) const
        {
            assert(m_Ranges.find(rangeName) != m_Ranges.end());

            return m_Ranges.find(rangeName)->second;
        }    
    }

}
