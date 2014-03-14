#include "GameEngineStd.h"

#include <stdio.h>

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Entity/ActorFactory.h>
#include <Core/EntityComponent/Component/ActorComponent.h>

#include <Core/EntityComponent/Component/TransformableComponent.h>

/* actor.xml:
    <?xml version="1.0" encoding="UTF-8"?>
    <Actor type="Actor" resource="actor.xml">
      <TransformableComponent>
        <Position x="1.0f" y="2.0f" z="3.0f"/>
        <!-- YXZ order (yaw, pitch, roll), in radians -->
        <Rotation yaw="0.0f" pitch="0.0f" roll="0.0f"/>
        <Scale x="1.0f" y ="1.0f" z="1.0"/>
      </TransformableComponent>

      <MoveableComponent>
        <Velocity vcs="100.0f" vdx="1.0f" vdy="-1.0f" vdz="0.0f"/>
        <Acceleration ax="0.0f" ay="0.0f" az="0.0f"/>
      </MoveableComponent>
    </Actor>
 */

/* actor-override.xml 
     <?xml version="1.0" encoding="UTF-8"?>
    <Actor type="Actor" resource="actor.xml">
      <TransformableComponent>
        <Position x="10.0f" y="20.0f" z="30.0f"/>
        <!-- YXZ order (yaw, pitch, roll), in radians -->
        <Rotation yaw="0.0f" pitch="0.0f" roll="0.0f"/>
        <Scale x="1.0f" y ="1.0f" z="1.0"/>
      </TransformableComponent>

      <CollidableComponent>
        <Shape type="Sphere">
          <Radius r="1.0f"/>
        </Shape>
        <CenterOfMassOffset>
          <Position x="0.0f" y="0.0f" z="0.0f"/>
          <Rotation yaw="0.0f" pitch="0.0f" roll="0.0f"/>        
        </CenterOfMassOffset>
        <Density type="Pine"/>
        <Material type="Elastic"/>
      </CollidableComponent>
    </Actor>
*/

int main()
{
#ifdef _DEBUG
    int debugFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    debugFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
    _CrtSetDbgFlag(debugFlag);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    {
#endif

        // Actors
        uge::ActorMap m_ActorMap;
        uge::ActorFactory m_ActorFactory;

        uge::ActorSharedPointer pActor = m_ActorFactory.CreateActor("actor.xml", nullptr);
        m_ActorMap.insert(std::make_pair(pActor->GetActorID(), pActor));

        uge::Component::TransformableComponentSharedPointer pTransformComponent =
            pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();

        uge::Vector3 position = pTransformComponent->GetPosition();
        printf("Actor's original position: (%f, %f, %f)\n", position.x, position.y, position.z);

        uge::XMLFile actorOverride;
        actorOverride.OpenFile("actor-override.xml", uge::File::FileMode::FileReadOnly);

        m_ActorFactory.ModifyActor(pActor, &actorOverride.GetRootElement());
        position = pTransformComponent->GetPosition();
        printf("Actor's new position: (%f, %f, %f)\n", position.x, position.y, position.z);

        pActor.reset();

        m_ActorMap.clear();

#ifdef _DEBUG
    }
    std::cerr << "Memory Leaks? " << ((_CrtDumpMemoryLeaks() == 1) ? "yes" : "no") << std::endl;

#endif

    return 0;
}
