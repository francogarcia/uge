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

        class DamageSoakingComponent;
        typedef std::shared_ptr<DamageSoakingComponent> DamageSoakingComponentSharedPointer;
        typedef std::weak_ptr<DamageSoakingComponent> DamageSoakingComponentWeakPointer;

        /**
         * @class DamageSoakingComponent
         *  Component used to reduce the damage taken by the actor.
         */
        class DamageSoakingComponent : public uge::Component::ActorComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Constructor.
             */
            DamageSoakingComponent();

            /**
             *  Destructor.
             */
            ~DamageSoakingComponent();

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

            int GetCurrentProtection() const;
            void SetCurrentProtection(const int value);

            void IncrementProtection(const int value);
            void DecrementProtection(const int value);

            int GetMaximumProtection() const;
            void SetMaximumProtection(const int value);

        private:
            /// The current protection provided by the component.
            int m_CurrentProtection;

            /// The maximum protection provided by the component.
            int m_MaxProtection;
        };

    }

}
