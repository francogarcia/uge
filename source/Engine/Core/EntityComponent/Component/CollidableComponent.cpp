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

#include "CollidableComponent.h"

namespace uge
{

    namespace Component
    {

        const char* CollidableComponent::g_ComponentName = "CollidableComponent";

        CollidableComponent::CollidableComponent()
            : m_Shape(CollidableComponent::Shape::Count),
              m_Density(""),
              m_Material("")
        {

        }

        CollidableComponent::~CollidableComponent()
        {

        }

        bool CollidableComponent::vInit(XMLElement* pInitXMLData)
        {
            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("Shape");
            if (xmlElement.IsGood())
            {
                if (!vInitShape(&xmlElement))
                {
                    return false;
                }

                xmlElement = pInitXMLData->GetFirstChildElement("CenterOfMassOffset");
                if (xmlElement.IsGood())
                {
                    xmlElement.GetFloatAttribute("x", &m_CenterOfMassOffset.x);
                    xmlElement.GetFloatAttribute("y", &m_CenterOfMassOffset.y);
                    xmlElement.GetFloatAttribute("z", &m_CenterOfMassOffset.z);

                    xmlElement = pInitXMLData->GetFirstChildElement("Density");
                    if (xmlElement.IsGood())
                    {
                        xmlElement.GetAttribute("type", &m_Density);

                        xmlElement = pInitXMLData->GetFirstChildElement("Material");
                        if (xmlElement.IsGood())
                        {
                            xmlElement.GetAttribute("type", &m_Material);

                            return true;
                        }
                    }
                }
            }

            return false;
        }

        void CollidableComponent::vPostInit()
        {

        }

        void CollidableComponent::vUpdate(const unsigned long dt)
        {

        }

        void CollidableComponent::vOnChange()
        {

        }

        const std::string CollidableComponent::vGetName() const
        {
            return g_ComponentName;
        }

        const CollidableComponent::Shape CollidableComponent::GetShape() const
        {
            return m_Shape;
        }

        const CollidableComponent::ShapeData& CollidableComponent::GetShapeData() const
        {
            return m_ShapeData;
        }

        const std::string CollidableComponent::GetDensity() const
        {
            return m_Density;
        }

        const std::string CollidableComponent::GetMaterial() const
        {
            return m_Material;
        }

        bool CollidableComponent::vInitShape(XMLElement* pXMLElement)
        {
            std::string shape;
            pXMLElement->GetAttribute("type", &shape);
            if (shape == "Box")
            {
                m_Shape = CollidableComponent::Shape::Box;

                XMLElement xmlElement = pXMLElement->GetFirstChildElement("Dimension");
                if (xmlElement.IsGood())
                {
                    float fValue;
                    xmlElement.GetFloatAttribute("x", &fValue);
                    m_ShapeData.push_back(fValue);

                    xmlElement.GetFloatAttribute("y", &fValue);
                    m_ShapeData.push_back(fValue);

                    xmlElement.GetFloatAttribute("z", &fValue);
                    m_ShapeData.push_back(fValue);

                    return true;
                }
            }
            else if (shape == "Sphere")
            {
                m_Shape = CollidableComponent::Shape::Sphere;

                XMLElement xmlElement = pXMLElement->GetFirstChildElement("Radius");
                if (xmlElement.IsGood())
                {
                    float fValue;
                    xmlElement.GetFloatAttribute("r", &fValue);
                    m_ShapeData.push_back(fValue);

                    return true;
                }
            }
            else if (shape == "Plane")
            {
                m_Shape = CollidableComponent::Shape::Plane;

                XMLElement xmlElement = pXMLElement->GetFirstChildElement("Normal");
                if (xmlElement.IsGood())
                {
                    float fValue;
                    xmlElement.GetFloatAttribute("x", &fValue);
                    m_ShapeData.push_back(fValue);

                    xmlElement.GetFloatAttribute("y", &fValue);
                    m_ShapeData.push_back(fValue);

                    xmlElement.GetFloatAttribute("z", &fValue);
                    m_ShapeData.push_back(fValue);

                    xmlElement = pXMLElement->GetFirstChildElement("Constant");
                    if (xmlElement.IsGood())
                    {
                        float fValue;
                        xmlElement.GetFloatAttribute("value", &fValue);
                        m_ShapeData.push_back(fValue);

                        return true;
                    }
                }
            }

            // Invalid shape or data.
            return false;
        }
    }

}
