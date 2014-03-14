#pragma once

namespace uge
{

    // Forward declarations.
    class Actor;
    namespace Component
    {
        class ActorComponent;
    }

    /// Declaration of the ActorID type for ease of use.
    typedef unsigned int ActorID;

    /// Declaration of the ComponentID type for ease of use.
    typedef unsigned int ComponentID;

    /// Declaration of a shared pointer of an Actor pointer for ease of use.
    typedef std::shared_ptr<Actor> ActorSharedPointer;

    /// Declaration of a weak pointer of an Actor pointer for ease of use.
    typedef std::weak_ptr<Actor> ActorWeakPointer;

    /// Maps an Actor by its ID to its pointer.
    typedef std::map<ActorID, ActorSharedPointer> ActorMap;
    typedef std::map<ActorID, ActorWeakPointer> WeakActorMap;

    /// Declaration of a shared pointer of an ActorComponent pointer for ease of use.
    typedef std::shared_ptr<Component::ActorComponent> ActorComponentSharedPointer;

    /// Maps an Actor's ID to its ActorComponents.
    typedef std::map<ComponentID, ActorComponentSharedPointer> ActorComponentMap;

}
