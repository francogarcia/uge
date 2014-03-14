#include "GameEngineStd.h"

#include "MoveableComponent.h"

namespace uge
{

    namespace Component
    {

        const char* MoveableComponent::g_ComponentName = "MoveableComponent";

        MoveableComponent::MoveableComponent() : m_Velocity(0.0f, 0.0f, 0.0f), m_fCurrentVelocity(0.0f), m_Acceleration(0.0f, 0.0f, 0.0f)
        {

        }

        MoveableComponent::~MoveableComponent()
        {

        }

        bool MoveableComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("Velocity");
            if (xmlElement.IsGood())
            {
                xmlElement.GetFloatAttribute("vcs", &m_fCurrentVelocity);
                xmlElement.GetFloatAttribute("vdx", &m_Velocity.x);
                xmlElement.GetFloatAttribute("vdy", &m_Velocity.y);
                xmlElement.GetFloatAttribute("vdz", &m_Velocity.z);

                xmlElement = pInitXMLData->GetFirstChildElement("Acceleration");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetFloatAttribute("ax", &m_Acceleration.x);
                    xmlElement.GetFloatAttribute("ay", &m_Acceleration.y);
                    xmlElement.GetFloatAttribute("az", &m_Acceleration.z);

                    return true;
                }
            }

            return false;
        }

        void MoveableComponent::vPostInit()
        {

        }

        void MoveableComponent::vUpdate(const unsigned long dt)
        {

        }

        void MoveableComponent::vOnChange()
        {

        }

        const std::string MoveableComponent::vGetName() const
        {
            return g_ComponentName;
        }

        const Ogre::Vector3 MoveableComponent::GetVelocity() const
        {
            return m_Velocity;
        }

        void MoveableComponent::SetVelocity(const Ogre::Vector3 velocity)
        {
            m_Velocity = velocity;
        }

        const float MoveableComponent::GetCurrentSpeed() const
        {
            return m_fCurrentVelocity;
        }

        void MoveableComponent::SetCurrentSpeed(const float fCurrentSpeed)
        {
            m_fCurrentVelocity = fCurrentSpeed;
        }

        const Ogre::Vector3 MoveableComponent::GetAcceleration() const
        {
            return m_Acceleration;
        }

        void MoveableComponent::SetAcceleration(const Ogre::Vector3 acceleration)
        {
            m_Acceleration = acceleration;
        }

    }

}
