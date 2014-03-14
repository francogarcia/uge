#include "GameEngineStd.h"

#include "OgreGraphicalComponent.h"

namespace uge
{

    namespace Component
    {

        const char* OgreGraphicalComponent::g_ComponentName = "OgreGraphicalComponent";

        OgreGraphicalComponent::OgreGraphicalComponent()
            : m_NodeName(""),
              m_MeshFileName(""),
              m_MaterialFileName(""),
              m_pSceneNode(nullptr)
        {

        }

        OgreGraphicalComponent::~OgreGraphicalComponent()
        {

        }

        bool OgreGraphicalComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("NodeName");
            if (xmlElement.IsGood())
            {
                xmlElement.GetAttribute("n", &m_NodeName);

                xmlElement = pInitXMLData->GetFirstChildElement("MeshFileName");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetAttribute("m", &m_MeshFileName);

                    xmlElement = pInitXMLData->GetFirstChildElement("MaterialFileName");
                    if (xmlElement.IsGood())
                    {
                        xmlElement.GetAttribute("n", &m_MaterialFileName);

                        return true;
                    }
                }
            }

            return false;
        }

        void OgreGraphicalComponent::vPostInit()
        {

        }

        void OgreGraphicalComponent::vUpdate(const unsigned long dt)
        {

        }

        void OgreGraphicalComponent::vOnChange()
        {

        }

        const std::string OgreGraphicalComponent::vGetName() const
        {
            return g_ComponentName;
        }

        const std::string& OgreGraphicalComponent::vGetSceneNodeName() const
        {
            return m_NodeName;
        }

        const std::string& OgreGraphicalComponent::GetMeshFileName() const
        {
            return m_MeshFileName;
        }

        const std::string& OgreGraphicalComponent::GetMaterialFileName() const
        {
            return m_MaterialFileName;
        }

        Ogre::SceneNode* OgreGraphicalComponent::GetSceneNode() const
        {
            return m_pSceneNode;
        }

        void OgreGraphicalComponent::SetSceneNode(Ogre::SceneNode* pSceneNode)
        {
            m_pSceneNode = pSceneNode;
        }

    }

}
