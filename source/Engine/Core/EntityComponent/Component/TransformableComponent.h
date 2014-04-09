/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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
  */

#pragma once

#include "ActorComponent.h"

#include <Utilities/Math/Quaternion.h>
#include <Utilities/Math/Matrix.h>
#include <Utilities/Math/Vector.h>

namespace uge
{

    namespace Component
    {

        class TransformableComponent;
        typedef std::shared_ptr<TransformableComponent> TransformableComponentSharedPointer;

        /**
         * @class TransformableComponent
         *  Component used to provide spatial position information to actors.
         */
        class TransformableComponent : public ActorComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            TransformableComponent();

            /**
             *  Destructor.
             */
            ~TransformableComponent();

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            bool vInit(XMLElement* pInitXMLData) override;

            /**
             *  Initializes the game object after it was instantiated.
             */
            void vPostInit() override;

            /**
             *  Updates the object.
             */
            void vUpdate(const unsigned long dt) override;

            /**
             *  Callback to be used when the object changes its data or state.
             */
            void vOnChange() override;

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            const std::string vGetName() const override;

            const Vector3 GetPosition() const;
            void SetPosition(const Vector3& position);

            const Quaternion GetRotation() const;
            const Vector3 GetRotationVector() const;
            void SetRotation(const Quaternion& rotation);

            const Vector3 GetScale() const;
            void SetScale(const Vector3& scale);

            const Matrix4& GetTransform() const;
            void SetTransform(const Matrix4& transform);

        private:
            /// The position, rotation and translation of the actor this component is associated to.
            Matrix4 m_Transform;
        };

    }

}
