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

#include "YSEAudioComponent.h"

namespace uge
{

    namespace Component
    {

        const char*  YSEAudioComponent::g_ComponentName = "YSEAudioComponent";

        YSEAudioComponent::YSEAudioComponent()
            : m_FileName(""),
              m_SceneNodeName(""),
              m_bLoop(false),
              m_fInitialProgress(0.0f),
              m_fVolume(1.0f)
        {

        }

        YSEAudioComponent::~YSEAudioComponent()
        {

        }

        bool YSEAudioComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("NodeName");
            if (xmlElement.IsGood())
            {
                xmlElement.GetAttribute("n", &m_SceneNodeName);

                xmlElement = pInitXMLData->GetFirstChildElement("FileName");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetAttribute("n", &m_FileName);

                    xmlElement = pInitXMLData->GetFirstChildElement("Volume");
                    if (xmlElement.IsGood())
                    {
                        xmlElement.GetFloatAttribute("v", &m_fVolume);

                        xmlElement = pInitXMLData->GetFirstChildElement("InitialProgress");
                        if (xmlElement.IsGood())
                        {
                            xmlElement.GetFloatAttribute("p", &m_fInitialProgress);

                            xmlElement = pInitXMLData->GetFirstChildElement("Loop");
                            if (xmlElement.IsGood())
                            {
                                xmlElement.GetBoolAttribute("l", &m_bLoop);

                                return true;
                            }
                        }
                    }
                }
            }

            return false;
        }

        void YSEAudioComponent::vPostInit()
        {

        }

        void YSEAudioComponent::vUpdate(const unsigned long dt)
        {

        }

        void YSEAudioComponent::vOnChange()
        {

        }

        const std::string YSEAudioComponent::vGetName() const
        {
            return g_ComponentName;
        }

        const std::string& YSEAudioComponent::vGetSceneNodeName() const
        {
            return m_SceneNodeName;
        }

        const std::string& YSEAudioComponent::GetFileName() const
        {
            return m_FileName;
        }

        const float YSEAudioComponent::GetVolume() const
        {
            return m_fVolume;
        }

        const float YSEAudioComponent::GetInitialProgress() const
        {
            return m_fInitialProgress;
        }

        const bool YSEAudioComponent::GetLooping() const
        {
            return m_bLoop;
        }

    }

}
