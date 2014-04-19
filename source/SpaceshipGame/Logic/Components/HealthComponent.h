/*
 * (c) Copyright 2014 Franco Eusébio Garcia
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

#include <Core/EntityComponent/Component/ActorComponent.h>

namespace sg
{
    namespace Component
    {

        class HealthComponent;
        typedef std::shared_ptr<HealthComponent> HealthComponentSharedPointer;

        /**
         * @class HealthComponent
         *  Component used to provide health points to actors.
         */
        class HealthComponent : public uge::Component::ActorComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            HealthComponent();

            /**
             *  Destructor.
             */
            ~HealthComponent();

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            bool vInit(uge::XMLElement* pInitXMLData) override;

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

            int GetHealthPoints() const;
            void SetHealthPoints(const int healthPoints);

            void IncrementHealthPoints(const int value);
            void DecrementHealthPoints(const int value);

            int SetMaximumHealthPoints() const;
            void SetMaximumHealthPoints(const int healthPoints);

        private:
            /// The health points of the entity.
            int m_HealthPoints;

            /// The max health points the entity can have.
            int m_MaxHealthPoints;
        };

    }

}
