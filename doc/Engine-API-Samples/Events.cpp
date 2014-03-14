#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Entity/ActorFactory.h>
#include <Core/EntityComponent/Entity/ActorTypes.h>
#include <Core/EntityComponent/Component/ActorComponent.h>

#include <Core/Events/Event.h>
#include <Core/Events/EventManager.h>
#include <Core/Events/DefaultEvents.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/System/Clock.h>
#include <Utilities/System/Time.h>

/* LogConfig.xml
    <?xml version="1.0" encoding="UTF-8"?>

    <LogConfig>
        <Log tag="InputWarning"    debugger="1" file="1"/>
        <Log tag="InputError"      debugger="1" file="1"/>
        <Log tag="OutputWarning"   debugger="1" file="1"/>
        <Log tag="OutputError"     debugger="1" file="1"/>
    </LogConfig>
*/

/* actor.xml:
    <?xml version="1.0" encoding="UTF-8"?>
    <?xml version="1.0" encoding="UTF-8"?>
    <Actor type="Actor" resource="actors/actor.xml">
      <TransformableComponent>
        <Position x="-180.0f" y="0.0f" z="0.0f"/>
        <!-- YXZ order (yaw, pitch, roll), in radians -->
        <Rotation yaw="0.0f" pitch="0.0f" roll="0.0f"/>
        <Scale x="4.0f" y ="10.0f" z="20.0"/>
      </TransformableComponent>

      <MoveableComponent>
        <Velocity vcs="100.0f" vdx="1.0f" vdy="-1.0f" vdz="0.0f"/>
        <Acceleration ax="0.0f" ay="0.0f" az="0.0f"/>
      </MoveableComponent>
    </Actor>
*/

class RoleSystem
{
public:
    RoleSystem()
    {

    }

    ~RoleSystem()
    {
        Destroy();
    }

    void Init()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &RoleSystem::NewActorDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &RoleSystem::DestroyActorDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_Destroy_Actor::sk_EventType);
    }

    void Destroy()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &RoleSystem::NewActorDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &RoleSystem::DestroyActorDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_Destroy_Actor::sk_EventType);
    }

    void NewActorDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_New_Actor> pData = std::static_pointer_cast<uge::EvtData_New_Actor>(pEventData);

        uge::ActorID id = pData->GetActorID();
        unsigned int roleSelection = id % 3;
        switch (roleSelection)
        {
            case 0:
                m_Roles[id] = "Knight";
                break;

            case 1:
                m_Roles[id] = "Mage";
                break;

            case 2:
                m_Roles[id] = "Archer";
                break;
        }

        std::cout << "Assigned the role: " << m_Roles[id] << " to the actor with ID: " << id << std::endl;
    }

    void DestroyActorDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_Destroy_Actor> pData = std::static_pointer_cast<uge::EvtData_Destroy_Actor>(pEventData);

        uge::ActorID id = pData->GetActorID();
        std::cout << "Removing the actor with ID: " << id << ", role: " << m_Roles[id] << std::endl;
        m_Roles.erase(id);
    }

private:
    std::map<uge::ActorID, std::string> m_Roles;
};

class HealthSystem
{
public:
    HealthSystem()
    {

    }

    ~HealthSystem()
    {
        Destroy();
    }

    void Init()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &HealthSystem::NewActorDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &HealthSystem::DestroyActorDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_Destroy_Actor::sk_EventType);
    }

    void Destroy()
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &HealthSystem::NewActorDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &HealthSystem::DestroyActorDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_Destroy_Actor::sk_EventType);
    }

    void NewActorDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_New_Actor> pData = std::static_pointer_cast<uge::EvtData_New_Actor>(pEventData);

        uge::ActorID id = pData->GetActorID();
        unsigned int hp = id % 10;
        m_HPs[id] = hp;
        std::cout << "Actor with ID: " << id << ", HP: " << m_HPs[id]  << std::endl;

        if (hp < 3)
        {
            std::shared_ptr<uge::EvtData_Destroy_Actor> pDestroyActorEvent(LIB_NEW uge::EvtData_Destroy_Actor(id));
            uge::IEventManager::Get()->vTriggerEvent(pDestroyActorEvent);
        }
    }

    void DestroyActorDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_Destroy_Actor> pData = std::static_pointer_cast<uge::EvtData_Destroy_Actor>(pEventData);

        uge::ActorID id = pData->GetActorID();
        std::cout << "Removing the actor with ID: " << id << std::endl;
        m_HPs.erase(id);
    }

private:
    std::map<uge::ActorID, unsigned int> m_HPs;
};

int main(int argc, char* argv[])
{
    uge::debug::log::Init("LogConfig.xml");

    uge::IEventManager* pEventManager = new uge::EventManager("Global Event Manager", true);

    RoleSystem roleSystem;
    roleSystem.Init();

    HealthSystem hpSystem;
    hpSystem.Init();

    uge::ActorMap m_ActorMap;
    uge::ActorFactory m_ActorFactory;

    const unsigned int actorsToSpawnPerUpdate = 10;
    srand(time(NULL));

    uge::Time::TimePoint startTime = uge::Time::GetTime();
    for (int i = 0; i < actorsToSpawnPerUpdate; ++i)
    {
        uge::ActorSharedPointer pActor = m_ActorFactory.CreateActor("actor.xml", nullptr);
        m_ActorMap.insert(std::make_pair(pActor->GetActorID(), pActor));
        std::shared_ptr<uge::EvtData_New_Actor> pNewActorEvent(LIB_NEW uge::EvtData_New_Actor(pActor->GetActorID()));
        uge::IEventManager::Get()->vQueueEvent(pNewActorEvent); // Event will be triggered during the vUpdate() call.
    }
    std::cout << "First update..." << std::endl << std::endl;
    uge::Time::TimePoint finalTime = uge::Time::GetTime();
    uge::IEventManager::Get()->vUpdate(uge::Time::GetDeltaAsMilliseconds(finalTime, startTime));

    startTime = uge::Time::GetTime();
    std::cout << std::endl << "After the first update..." << std::endl << std::endl;
    uge::ActorID unluckyActor = rand() % actorsToSpawnPerUpdate + 1;
    std::shared_ptr<uge::EvtData_Destroy_Actor> pDestroyActorEvent(LIB_NEW uge::EvtData_Destroy_Actor(unluckyActor));
    uge::IEventManager::Get()->vTriggerEvent(pDestroyActorEvent); // Event will be triggered now, before the vUpdate() call.

    for (int i = 0; i <  actorsToSpawnPerUpdate; ++i)
    {
        uge::ActorSharedPointer pActor = m_ActorFactory.CreateActor("actor.xml", nullptr);
        m_ActorMap.insert(std::make_pair(pActor->GetActorID(), pActor));
        std::shared_ptr<uge::EvtData_New_Actor> pNewActorEvent(LIB_NEW uge::EvtData_New_Actor(pActor->GetActorID()));
        uge::IEventManager::Get()->vQueueEvent(pNewActorEvent); // Event will be triggered during the vUpdate() call.
    }
    std::cout << std::endl << "Second update..." << std::endl << std::endl;
    finalTime = uge::Time::GetTime();
    uge::IEventManager::Get()->vUpdate(uge::Time::GetDeltaAsMilliseconds(finalTime, startTime));

    m_ActorMap.clear();

    uge::debug::log::Destroy();

    return 0;
}
