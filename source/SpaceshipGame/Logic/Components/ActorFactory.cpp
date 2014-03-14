#include "SpaceshipGameStd.h"

#include "ActorFactory.h"

#include "DamageInflictingComponent.h"
#include "DamageSoakingComponent.h"
#include "HealthComponent.h"

namespace sg
{

    ActorFactory::ActorFactory() : uge::ActorFactory()
    {
        RegisterComponents();
    }

    ActorFactory::~ActorFactory()
    {

    }

    void ActorFactory::RegisterComponents()
    {
        m_ComponentFactory.Register<Component::DamageInflictingComponent>(uge::Component::GetComponentID(Component::DamageInflictingComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::DamageSoakingComponent>(uge::Component::GetComponentID(Component::DamageSoakingComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::HealthComponent>(uge::Component::GetComponentID(Component::HealthComponent::g_ComponentName));
    }

}
