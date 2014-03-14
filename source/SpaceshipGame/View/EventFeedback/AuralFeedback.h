#pragma once

#include <Core/Events/IEventManager.h>

#include <Core/Resource/ResourceCache.h>
#include <Core/Resource/XMLResource.h>
#include <Core/Resource/ZipFileResource.h>
#include <Core/Script/Lua/ScriptResource.h>

#include <Engine/GameView/ViewFeedback/IViewFeedback.h>

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>

#include "../../Logic/Events/GameEvents.h"

namespace sg
{

    class AuralFeedback : public uge::IViewFeedback
    {
    public:
        static const char* g_Name;

        struct Options
        {
            Options()
                : bEnableOnMoveActor(false),
                  bEnableOnStopActor(false)
            {

            }

            bool bEnableOnMoveActor;
            bool bEnableOnStopActor;
        };

        AuralFeedback()
            : m_Options(), m_pAudio(), m_pMovingAudioBuffer(nullptr)
        {

        }

        ~AuralFeedback()
        {
            m_pAudio.reset();
        }

        virtual bool vInit(const std::string& resourceFileName) override
        {
            uge::XMLFile xmlFile;
            xmlFile.OpenFile(resourceFileName, uge::File::FileMode::FileReadOnly);
            assert(xmlFile.IsGood() && "XML file could not be opened!");

            uge::XMLElement xmlRootElement(xmlFile.GetRootElement());
            assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

            AuralFeedback::Options afOptions;
            uge::XMLElement eventsElement = xmlRootElement.GetFirstChildElement("Events");
            assert(eventsElement.IsGood() && "Events element not found!");
            for (uge::XMLElement xmlElement = eventsElement.GetFirstChildElement("Event");
                 xmlElement.IsGood(); xmlElement = xmlElement.GetNextSiblingElement())
            {
                std::string eventName;
                xmlElement.GetAttribute("name", &eventName);

                bool bEventEnabled;
                xmlElement.GetBoolAttribute("enabled", &bEventEnabled);
                if (eventName == "OnMoveActor")
                {
                    afOptions.bEnableOnMoveActor = bEventEnabled;
                }
                else if (eventName == "OnStopActor")
                {
                    afOptions.bEnableOnStopActor = bEventEnabled;
                }
            }

            xmlFile.CloseFile();

            RegisterDelegates(afOptions);

            InitResourceCache("data/", 10);

            return true;
        }

        virtual void vSetAudioSystem(uge::IAudioWeakPointer pAudio)
        {
            m_pAudio = pAudio;
        }

    private:

        void RegisterDelegates(const AuralFeedback::Options& options)
        {
            if (options.bEnableOnMoveActor)
            {
                uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnMoveActor);
                uge::IEventManager::Get()->vAddListener(functionDelegate, sg::MoveActor::sk_EventType);
            }

            if (options.bEnableOnStopActor)
            {
                uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnStopActor);
                uge::IEventManager::Get()->vAddListener(functionDelegate, sg::StopActor::sk_EventType);
            }
        }

        void InitResourceCache(const std::string& fileName, unsigned int sizeMB)
        {
            uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileDevelopmentResource(fileName, "./", uge::ZipFileDevelopmentResource::Mode::Editor);
            bool bSuccess = m_ResourceCache.Init(sizeMB, pResourceFile); // 10 MB
            assert(bSuccess && "Could not create the resource cache!");

            uge::IResourceLoaderSharedPointer pCreateXMLLoader = uge::XMLResourceLoader::CreateLoader();
            m_ResourceCache.RegisterLoader(pCreateXMLLoader);
            uge::IResourceLoaderSharedPointer pCreateLuaScriptLoader = uge::LuaScriptResourceLoader::CreateLoader();
            m_ResourceCache.RegisterLoader(pCreateLuaScriptLoader);
            // OGG loader.
            m_ResourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftOggResourceLoader));
            // WAVE loader.
            m_ResourceCache.RegisterLoader(std::shared_ptr<uge::IResourceLoader>(LIB_NEW uge::OpenALSoftWaveResourceLoader));
        }

        uge::IAudioBuffer* PlaySoundEffect(const std::string& fileName, float fVolume, bool bLoop, const uge::Vector3& position = uge::Vector3::g_Zero)
        {
            uge::Resource pResourceFile(fileName);
            uge::ResourceHandleSharedPointer pResource = m_ResourceCache.GetHandle(&pResourceFile);

            if (!m_pAudio.expired())
            {
                uge::IAudioBuffer* pAudioBuffer = m_pAudio.lock()->vInitAudioBuffer(pResource);
                pAudioBuffer->vSetPosition(position);
                pAudioBuffer->vPlay(fVolume, bLoop);

                return pAudioBuffer;
            }

            return nullptr;
        }

        void OnMoveActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<sg::MoveActor> pData = std::static_pointer_cast<sg::MoveActor>(pEventData);

            printf("[AuralFeedback] Actor %u started moving!\n", pData->GetActorID());
            PlaySoundEffect("data/audio/effects/sound.wav", 1.0f, false);
        }

        void OnStopActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<sg::StopActor> pData = std::static_pointer_cast<sg::StopActor>(pEventData);

            printf("[AuralFeedback] Actor %u stopped!\n", pData->GetActorID());
        }

    private:
        uge::IAudioWeakPointer m_pAudio;
        AuralFeedback::Options m_Options;

        uge::ResourceCache m_ResourceCache;

        uge::IAudioBuffer* m_pMovingAudioBuffer;
    };

}
