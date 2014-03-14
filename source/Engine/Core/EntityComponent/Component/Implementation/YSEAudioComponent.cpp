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
