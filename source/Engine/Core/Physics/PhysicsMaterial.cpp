#include "GameEngineStd.h"

#include "PhysicsMaterial.h"

namespace uge
{
    PhysicsMaterial::PhysicsMaterial(float fRestitution, float fFriction)
        : m_fRestitution(fRestitution), m_fFriction(fFriction)
    {

    }
}
