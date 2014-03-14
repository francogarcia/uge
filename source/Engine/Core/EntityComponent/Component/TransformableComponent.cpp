#include "GameEngineStd.h"

#include "TransformableComponent.h"

namespace uge
{

    namespace Component
    {

        const char* TransformableComponent::g_ComponentName = "TransformableComponent";

        TransformableComponent::TransformableComponent()
            : m_Transform(Matrix4::g_Identity)
        {

        }

        TransformableComponent::~TransformableComponent()
        {

        }

        bool TransformableComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            Vector3 position(0.0f, 0.0f, 0.0f);
            Quaternion rotation(0.0f, 0.0f, 0.0f, 0.0f);
            Vector3 scale(0.0f, 0.0f, 0.0f);

            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("Position");
            if (xmlElement.IsGood())
            {
                xmlElement.GetFloatAttribute("x", &position.x);
                xmlElement.GetFloatAttribute("y", &position.y);
                xmlElement.GetFloatAttribute("z", &position.z);

                xmlElement = pInitXMLData->GetFirstChildElement("Scale");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetFloatAttribute("x", &scale.x);
                    xmlElement.GetFloatAttribute("y", &scale.y);
                    xmlElement.GetFloatAttribute("z", &scale.z);

                    xmlElement = pInitXMLData->GetFirstChildElement("Rotation");
                    if (xmlElement.IsGood())
                    {
                        Vector3 rotationVector;
                        // YXZ order (yaw, pitch, roll).
                        xmlElement.GetFloatAttribute("yaw", &rotationVector.y);
                        xmlElement.GetFloatAttribute("pitch", &rotationVector.x);
                        xmlElement.GetFloatAttribute("roll", &rotationVector.z);

                        rotation.MakeQuaternion(rotationVector);

                        m_Transform.MakeTransform(position, scale, rotation);

                        return true;
                    }
                    else
                    {
                        xmlElement = pInitXMLData->GetFirstChildElement("RotationQuaternion");
                        if (xmlElement.IsGood())
                        {
                            xmlElement.GetFloatAttribute("x", &rotation.x);
                            xmlElement.GetFloatAttribute("y", &rotation.y);
                            xmlElement.GetFloatAttribute("z", &rotation.z);
                            xmlElement.GetFloatAttribute("w", &rotation.w);

                            m_Transform.MakeTransform(position, scale, rotation);

                            return true;
                        }
                    }
                }
            }

            return false;
        }

        void TransformableComponent::vPostInit()
        {

        }

        void TransformableComponent::vUpdate(const unsigned long dt)
        {

        }

        void TransformableComponent::vOnChange()
        {

        }

        const std::string TransformableComponent::vGetName() const
        {
            return g_ComponentName;
        }

        const Vector3 TransformableComponent::GetPosition() const
        {
            return m_Transform.GetPositionVector();
        }

        void TransformableComponent::SetPosition(const Vector3& position)
        {
            m_Transform.SetPositionFromVector(position);
        }

        const Quaternion TransformableComponent::GetRotation() const
        {
            return m_Transform.GetRotationQuaternion();
        }

        const Vector3 TransformableComponent::GetRotationVector() const
        {
            return m_Transform.GetRotationVector();
        }

        void TransformableComponent::SetRotation(const Quaternion& rotation)
        {
            Vector3 position = m_Transform.GetPositionVector();
            Vector3 scale = m_Transform.GetScaleVector();
            m_Transform.MakeTransform(position, scale, rotation);
        }

        const Vector3 TransformableComponent::GetScale() const
        {
            return m_Transform.GetScaleVector();
        }

        void TransformableComponent::SetScale(const Vector3& scale)
        {
            m_Transform.SetScaleFromVector(scale);
        }

        const Matrix4& TransformableComponent::GetTransform() const
        {
            return m_Transform;
        }

        void TransformableComponent::SetTransform(const Matrix4& transform)
        {
            m_Transform = transform;
        }
    }

}
