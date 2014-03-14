#include <stdio.h>

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Entity/ActorFactory.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Core/Events/Event.h>
#include <Core/Events/EventManager.h>

#include <Core/Physics/IPhysics.h>
#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>

#include <Utilities/System/Clock.h>
#include <Utilities/System/Time.h>

int main(int argc, char* argv[])
{
    // Create the event manager.
    uge::IEventManager* pEventManager = new uge::EventManager("Global Event Manager", true);

    // Create the physics subsystem.
    uge::IPhysicsSharedPointer pPhysics(LIB_NEW uge::BulletPhysics);
    if (!pPhysics->vInit())
    {
        fprintf(stderr, "Error during the Physics subsystem initialization!\n");

        return -1;
    }

    pPhysics->vSetGravity(uge::Vector3(0.0f, -9.8f, 0.0f));

    // Create an actor.
    uge::ActorMap m_ActorMap;
    uge::ActorFactory m_ActorFactory;

    uge::ActorSharedPointer pActor = m_ActorFactory.CreateActor("ball.xml", nullptr);
    m_ActorMap.insert(std::make_pair(pActor->GetActorID(), pActor));

    // Add the actor to the physics simulation.
    pPhysics->vAddActor(pActor);

    // Create a plane.
    uge::ActorSharedPointer pPlane = m_ActorFactory.CreateActor("plane.xml", nullptr);
    m_ActorMap.insert(std::make_pair(pPlane->GetActorID(), pPlane));

    // Add the actor to the physics simulation.
    pPhysics->vAddActor(pPlane);

    // Simulate the game world for kTimeToRun milliseconds.
    const unsigned long kFPS = 1000u / 60u; // In milliseconds.
    const unsigned long kTimeToRun = 1000u * 1000u; // In milliseconds.
    unsigned long timeElapsed = 0u;

    uge::Time::TimePoint lastTime = uge::Time::GetTime();
    while (timeElapsed < kTimeToRun)
    {
        uge::Time::TimePoint currentTime = uge::Time::GetTime();
        unsigned long timeDelta = uge::Time::GetDeltaAsNanoseconds(currentTime, lastTime);

        // Step the simulation.
        pPhysics->vUpdate(timeDelta);
        pPhysics->vSyncVisibleScene();

        pEventManager->vUpdate();

        uge::Component::TransformableComponentSharedPointer pTransformComponent =
            pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        uge::Vector3 position = pTransformComponent->GetPosition();
        printf("Actor's current position: (%f, %f, %f)\n", position.x, position.y, position.z);

        std::this_thread::sleep_for(std::chrono::milliseconds(kFPS));

        lastTime = currentTime;
        timeElapsed += (timeDelta / 1000u);
    }

    // Remove the actor.
    pActor.reset();
    m_ActorMap.clear();

    // Delete the physics subsystem.
    if (!pPhysics->vDestroy())
    {
        fprintf(stderr, "Error during the Physics subsystem de-initialization!\n");

        return -1;
    }
    pPhysics.reset();

    // Delete the event manager.
    SAFE_DELETE(pEventManager);

    return 0;
}
