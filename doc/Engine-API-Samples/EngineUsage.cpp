#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>

#include <Engine/GameApplication/BaseGameApplication.h>
#include <Engine/GameLogic/BaseGameLogic.h>
#include <Engine/GameView/GameView.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

// Pong specific headers
#include "Logic/PongGameStateFactory.h"

#define UGE_ENABLE_PHYSICS  1
#define UGE_DEBUG_PHYSICS   1

class UGEGameLogic : public uge::BaseGameLogic
{
public:
    UGEGameLogic()
    {

    }

    ~UGEGameLogic()
    {

    }

    virtual uge::GameStateFactory* vCreateGameStateFactory() override
    {
        return LIB_NEW PongState::PongGameStateFactory;
    }

    virtual uge::IPhysics* vCreatePhysics() override
    {
        // GAME PHYSICS
#ifdef UGE_ENABLE_PHYSICS
        uge::IPhysics* pPhysics = LIB_NEW uge::BulletPhysics;
#else
        uge::IPhysics* pPhysics = LIB_NEW uge::NullPhysics;
#endif

        assert(pPhysics != nullptr);

        bool bSuccess = pPhysics->vInit();
        pPhysics->vSetGravity(uge::Vector3(0.0f, -0.5f, 0.0f));

        return pPhysics;
    }

    void vRegisterGameDelegates() override
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &UGEGameLogic::ActorCollisionStartedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &UGEGameLogic::ActorCollisionEndedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_PhysSeparation::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &UGEGameLogic::ActorCreatedDelegate);
        uge::IEventManager::Get()->vAddListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);
    }

    void vUnregisterGameDelegates() override
    {
        uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &UGEGameLogic::ActorCollisionStartedDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysCollision::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &UGEGameLogic::ActorCollisionEndedDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_PhysSeparation::sk_EventType);

        functionDelegate = fastdelegate::MakeDelegate(this, &UGEGameLogic::ActorCreatedDelegate);
        uge::IEventManager::Get()->vRemoveListener(functionDelegate, uge::EvtData_New_Actor::sk_EventType);
    }

protected:
    void ActorCreatedDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_New_Actor> pData = std::static_pointer_cast<uge::EvtData_New_Actor>(pEventData);

        std::cout << "Actor " << pData->GetActorID() << " was created!" << std::endl;
    }

    void ActorCollisionStartedDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_PhysCollision> pData = std::static_pointer_cast<uge::EvtData_PhysCollision>(pEventData);

        uge::ActorID actorA = pData->GetActorA();
        uge::ActorID actorB = pData->GetActorB();

        std::cout << "Actor " << actorA << " collided with " << actorB << "!" << std::endl;
        if (actorA == 1 || actorB == 1)
        {
            uge::ActorSharedPointer pActor = vGetActor(1).lock();

            uge::Component::BulletPhysicsComponentSharedPointer pActorPhysicsComponent =
                pActor->GetComponent<uge::Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();
            //pActorPhysicsComponent->vStop();
            //pActorPhysicsComponent->vApplyTorque(uge::Vector3(0.0f, 1.0f, 0.0f), 1000.0f);
            pActorPhysicsComponent->vApplyForce(uge::Vector3(-1.0f, 0.0f, 0.0f), 1000.0f);
        }
    }

    void ActorCollisionEndedDelegate(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<uge::EvtData_PhysSeparation> pData = std::static_pointer_cast<uge::EvtData_PhysSeparation>(pEventData);

        uge::ActorID actorA = pData->GetActorA();
        uge::ActorID actorB = pData->GetActorB();

        std::cout << "Actor " << actorA << " is not colliding with " << actorB << " anymore!" << std::endl;
    }

private:

};

class UGEGameView : public uge::HumanGameView
{
public:
    UGEGameView(uge::IGraphicsSharedPointer pGraphics,
                uge::IAudioSharedPointer pAudio,
                uge::ResourceCache& resourceCache)
        : m_pGraphics(pGraphics), m_pAudio(pAudio), m_ResourceCache(resourceCache)
    {

    }

    ~UGEGameView()
    {

    }

    uge::ISceneRendererSharedPointer GetPhysicsDebugRenderer()
    {
        return vGetSceneRenderer(m_GraphicalRendererID);
    }

protected:
    virtual bool vInit() override
    {
        if (!uge::HumanGameView::vInit())
        {
            return false;
        }

        uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer(m_pGraphics, m_ResourceCache));
        pOgreSceneRenderer->Load();

        // TODO: save the renderer ID.
        m_GraphicalRendererID = vAddSceneRenderer(pOgreSceneRenderer);

        uge::OpenALSoftSceneRendererSharedPointer pOpenALSoftSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer(m_pAudio, m_ResourceCache));
        m_AuralRendererID = vAddSceneRenderer(pOpenALSoftSceneRenderer);

        return true;
    }

    virtual void vCreateCamera() override
    {
        uge::Frustum viewFrustum;
        float fAspectRatio = 800.0 / 600.0f;
        viewFrustum.Init(45.0f, fAspectRatio, 5.0f, 10000.0f); // fov, aspect ratio, near plane, far plane
        uge::Matrix4 cameraInitialTransform;
        cameraInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, 200.f));

        m_pCamera.reset(LIB_NEW uge::CameraNode(cameraInitialTransform, viewFrustum));
        m_SceneManager.AddCamera(m_pCamera);
    }

private:
    uge::IGraphicsSharedPointer m_pGraphics;
    uge::IAudioSharedPointer m_pAudio;
    uge::ResourceCache& m_ResourceCache;

    uge::SceneRendererID m_AuralRendererID;
    uge::SceneRendererID m_GraphicalRendererID;
};

class UGEGame : public uge::BaseGameApplication
{
public:
    UGEGame()
    {

    }

    ~UGEGame()
    {

    }

    virtual bool vInit() override
    {
        if (!uge::BaseGameApplication::vInit())
        {
            return false;
        }

        {
            uge::IGameViewSharedPointer pGameView(LIB_NEW UGEGameView(m_Output.GetGraphics(),
                                                                      m_Output.GetAudio(),
                                                                      m_Resources.GetResourceCache()));
            vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
            std::shared_ptr<UGEGameView> pCastGameView = std::dynamic_pointer_cast<UGEGameView>(pGameView);
            m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

            m_Output.PostInit();
        }

        return true;
    }

    virtual uge::BaseGameLogic* vCreateGameLogic() override
    {
        uge::BaseGameLogic* pGameLogic;
        pGameLogic = LIB_NEW UGEGameLogic;

        return pGameLogic;
    }

    virtual std::wstring vGetGameTitle() const override
    {
        return L"UGE Game!";
    }

    virtual bool vInitOutputSystems()
    {
        // Graphics
        uge::IGraphicsSharedPointer pGraphics(LIB_NEW uge::OgreGraphics);

        // Audio
        const int TOTAL_BUFFERS = 4u;
        //uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));
        uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio);

        return m_Output.Init(pGraphics,
                             pAudio);
    }
};

int main()
{
    UGEGame game;
    game.vInit();
    game.vRun();
    game.vDestroy();

    return 0;
}
