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

int main(int argc, char* argv[])
{
    const int TOTAL_BUFFERS = 4u;
    std::shared_ptr<uge::Audio> pAudio = std::shared_ptr<uge::OpenALSoftAudio>(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));
    pAudio->vInit();

    uge::TaskManager taskManager;

    uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileResource("data.zip");
    uge::ResourceCache resourceCache;
    if (!resourceCache.Init(100, pResourceFile)) // 100MB
    {
        std::cerr << "Error creating the resource cache!" << std::endl;

        return -1;
    }

    uge::IResourceLoaderSharedPointer pCreateXMLLoader = uge::XMLResourceLoader::CreateLoader();
    resourceCache.RegisterLoader(pCreateXMLLoader);
    uge::IResourceLoaderSharedPointer pCreateLuaScriptLoader = uge::LuaScriptResourceLoader::CreateLoader();
    resourceCache.RegisterLoader(pCreateLuaScriptLoader);
    // OGG loader.
    resourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftOggResourceLoader));
    // WAVE loader.
    resourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftWaveResourceLoader));

    // Load a sound resource and start playing it.
    uge::Resource oggAudioResourceFile("data/audio/effects/sound.ogg");
    uge::ResourceHandleSharedPointer pOggAudioResource = resourceCache.GetHandle(&oggAudioResourceFile);
    uge::IAudioBuffer* pAudioBuffer = pAudio->vInitAudioBuffer(pOggAudioResource);
    pAudioBuffer->vPlay(0.5f, true);

    // Load a sound resource and attach it to a task.
    uge::Resource wavAudioResourceFile("data/audio/effects/sound.wav");
    uge::ResourceHandleSharedPointer pWavAudioResource = resourceCache.GetHandle(&wavAudioResourceFile);
    std::shared_ptr<uge::SoundTask>soundTask(LIB_NEW uge::SoundTask(pAudio, pWavAudioResource, 1.0f, true));
    taskManager.AttachTask(soundTask);

    uge::Time::TimePoint startTime = uge::Time::GetTime();
    while (true)
    {
        uge::Time::TimePoint currentTime = uge::Time::GetTime();
        unsigned long deltaNanoseconds = uge::Time::GetDeltaAsNanoseconds(currentTime, startTime);

        taskManager.UpdateTasks(deltaNanoseconds);
        pAudio->vUpdate(deltaNanoseconds);

        startTime = currentTime;
    }

    pAudio->vDestroy();

    SAFE_DELETE(pResourceFile);

    return 0;
}
