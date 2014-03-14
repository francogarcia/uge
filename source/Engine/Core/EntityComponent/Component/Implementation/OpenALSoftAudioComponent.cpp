#include "GameEngineStd.h"

#include "OpenALSoftAudioComponent.h"

namespace uge
{

    namespace Component
    {

        const char*  OpenALSoftAudioComponent::g_ComponentName = "OpenALSoftAudioComponent";

        OpenALSoftAudioComponent::OpenALSoftAudioComponent()
            : m_FileName(""),
              m_SceneNodeName(""),
              m_bLoop(false),
              m_fInitialProgress(0.0f),
              m_fVolume(1.0f)
        {

        }

        OpenALSoftAudioComponent::~OpenALSoftAudioComponent()
        {

        }

        bool OpenALSoftAudioComponent::vInit(XMLElement* pInitXMLData)
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

        void OpenALSoftAudioComponent::vPostInit()
        {

        }

        void OpenALSoftAudioComponent::vUpdate(const unsigned long dt)
        {

        }

        void OpenALSoftAudioComponent::vOnChange()
        {

        }

        const std::string OpenALSoftAudioComponent::vGetName() const
        {
            return g_ComponentName;
        }

        const std::string& OpenALSoftAudioComponent::vGetSceneNodeName() const
        {
            return m_SceneNodeName;
        }

        const std::string& OpenALSoftAudioComponent::GetFileName() const
        {
            return m_FileName;
        }

        const float OpenALSoftAudioComponent::GetVolume() const
        {
            return m_fVolume;
        }

        const float OpenALSoftAudioComponent::GetInitialProgress() const
        {
            return m_fInitialProgress;
        }

        const bool OpenALSoftAudioComponent::GetLooping() const
        {
            return m_bLoop;
        }

    }

}
