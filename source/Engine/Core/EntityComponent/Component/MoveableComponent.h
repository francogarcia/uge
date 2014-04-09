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

#include <Utilities/Math/Vector.h>

namespace uge
{

    namespace Component
    {

        /**
         * @class MoveableComponent
         *  Component used to provide velocity and acceleration information to actors.
         */
        class MoveableComponent : public ActorComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            MoveableComponent();

            /**
             *  Destructor.
             */
            ~MoveableComponent();

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

            const Ogre::Vector3 GetVelocity() const;

            void SetVelocity(const Ogre::Vector3 velocity);

            const float GetCurrentSpeed() const;

            void SetCurrentSpeed(const float fCurrentSpeed);

            const Ogre::Vector3 GetAcceleration() const;

            void SetAcceleration(const Ogre::Vector3 acceleration);

        private:
            /// The velocity of the actor this component is associated to.
            Ogre::Vector3 m_Velocity;
            /// The current velocity value.
            float m_fCurrentVelocity;
            /// The acceleration of the actor this component is associated to.
            Ogre::Vector3 m_Acceleration;
        };

    }

}
