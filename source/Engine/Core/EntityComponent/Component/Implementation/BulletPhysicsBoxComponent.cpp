#include "GameEngineStd.h"

#include "BulletPhysicsBoxComponent.h"

namespace uge
{

    namespace Component
    {

        const char* BulletPhysicsBoxComponent::g_ComponentName = "BulletPhysicsBoxComponent";

        BulletPhysicsBoxComponent::BulletPhysicsBoxComponent()
        {

        }

        BulletPhysicsBoxComponent::~BulletPhysicsBoxComponent()
        {

        }

        void BulletPhysicsBoxComponent::vCreateShape()
        {
            m_pPhysics->vAddBox(m_RigidBodyLocalScale, GetOwner(), m_Density, m_Material);
        }

        const std::string BulletPhysicsBoxComponent::vGetName() const
        {
            return g_ComponentName;
        }

    }

}
