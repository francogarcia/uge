/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser GPL v3
  * as published by the Free Software Foundation.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
  * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
  *
  * You should have received a copy of the GNU Lesser GPL v3
  * along with this program; if not, write to the Free Software
  */

#include "PongGameStd.h"

// #include <vld.h>

//#include <Core/EntityComponent/Entity/Actor.h>
//#include <Core/EntityComponent/Entity/ActorFactory.h>
//#include <Core/EntityComponent/Component/ActorComponent.h>
//#include <Core/EntityComponent/Component/TransformableComponent.h>
//#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>
//
//#include <Core/Resource/Resource.h>
//#include <Core/Resource/ResourceCache.h>
//#include <Core/Resource/XMLResource.h>
//#include <Core/Resource/ZipFileResource.h>
//#include <Core/Script/Lua/ScriptResource.h>
//
//#include <Core/Events/Event.h>
//#include <Core/Events/EventManager.h>
//#include <Core/Events/DefaultEvents.h>
//
//#include <Core/Physics/IPhysics.h>
//#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
//#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>
//
//#include <Core/Task/TaskManager.h>
//
//#include <IO/Output/Audio/Audio.h>
//#include <IO/Output/Audio/AudioTask.h>
//
//#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
//#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>
//
//#include <IO/Output/Graphics/Graphics.h>
//#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>
//
//#include <Engine/GameSystem/OutputSystem.h>
//#include <Engine/GameSystem/ResourceSystem.h>
//
//#include <Engine/GameView/SceneManager.h>
//
//#include <Utilities/Debug/Logger.h>
//#include <Utilities/System/Time.h>
//
//#include <Utilities/Math/MathStd.h>
//
//#include <Utilities/Math/Debug/MathPrint.h>

#define UGE_ENABLE_PHYSICS  1
#define UGE_DEBUG_PHYSICS   1

// Pong specific headers
#include "Application/PongApplication.h"

#include <Utilities/Debug/Logger.h>

int main()
{
    uge::debug::log::Init("data/debug/LogConfig.xml");
    //LOG_INFO("Game started.");

    PongApplication game;
    game.vInit();
    game.vRun();
    game.vDestroy();

    //LOG_INFO("Game finished.");
    uge::debug::log::Destroy();

    return 0;
}

//int main()
//{
//    // GAME SCENE
//
//    uge::IScene* pScene = LIB_NEW uge::Scene();
//
//    // GRAPHICAL RENDERER
//
//    uge::IGraphicsSharedPointer pGraphics(LIB_NEW uge::OgreGraphics);
//    pGraphics->vInit();
//
//    uge::OgreSceneRendererSharedPointer pOgreSceneRenderer(LIB_NEW uge::OgreSceneRenderer(pGraphics));
//    uge::ISceneRendererSharedPointer pSceneRenderer(pOgreSceneRenderer);
//    pScene->vAddSceneRendererer(pSceneRenderer);
//
//    // GAME CAMERA
//
//    uge::Frustum viewFrustum;
//    float fAspectRatio = 800.0 / 600.0f;
//    viewFrustum.Init(45.0f, fAspectRatio, 5.0f, 100.0f); // fov, aspect ratio, near plane, far plane
//    uge::Matrix4 cameraInitialTransform;
//    cameraInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, 80.f));
//
//    uge::CameraNodeSharedPointer pCamera(LIB_NEW uge::OgreCameraNode(pOgreSceneRenderer->GetOgreSceneManager(), cameraInitialTransform, viewFrustum));
//    pCamera->vInit(pScene);
//    pScene->vSetCamera(pCamera);
//
//    // GRAPHICS SETUP
//
//    pGraphics->vSetBackgroundColor(0, 0, 0, 0);
//
//    // SCENE SETUP (1)
//
//    pOgreSceneRenderer->Load();
//    //pScene->Run();
//
//    // GAME LOGIC SETUP
//
//    uge::ActorMap actorMap;
//    uge::ActorFactory actorFactory;
//
//    uge::ActorSharedPointer pActor = actorFactory.CreateActor("data/temp/actors/sinbad.xml", nullptr);
//    actorMap.insert(std::make_pair(pActor->GetActorID(), pActor));
//
//    uge::ActorSharedPointer pChildActor = actorFactory.CreateActor("data/temp/actors/sinbad2.xml", nullptr);
//    actorMap.insert(std::make_pair(pChildActor->GetActorID(), pChildActor));
//
//    // SCENE SETUP (2)
//    uge::Matrix4 actorInitialTransform;
//    actorInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, 0.0f));
//
//    uge::ISceneNodeSharedPointer pActorISceneNode(LIB_NEW uge::OgreSceneNode(pActor->GetActorID(),
//            pActor->GetComponent<uge::Component::OgreGraphicalComponent>(uge::Component::OgreGraphicalComponent::g_ComponentName),
//            uge::RenderPass::Actor,
//            &actorInitialTransform,
//            nullptr));
//    pScene->vAddChild(pActor->GetActorID(), pActorISceneNode);
//
//    uge::Matrix4 childActorInitialTransform;
//    //childActorInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, -20.0f));
//    childActorInitialTransform.MakeTranslationMatrix(uge::Vector3(0.0f, 0.0f, 0.0f));
//
//    uge::ISceneNodeSharedPointer pChildActorISceneNode(LIB_NEW uge::OgreSceneNode(pChildActor->GetActorID(),
//            pChildActor->GetComponent<uge::Component::OgreGraphicalComponent>(uge::Component::OgreGraphicalComponent::g_ComponentName),
//            uge::RenderPass::Actor,
//            &childActorInitialTransform,
//            nullptr));
//
//    // Move together.
//    pScene->vAddChild(pChildActor->GetActorID(), pChildActorISceneNode);
//    //pActorISceneNode->vAddChild(pChildActorISceneNode);
//    // Don't move.
//    //pActorISceneNode->vRemoveChild(pChildActor->GetActorID());
//    //pScene->vAddChild(pChildActor->GetActorID(), pChildActorISceneNode);
//
//    // Audio
//    const int TOTAL_BUFFERS = 4u;
//    uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));
//    pAudio->vInit();
//
//    uge::OpenALSoftSceneRendererSharedPointer pOALSceneRenderer(LIB_NEW uge::OpenALSoftSceneRenderer(pAudio));
//    uge::ISceneRendererSharedPointer pAudioSceneRenderer(pOALSceneRenderer);
//    pScene->vAddSceneRendererer(pAudioSceneRenderer);
//
//    uge::ActorSharedPointer pSoundActor = actorFactory.CreateActor("data/temp/actors/sound.xml", nullptr);
//    actorMap.insert(std::make_pair(pSoundActor->GetActorID(), pSoundActor));
//
//    uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileResource("data/data.zip");
//    uge::ResourceCache resourceCache(100, pResourceFile);
//    if (!resourceCache.Init())
//    {
//        std::cerr << "Error creating the resource cache!" << std::endl;
//        std::exit(EXIT_FAILURE);
//    }
//
//    // XML loader.
//    uge::IResourceLoaderSharedPointer pCreateXMLLoader = uge::XMLResourceLoader::CreateLoader();
//    resourceCache.RegisterLoader(pCreateXMLLoader);
//    // Lua loader.
//    uge::IResourceLoaderSharedPointer pCreateLuaScriptLoader = uge::LuaScriptResourceLoader::CreateLoader();
//    resourceCache.RegisterLoader(pCreateLuaScriptLoader);
//    // OGG loader.
//    resourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftOggResourceLoader));
//    // WAVE loader.
//    resourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftWaveResourceLoader));
//
//    // Load a sound resource.
//    uge::Component::OpenALSoftAudioComponentSharedPointer pAudioComponent = pSoundActor->GetComponent<uge::Component::OpenALSoftAudioComponent>(uge::Component::OpenALSoftAudioComponent::g_ComponentName).lock();
//
//    uge::Resource oggAudioResourceFile(pAudioComponent->GetFileName());
//    uge::ResourceHandleSharedPointer pOggAudioResource = resourceCache.GetHandle(&oggAudioResourceFile);
//    uge::IAudioBuffer* pAudioBuffer = pAudio->vInitAudioBuffer(pOggAudioResource);
//    //pAudioBuffer->vPlay(pAudioComponent->GetVolume(), pAudioComponent->GetLooping());
//
//    uge::Matrix4 audioInitialTransform;
//    audioInitialTransform.MakeTranslationMatrix(uge::Vector3(5.0f, 0.0f, 0.0f));
//
//    uge::ISceneNodeSharedPointer pAudioISceneNode(LIB_NEW uge::OpenALSoftSceneNode(pAudioBuffer, pSoundActor->GetActorID(),
//            pAudioComponent,
//            uge::RenderPass::Actor,
//            &audioInitialTransform,
//            nullptr));
//    //pScene->vAddChild(pSoundActor->GetActorID(), pIAudioSceneNode);
//    pActorISceneNode->vAddChild(pAudioISceneNode);
//
//    // MAIN LOOP
//    uge::SceneNodeSharedPointer pActorSceneNode = std::dynamic_pointer_cast<uge::SceneNode>(pActorISceneNode);
//    uge::SceneNodeSharedPointer pChildActorSceneNode = std::dynamic_pointer_cast<uge::SceneNode>(pChildActorISceneNode);
//    uge::SceneNodeSharedPointer pAudioSceneNode = std::dynamic_pointer_cast<uge::SceneNode>(pAudioISceneNode);
//
//    uge::Time::TimePoint startTime = uge::Time::GetTime();
//
//    // Walk in circles.
//    float fAngle = 0.0f;
//    float fAngleStep = uge::DegreesToRadians(15.0);
//
//    float fRadius = 20.0f;
//    float fCenterX = 0.0f;
//    float fCenterY = 0.0f;
//    float fCenterZ = 0.0f;
//
//    float fPositionX = 0.0f;
//    float fPositionY = 0.0f;
//    float fPositionZ = 0.0f;
//
//    bool bRender = true;
//    while (bRender)
//    {
//        uge::Time::TimePoint currentTime = uge::Time::GetTime();
//        unsigned long deltaNanoseconds = uge::Time::GetDeltaAsNanoseconds(currentTime, startTime);
//        pAudio->vUpdate(deltaNanoseconds);
//        //pGraphics->vUpdate(deltaNanoseconds);
//        startTime = currentTime;
//
//        // Local positions.
//        uge::Vector3 actorPosition(pActorSceneNode->GetPosition());
//        PrintVector(actorPosition);
//        PrintVector(pChildActorSceneNode->GetPosition());
//        PrintVector(pAudioSceneNode->GetPosition());
//        std::cout << std::endl;
//
//        fPositionX = fCenterX + fRadius * uge::Cos(fAngle);
//        fPositionZ = fCenterZ + fRadius * uge::Sin(fAngle);
//        fAngle += fAngleStep;
//
//        actorPosition.x = fPositionX;
//        actorPosition.y = fPositionY;
//        actorPosition.z = fPositionZ;
//        pActorSceneNode->vSetPosition(actorPosition);
//        PrintVector(pActorSceneNode->GetWorldPosition());
//        PrintVector(pChildActorSceneNode->GetWorldPosition());
//        PrintVector(pAudioSceneNode->GetWorldPosition());
//        std::cout << std::endl;
//        std::cout << std::endl;
//
//        bRender = pGraphics->vPreRender();
//
//        pScene->vOnUpdate(0);
//        bRender &= pScene->vOnRender();
//
//        pGraphics->vPostRender();
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(50));
//    }
//
//    pGraphics->vDestroy();
//    pAudio->vDestroy();
//
//    return 0;
//}


//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>    /* for sqrtf() */
//#include <time.h>    /* for time(), to seed srand() */
//
///* OpenAL headers */
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alext.h>
//
///* load a file into memory, returning the buffer and
// * setting bufsize to the size-in-bytes */
//void* load(char* fname, long* bufsize)
//{
//    FILE* fp = fopen(fname, "rb");
//    fseek(fp, 0L, SEEK_END);
//    long len = ftell(fp);
//    rewind(fp);
//    void* buf = malloc(len);
//    fread(buf, 1, len, fp);
//    fclose(fp);
//    *bufsize = len;
//    return buf;
//}
//
///* randomly displace 'a' by one meter +/- in x or z */
//void randWalk(float* a)
//{
//    int r = rand() & 0x3;
//    switch (r)
//    {
//        case 0:
//            a[0] -= 1.;
//            break;
//        case 1:
//            a[0] += 1.;
//            break;
//        case 2:
//            a[2] -= 1.;
//            break;
//        case 3:
//            a[2] += 1.;
//            break;
//    }
//    printf("Walking to: %.1f,%.1f,%.1f\n", a[0], a[1], a[2]);
//}
//
//void circleWalk(float centerX, float centerZ, float radius,
//                float angle, float& positionX, float& positionZ)
//{
//    positionX = centerX + radius * std::cos(angle);
//    positionZ = centerZ + radius * std::sin(angle);
//}
//
//int main(int argc, char* argv[])
//{
//    /* Start just 1m to the right. */
//    float position[3] = {1.0f, 0.0f, 0.0f};
//
//    /* initialize OpenAL context, asking for 44.1kHz to match HRIR data */
//    ALCint contextAttr[] = {ALC_FREQUENCY, 44100, 0};
//    ALCdevice* device = alcOpenDevice(NULL);
//    ALCcontext* context = alcCreateContext(device, contextAttr);
//    alcMakeContextCurrent(context);
//
//    /* listener at origin, facing z (ears at 0m height) */
//    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
//    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
//    float orient[6] = {/*fwd:*/ 0.0f, 0.0f, 1.0f, /*up:*/ 0.0f, 1.0f, 0.0f};
//    alListenerfv(AL_ORIENTATION, orient);
//
//    /* this will be the source of ghostly footsteps... */
//    ALuint source;
//    alGenSources(1, &source);
//    alSourcef(source, AL_PITCH, 1.0f);
//    alSourcef(source, AL_GAIN, 1.0f);
//    alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
//    alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
//    alSourcei(source, AL_LOOPING, AL_TRUE);
//
//    /* allocate an OpenAL buffer and fill it with monaural sample data */
//    ALuint buffer;
//    alGenBuffers(1, &buffer);
//    {
//        long dataSize;
//        const ALvoid* data = load("data/audio/effects/drone.ogg", &dataSize);
//        /* for simplicity, assume raw file is signed-16b at 44.1kHz */
//        alBufferData(buffer, AL_FORMAT_MONO16, data, dataSize, 44100);
//        free((void*)data);
//    }
//    alSourcei(source, AL_BUFFER, buffer);
//
//    /* state initializations for the upcoming loop */
//    srand((int)time(NULL));
//    const float dt = 1.0f / 1.0f; // 2 frames per second.
//    const float vel = 0.2f;
//    const float pi = 3.141592f;
//    const float radius = 10.0f;
//
//    /** BEGIN! **/
//    alSourcePlay(source);
//
//    fflush(stderr);   /* in case OpenAL reported an error earlier */
//
//    /* loop forever... walking to random, adjacent, integer coordinates */
//    float angle = 0.0f;
//    for (;;)
//    {
//        // Move in circles.
//        circleWalk(0.0f, 0.0f, radius, angle, position[0], position[2]);
//        alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
//
//        angle += (vel);
//        if (angle > 2 * pi)
//        {
//            angle = angle - 2 * pi;
//        }
//
//        printf("(%f, %f, %f)\n", position[0], position[1], position[2]);
//        printf("dist = %f\n\n", std::sqrtf(std::pow(position[0], 2) + std::pow(position[0], 2)));
//
//        Sleep(dt * 1000);
//    }
//
//    /* cleanup that should be done when you have a proper exit... ;) */
//    alDeleteSources(1, &source);
//    alDeleteBuffers(1, &buffer);
//    alcDestroyContext(context);
//    alcCloseDevice(device);
//
//    return 0;
//}


//int main(int argc, char* argv[])
//{
//    TinyOAL::cAudio sound();
//
//
//    const int TOTAL_BUFFERS = 4u;
//    std::shared_ptr<uge::Audio> pAudio = std::shared_ptr<uge::OpenALSoftAudio>(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));
//    pAudio->vInitialize();
//
//    uge::TaskManager taskManager;
//
//    uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileResource("data/data.zip");
//    uge::ResourceCache resourceCache(100, pResourceFile); // 100MB
//    if (!resourceCache.Init())
//    {
//        std::cerr << "Error creating the resource cache!" << std::endl;
//    }
//
//    uge::IResourceLoaderSharedPointer pCreateXMLLoader = uge::XMLResourceLoader::CreateLoader();
//    resourceCache.RegisterLoader(pCreateXMLLoader);
//    uge::IResourceLoaderSharedPointer pCreateLuaScriptLoader = uge::LuaScriptResourceLoader::CreateLoader();
//    resourceCache.RegisterLoader(pCreateLuaScriptLoader);
//    // OGG loader.
//    resourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftOggResourceLoader));
//    // WAVE loader.
//    resourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftWaveResourceLoader));
//
//    // Load a sound resource and start playing it.
//    uge::Resource oggAudioResourceFile("data/audio/effects/idea803.ogg");
//    uge::ResourceHandleSharedPointer pOggAudioResource = resourceCache.GetHandle(&oggAudioResourceFile);
//    uge::IAudioBuffer* pAudioBuffer = pAudio->vInitAudioBuffer(pOggAudioResource);
//    pAudioBuffer->vPlay(0.5f, true);
//
//    // Load a sound resource and attach it to a task.
//    uge::Resource wavAudioResourceFile("data/audio/effects/blip16.wav");
//    uge::ResourceHandleSharedPointer pWavAudioResource = resourceCache.GetHandle(&wavAudioResourceFile);
//    std::shared_ptr<uge::SoundTask>soundTask(LIB_NEW uge::SoundTask(pAudio, pWavAudioResource, 1.0f, true));
//    taskManager.AttachTask(soundTask);
//
//    uge::Time::TimePoint startTime = uge::Time::GetTime();
//    while (true)
//    {
//        uge::Time::TimePoint currentTime = uge::Time::GetTime();
//        unsigned long deltaNanoseconds = uge::Time::GetDeltaAsNanoseconds(currentTime, startTime);
//
//        taskManager.UpdateTasks(deltaNanoseconds);
//        pAudio->vUpdate(deltaNanoseconds);
//
//        startTime = currentTime;
//    }
//
//    pAudio->vShutdown();
//
//    SAFE_DELETE(pResourceFile);
//
//    return 0;
//}

//int main(int argc, char* argv[])
//{
//    uge::debug::log::Init("data/debug/LogConfig.xml");
//
//    // Create application object
//    Pong app;
//
//    try
//    {
//        app.Init();
//        app.Run();
//        app.Destroy();
//    }
//    catch (Ogre::Exception& e)
//    {
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else
//        std::cerr << "An exception has occured: " <<
//                  e.getFullDescription().c_str() << std::endl;
//#endif
//    }
//
//    uge::debug::log::Destroy();
//
//    return 0;
//}
