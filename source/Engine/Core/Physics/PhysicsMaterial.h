#pragma once

namespace uge
{
    struct PhysicsMaterial;
    typedef std::map<std::string, float> DensityTable;
    typedef std::map<std::string, PhysicsMaterial> PhysicsMaterialTable;

    struct PhysicsMaterial
    {
    public:
        PhysicsMaterial(float fRestitution, float fFriction);

    public:
        float m_fRestitution;
        float m_fFriction;
    };
}
