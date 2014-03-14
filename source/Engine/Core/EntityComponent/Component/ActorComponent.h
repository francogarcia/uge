/**
 * @file ActorComponent.h
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include "../Entity/ActorTypes.h"

#include <Utilities/File/XMLFile.h>

namespace uge
{

    // Forward declaration.
    class ActorFactory;

    namespace Component
    {

        /**
         * @class ActorComponent
         * Base class to implement on components for using as game objects.
         */
        class ActorComponent
        {
        public:
            /// Restricts the creation of new components only by the ActorFactory.
            friend class ActorFactory;

            /**
             *  Destructor.
             */
            virtual ~ActorComponent();

            /**
             *  Instantiates the game object, loading the default data provided for it.
             * This method must be implemented by the subclass.
             * @param pInitXMLData : pointer to a XML element containing the object's load data.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData) = 0;

            /**
             *  Initializes the game object after it was instantiated.
             * This method must be implemented by the subclass.
             */
            virtual void vPostInit() = 0;

            /**
             *  Updates the object.
             * This method must be implemented by the subclass.
             * @param dt : time elapsed since the last update.
             */
            virtual void vUpdate(const unsigned long dt) = 0;

            /**
             *  Callback to be used when the object changes its data or state.
             * This method must be implemented by the subclass.
             */
            virtual void vOnChange() = 0;

            /**
             *  Fetches the ID of the component of the object.
             * This method might be overloaded by a subclass.
             * @return : the unique identifier used by the component.
             */
            virtual const ComponentID vGetID() const;

            /**
             *  Gets the name of the component.
             * This method must be implemented by the subclass.
             * @return : the name of the component, as defined by the subclass.
             */
            virtual const std::string vGetName() const = 0;

        protected:
            /**
             *  Constructor.
             */
            ActorComponent();

            /**
             *  Sets an owner to the component.
             * @param pOwner : pointer to the actor which will own this object.
             */
            void SetOwner(ActorSharedPointer pOwner);

            const ActorSharedPointer GetOwner() const;

        private:
            /// Pointer to the owner of this component object.
            ActorSharedPointer m_pActorOwner;
        };

        /**
         *  Fetches the component ID, searching by its name.
         * @param : the name of the desired component.
         * @return : the ID of the corresponding component.
         */
        const ComponentID GetComponentID(const std::string& componentName);

    }

}
