#include "SpaceshipGameStd.h"

#include "GameEvents.h"

namespace sg
{
    const uge::EventType AlienDestroyed::sk_EventType(0xe91b0343);
    const uge::EventType FireProjectile::sk_EventType(0xd8c91a61);
    const uge::EventType MoveActor::sk_EventType(0x9c4753d0);
    const uge::EventType StopActor::sk_EventType(0xb35753b9);
}