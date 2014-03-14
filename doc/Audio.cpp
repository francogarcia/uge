#include "PongGameStd.h"

// #include <vld.h>

//#include <Utilities/Debug/Logger.h>

//#include <Core/Script/Lua/LuaStateManager.h>
//#include <Core/Script/Lua/ScriptTask.h>
//#include <Core/Script/Lua/ScriptExports.h>
//
//#include <Engine/GameApplication/BaseGameApplication.h>
//#include <Engine/GameLogic/BaseGameLogic.h>

// #include <EntityComponent/Entity/Actor.h>
// #include <EntityComponent/Entity/ActorFactory.h>
// #include <EntityComponent/Component/ActorComponent.h>
//
// #include <Events/Event.h>
// #include <Events/EventManager.h>
// #include <Events/DefaultEvents.h>
//
// #include <System/Clock.h>
// #include <System/Time.h>

//#include "Logic/Pong.h"

#include "PongGameStd.h"

#include <Core/Resource/Resource.h>
#include <Core/Resource/ResourceCache.h>
#include <Core/Resource/XMLResource.h>
#include <Core/Resource/ZipFileResource.h>
#include <Core/Script/Lua/ScriptResource.h>
#include <Core/Task/TaskManager.h>

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/AudioTask.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/System/Time.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>    /* for sqrtf() */
#include <time.h>    /* for time(), to seed srand() */

/* OpenAL headers */
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

/* load a file into memory, returning the buffer and
 * setting bufsize to the size-in-bytes */
void* load(char* fname, long* bufsize)
{
    FILE* fp = fopen(fname, "rb");
    fseek(fp, 0L, SEEK_END);
    long len = ftell(fp);
    rewind(fp);
    void* buf = malloc(len);
    fread(buf, 1, len, fp);
    fclose(fp);
    *bufsize = len;
    return buf;
}

/* randomly displace 'a' by one meter +/- in x or z */
void randWalk(float* a)
{
    int r = rand() & 0x3;
    switch (r)
    {
        case 0:
            a[0] -= 1.;
            break;
        case 1:
            a[0] += 1.;
            break;
        case 2:
            a[2] -= 1.;
            break;
        case 3:
            a[2] += 1.;
            break;
    }
    printf("Walking to: %.1f,%.1f,%.1f\n", a[0], a[1], a[2]);
}

void circleWalk(float centerX, float centerZ, float radius,
                float angle, float& positionX, float& positionZ)
{
    positionX = centerX + radius * std::cos(angle);
    positionZ = centerZ + radius * std::sin(angle);
}

int main(int argc, char* argv[])
{
    /* Start just 1m to the right. */
    float position[3] = {1.0f, 0.0f, 0.0f};

    /* initialize OpenAL context, asking for 44.1kHz to match HRIR data */
    ALCint contextAttr[] = {ALC_FREQUENCY, 44100, 0};
    ALCdevice* device = alcOpenDevice(NULL);
    ALCcontext* context = alcCreateContext(device, contextAttr);
    alcMakeContextCurrent(context);

    /* listener at origin, facing z (ears at 0m height) */
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    float orient[6] = {/*fwd:*/ 0.0f, 0.0f, 1.0f, /*up:*/ 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_ORIENTATION, orient);

    /* this will be the source of ghostly footsteps... */
    ALuint source;
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
    alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(source, AL_LOOPING, AL_TRUE);

    /* allocate an OpenAL buffer and fill it with monaural sample data */
    ALuint buffer;
    alGenBuffers(1, &buffer);
    {
        long dataSize;
        const ALvoid* data = load("data/audio/effects/drone.ogg", &dataSize);
        /* for simplicity, assume raw file is signed-16b at 44.1kHz */
        alBufferData(buffer, AL_FORMAT_MONO16, data, dataSize, 44100);
        free((void*)data);
    }
    alSourcei(source, AL_BUFFER, buffer);

    /* state initializations for the upcoming loop */
    srand((int)time(NULL));
    const float dt = 1.0f / 1.0f; // 2 frames per second.
    const float vel = 0.2f;
    const float pi = 3.141592f;
    const float radius = 10.0f;

    /** BEGIN! **/
    alSourcePlay(source);

    fflush(stderr);   /* in case OpenAL reported an error earlier */

    /* loop forever... walking to random, adjacent, integer coordinates */
    float angle = 0.0f;
    for (;;)
    {
        // Move in circles.
        circleWalk(0.0f, 0.0f, radius, angle, position[0], position[2]);
        alSource3f(source, AL_POSITION, position[0], position[1], position[2]);

        angle += (vel);
        if (angle > 2 * pi)
        {
            angle = angle - 2 * pi;
        }

        printf("(%f, %f, %f)\n", position[0], position[1], position[2]);
        printf("dist = %f\n\n", std::sqrtf(std::pow(position[0], 2) + std::pow(position[0], 2)));

        Sleep(dt * 1000);
    }

    /* cleanup that should be done when you have a proper exit... ;) */
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}


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
