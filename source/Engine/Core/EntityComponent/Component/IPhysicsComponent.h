#pragma once

#include <Utilities/Math/MathStd.h>

#include "ActorComponent.h"

namespace uge
{

    namespace Component
    {

        class IPhysicsComponent : public ActorComponent
        {
        public:
            /**
             *  Constructor.
             */
            IPhysicsComponent() { }

            /**
             *  Destructor.
             */
            virtual ~IPhysicsComponent() { }

            /**
             *  Instantiates the game object and loads the default data.
             * @param pInitXMLData : pointer to a XML element containing the object's initial position.
             * @return : true if the if initialization was successful; false otherwise.
             */
            virtual bool vInit(XMLElement* pInitXMLData) = 0;

            /**
             *  Initializes the game object after it was instantiated.
             */
            virtual void vPostInit() = 0;

            /**
             *  Updates the object.
             */
            virtual void vUpdate(const unsigned long dt) = 0;

            /**
             *  Callback to be used when the object changes its data or state.
             */
            virtual void vOnChange() = 0;

            /**
             *  Gets the name of the component.
             * @return : the name of the component;
             */
            virtual const std::string vGetName() const = 0;

        private:
        };

    }

}
