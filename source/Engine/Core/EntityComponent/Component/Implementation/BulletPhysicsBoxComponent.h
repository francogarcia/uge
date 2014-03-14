#pragma once

#include "BulletPhysicsComponent.h"

namespace uge
{

    namespace Component
    {

        class BulletPhysicsBoxComponent : public BulletPhysicsComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Construtor.
             */
            BulletPhysicsBoxComponent();

            /**
             *  Destructor.
             */
            virtual ~BulletPhysicsBoxComponent();

            virtual const std::string vGetName() const override;

            virtual void vCreateShape();

        private:

        };

    }

}
