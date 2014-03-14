#include "SpaceshipGameStd.h"

#include "DamageInflictingComponent.h"

namespace sg
{
    namespace Component
    {

        const char* DamageInflictingComponent::g_ComponentName = "DamageInflictingComponent";

        DamageInflictingComponent::DamageInflictingComponent()
            : m_DamageOutput(0)
        {

        }

        DamageInflictingComponent::~DamageInflictingComponent()
        {

        }

        bool DamageInflictingComponent::vInit(uge::XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            uge::XMLElement xmlElement = pInitXMLData->GetFirstChildElement("DamageOutput");
            if (xmlElement.IsGood())
            {
                xmlElement.GetIntAttribute("value", &m_DamageOutput);

                return true;
            }

            return false;
        }

        void DamageInflictingComponent::vPostInit()
        {

        }

        void DamageInflictingComponent::vUpdate(const unsigned long dt)
        {

        }

        void DamageInflictingComponent::vOnChange()
        {

        }

        const std::string DamageInflictingComponent::vGetName() const
        {
            return g_ComponentName;
        }

        int DamageInflictingComponent::GetDamageOutput() const
        {
            return m_DamageOutput;
        }

        void DamageInflictingComponent::SetDamageOutput(const int damageOutput)
        {
            m_DamageOutput = damageOutput;
        }

    }
}
