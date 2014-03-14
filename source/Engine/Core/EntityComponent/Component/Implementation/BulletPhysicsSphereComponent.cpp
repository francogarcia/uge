#include "GameEngineStd.h"

#include "BulletPhysicsSphereComponent.h"

namespace uge
{

    namespace Component
    {

        const char* BulletPhysicsSphereComponent::g_ComponentName = "BulletPhysicsSphereComponent";

        BulletPhysicsSphereComponent::BulletPhysicsSphereComponent()
        {

        }

        BulletPhysicsSphereComponent::~BulletPhysicsSphereComponent()
        {

        }

        void BulletPhysicsSphereComponent::vCreateShape()
        {
            m_pPhysics->vAddSphere(m_RigidBodyLocalScale.x, GetOwner(), m_Density, m_Material);
        }

        const std::string BulletPhysicsSphereComponent::vGetName() const
        {
            return g_ComponentName;
        }

    }

}
