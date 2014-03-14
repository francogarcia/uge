#pragma once

#include <Utilities/Math/MathStd.h>

#include "ActorComponent.h"

namespace uge
{

    namespace Component
    {

        class CollidableComponent;
        typedef std::shared_ptr<CollidableComponent> CollidableComponentSharedPointer;

        class CollidableComponent : public ActorComponent
        {
        public:
            typedef std::vector<float> ShapeData;

            enum class Shape : unsigned char
            {
                Box,
                Sphere,
                Plane,

                Count
            };

            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            CollidableComponent();

            /**
             *  Destructor.
             */
            virtual ~CollidableComponent();

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData) override;

            /**
             *  Initializes the game object after it was instantiated.
             */
            virtual void vPostInit() override;

            /**
             *  Updates the object.
             */
            virtual void vUpdate(const unsigned long dt) override;

            /**
             *  Callback to be used when the object changes its data or state.
             */
            virtual void vOnChange() override;

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            virtual const std::string vGetName() const override;

            virtual const CollidableComponent::Shape GetShape() const;
            virtual const CollidableComponent::ShapeData& GetShapeData() const;
            virtual const std::string GetDensity() const;
            virtual const std::string GetMaterial() const;

        protected:
            virtual bool vInitShape(XMLElement* pXMLElement);

        private:
            CollidableComponent::Shape m_Shape;
            std::string m_Density;
            std::string m_Material;

            // Box: Length, height, depth if box.
            // Sphere: radius.
            // Plane: constant.
            CollidableComponent::ShapeData m_ShapeData;
            
            Vector3 m_CenterOfMassOffset;
        };

    }

}
