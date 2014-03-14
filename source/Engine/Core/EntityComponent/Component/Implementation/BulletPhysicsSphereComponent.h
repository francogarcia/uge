#pragma once

#include "GameEngineStd.h"

#include "BulletPhysicsComponent.h"

namespace uge
{

    namespace Component
    {

        class BulletPhysicsSphereComponent : public BulletPhysicsComponent
        {
        public:
            /// The name of the component.
            static const char* g_ComponentName;

            /**
             *  Construtor.
             */
            BulletPhysicsSphereComponent();

            /**
             *  Destructor.
             */
            virtual ~BulletPhysicsSphereComponent();

            virtual const std::string vGetName() const override;

            virtual void vCreateShape();

        private:

        };

    }

}
