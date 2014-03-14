#include "PongGameStd.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Entity/ActorFactory.h>
#include <Core/EntityComponent/Component/ActorComponent.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Core/Resource/Resource.h>
#include <Core/Resource/ResourceCache.h>
#include <Core/Resource/XMLResource.h>
#include <Core/Resource/ZipFileResource.h>
#include <Core/Script/Lua/ScriptResource.h>

#include <Core/Events/Event.h>
#include <Core/Events/EventManager.h>
#include <Core/Events/DefaultEvents.h>

#include <Core/Task/TaskManager.h>

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/AudioTask.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>

#include <IO/Output/Graphics/Graphics.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include <Engine/GameView/SceneManager.h>
#include <Engine/GameSystem/OutputSystem.h>
#include <Engine/GameSystem/ResourceSystem.h>

#include <Core/Scene/Implementation/Ogre3D/OgreSceneNodeRenderer.h>
#include <Core/Scene/Implementation/Ogre3D/OgreSceneRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneNodeRenderer.h>
#include <Core/Scene/Implementation/OpenALSoft/OpenALSoftSceneRenderer.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/System/Time.h>

#include <Utilities/Math/MathStd.h>
//#include <Utilities/Math/Quaternion.h>
//#include <Utilities/Math/Vector.h>
//#include <Utilities/Math/Matrix.h>

void PrintMatrix(const uge::Matrix4& mat)
{
    std::cout << "[main]" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << mat[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void PrintVector(const uge::Vector3& vec)
{
    std::cout << "[main] (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}

void PrintQuaternion(const uge::Quaternion& quat)
{
    std::cout << "[main] (" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}

void PrintOgreMatrix(const Ogre::Matrix4& mat)
{
    std::cout << "[main]" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << mat[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

void PrintOgreVector(const Ogre::Vector3& vec)
{
    std::cout << "[main] " << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}

void PrintOgreQuaternion(const Ogre::Quaternion& quat)
{
    std::cout << "[main] (" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}


// Going to the engine soon!
class UGEGame
{
public:
    UGEGame()
    {

    }

    ~UGEGame()
    {

    }

    bool Init()
    {
        // EVENT SYSTEM
        m_pEventManager.reset(LIB_NEW uge::EventManager("Global Event Manager", true));

        // GAME VIEW
        uge::IGraphicsSharedPointer pGraphics(LIB_NEW uge::OgreGraphics);
        const int TOTAL_BUFFERS = 4u;
        //uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));
        uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio);
        bSuccess &= m_Output.Init(pGraphics,
                                  pAudio);

        // GAME SCENE
        m_SceneManager.Init();
        InitCamera();

        // RESOURCES
        uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileResource("data/data.zip");
        m_Resources.Init(100, pResourceFile);

        // TODO / FIXME : TEMPORARY CODE
        {
            uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer(m_Output.GetGraphics(), m_Resources.GetResourceCache()));
            pOgreSceneRenderer->Load();

            // TODO: save the renderer ID.
            uge::SceneRendererID sceneRendererID = m_SceneManager.AddSceneRenderer(pOgreSceneRenderer);

            uge::OpenALSoftSceneRendererSharedPointer pOpenALSoftSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer(m_Output.GetAudio(), m_Resources.GetResourceCache()));
            sceneRendererID = m_SceneManager.AddSceneRenderer(pOpenALSoftSceneRenderer);
        }
        // END TEMPORARY CODE

        // GRAPHICS SETUP
        m_Output.GetGraphics()->vSetBackgroundColor(0, 0, 0, 0);

        // GAME LOGIC SETUP
        CreateActors();

        // GAME SCENE
        InitScene();

        return true;
    }

    void Run()
    {
        // MAIN LOOP

        uge::Time::TimePoint startTime = uge::Time::GetTime();

        bool bContinue = true;
        while (bContinue)
        {
            uge::Time::TimePoint currentTime = uge::Time::GetTime();
            unsigned long deltaNanoseconds = uge::Time::GetDeltaAsNanoseconds(currentTime, startTime);
            //pGraphics->vUpdate(deltaNanoseconds);
            startTime = currentTime;

            bContinue = Update(deltaNanoseconds);
            bContinue &= Render(deltaNanoseconds);

            //std::this_thread::sleep_for(std::chrono::milliseconds(50));

            DoStuff();
        }
    }

    bool Destroy()
    {
        bool bSuccess = m_SceneManager.Destroy();
        bSuccess &= m_Output.Destroy();

        m_Resources.Destroy();

        return bSuccess;
    }

    void CreateActors()
    {
        // Sinbad
        m_pActor = m_ActorFactory.CreateActor("data/temp/actors/sinbad.xml", nullptr);
        m_ActorMap.insert(std::make_pair(m_pActor->GetActorID(), m_pActor));

        m_pActor2 = m_ActorFactory.CreateActor("data/temp/actors/sinbad2.xml", nullptr);
        m_ActorMap.insert(std::make_pair(m_pActor2->GetActorID(), m_pActor2));

        m_pActor3 = m_ActorFactory.CreateActor("data/temp/actors/sinbad3.xml", nullptr);
        m_ActorMap.insert(std::make_pair(m_pActor3->GetActorID(), m_pActor3));

        uge::ActorSharedPointer pPlane = m_ActorFactory.CreateActor("data/temp/actors/plane.xml", nullptr);
        m_PlaneID = pPlane->GetActorID();
        m_ActorMap.insert(std::make_pair(m_PlaneID, pPlane));
    }

    void InitScene()
    {
        //m_SceneManager.AddSceneNode(m_pActor);
        //m_SceneManager.AddSceneNode(m_pActor2);
        //m_SceneManager.AddSceneNode(m_pActor3);

        // FIRST ACTOR
        uge::Component::TransformableComponentSharedPointer pActorTransformComponent =
            m_pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        uge::ISceneNodeSharedPointer pActorISceneNode(LIB_NEW uge::SceneNode(m_pActor->GetActorID(),
                                                                             m_pActor,
                                                                             uge::RenderPass::Actor,
                                                                             &pActorTransformComponent->GetTransform(),
                                                                             nullptr));

        // SECOND ACTOR
        uge::Component::TransformableComponentSharedPointer pActor2TransformComponent =
            m_pActor2->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        uge::ISceneNodeSharedPointer pActor2ISceneNode(LIB_NEW uge::SceneNode(m_pActor2->GetActorID(),
                                                                              m_pActor2,
                                                                              uge::RenderPass::Actor,
                                                                              &pActor2TransformComponent->GetTransform(),
                                                                              nullptr));
        //m_pScene->vAddChild(m_pActor2->GetActorID(), pActor2ISceneNode);
        pActorISceneNode->vAddChild(pActor2ISceneNode);

        // THIRD ACTOR
        uge::Component::TransformableComponentSharedPointer pActor3TransformComponent =
            m_pActor3->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        uge::ISceneNodeSharedPointer pActor3ISceneNode(LIB_NEW uge::SceneNode(m_pActor3->GetActorID(),
                                                                              m_pActor3,
                                                                              uge::RenderPass::Actor,
                                                                              &pActor3TransformComponent->GetTransform(),
                                                                              nullptr));
        pActor2ISceneNode->vAddChild(pActor3ISceneNode);

        // Now we add all the nodes to the scene.
        m_SceneManager.AddSceneNode(m_pActor->GetActorID(), pActorISceneNode);

        uge::ActorSharedPointer pPlane = m_ActorMap.find(m_PlaneID)->second;
        uge::Component::TransformableComponentSharedPointer pPlaneTransformComponent =
            pPlane->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        uge::ISceneNodeSharedPointer pPlaneISceneNode(LIB_NEW uge::SceneNode(m_PlaneID,
                                                                             pPlane,
                                                                             uge::RenderPass::Actor,
                                                                             &pPlaneTransformComponent->GetTransform(),
                                                                             nullptr));
        m_SceneManager.AddSceneNode(m_PlaneID, pPlaneISceneNode);
    }

    bool Update(const unsigned long timeElapsed)
    {
        uge::IEventManager::Get()->vUpdate(uge::IEventManager::kINFINITE);

        bool bContinue = m_SceneManager.Update(timeElapsed);
        m_Output.Update(timeElapsed);

        return bContinue;
    }

    bool Render(const unsigned long timeElapsed)
    {
        bool bContinue = m_Output.PreRender();
        bContinue &= m_SceneManager.Render();
        bContinue &= m_Output.PostRender();

        return bContinue;
    }

    void InitCamera()
    {
        uge::Frustum viewFrustum;
        float fAspectRatio = 800.0 / 600.0f;
        viewFrustum.Init(45.0f, fAspectRatio, 5.0f, 100.0f); // fov, aspect ratio, near plane, far plane
        uge::Matrix4 cameraInitialTransform;
        cameraInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, 80.f));

        m_pCamera.reset(LIB_NEW uge::CameraNode(cameraInitialTransform, viewFrustum));
        m_SceneManager.AddCamera(m_pCamera);
    }

    void DoStuff()
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////
        // Debug information                                                                           //
        /////////////////////////////////////////////////////////////////////////////////////////////////

        // Local positions.
        uge::SceneNodeSharedPointer pActorSceneNode = std::dynamic_pointer_cast<uge::SceneNode>(m_SceneManager.GetSceneNode(m_pActor->GetActorID()));
        PrintVector(pActorSceneNode->GetPosition());
        std::cout << std::endl;

        uge::Component::TransformableComponentSharedPointer pActorTransformComponent =
            m_pActor->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
        uge::Vector3 actorPosition = pActorTransformComponent->GetPosition();
        actorPosition.x += 0.05f;
        pActorTransformComponent->SetPosition(actorPosition);

        for (auto& pChildISceneNode : pActorSceneNode->vGetChildren())
        {
            uge::SceneNodeSharedPointer pChildSceneNode = std::dynamic_pointer_cast<uge::SceneNode>(pChildISceneNode);
            PrintVector(pChildSceneNode->GetPosition());

            uge::Component::TransformableComponentSharedPointer pActor2TransformComponent =
                m_pActor2->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            uge::Matrix4 actor2Transform = pActor2TransformComponent->GetTransform();
            actor2Transform.Rotate(uge::Vector3(0.0f, 1.0f, 0.0f), uge::DegreesToRadians(45));
            pActor2TransformComponent->SetTransform(actor2Transform);

            for (auto& pGrandChildISceneNode : pChildSceneNode->vGetChildren())
            {
                uge::SceneNodeSharedPointer pGrandChildSceneNode = std::dynamic_pointer_cast<uge::SceneNode>(pGrandChildISceneNode);
                uge::Vector3 actor3WorldPosition = pGrandChildSceneNode->GetPosition();
                PrintVector(actor3WorldPosition);

                uge::Component::TransformableComponentSharedPointer pActor3TransformComponent =
                    m_pActor3->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
                uge::Matrix4 actor3Transform = pActor3TransformComponent->GetTransform();
                //actor3Transform.Scale(uge::Vector3(1.0f, 0.5f, 1.0f));
                actor3Transform.Translate(uge::Vector3(-0.05f, 0.0f, 0.0f));
                pActor3TransformComponent->SetTransform(actor3Transform);

                //if (actor3WorldPosition.x > 4.5f)
                //{
                //    m_SceneManager.RemoveSceneNode(m_pActor3->GetActorID());

                //    break;
                //}
            }
        }
    }

private:
    // Actors management
    uge::ActorMap m_ActorMap;
    uge::ActorFactory m_ActorFactory;

    // Scene Actors
    uge::ActorSharedPointer m_pActor;
    uge::ActorSharedPointer m_pActor2;
    uge::ActorSharedPointer m_pActor3;
    uge::ActorID m_PlaneID;

    // Game systems.
    uge::OutputSystem m_Output;
    uge::ResourceSystem m_Resources;

    std::unique_ptr<uge::IEventManager> m_pEventManager;

    // Scene
    uge::SceneManager m_SceneManager;
    uge::ICameraNodeSharedPointer m_pCamera;
};

int main()
{
    UGEGame game;
    game.Init();
    game.Run();
    game.Destroy();

    return 0;
}
