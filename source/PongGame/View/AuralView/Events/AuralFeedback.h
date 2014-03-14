#pragma once

#include <Core/Events/IEventManager.h>

#include <Core/Resource/ResourceCache.h>
#include <Core/Resource/XMLResource.h>
#include <Core/Resource/ZipFileResource.h>
#include <Core/Script/Lua/ScriptResource.h>

#include <Engine/GameView/ViewFeedback/IViewFeedback.h>

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>

#include "../../../Events/PongEvents.h"

class AuralFeedback : public uge::IViewFeedback
{
public:
    static const char* g_Name;

    struct Options
    {
        Options()
            : bEnableOnRestartGame(false),
              bEnableOnPlayerScored(false),
              bEnableOnBallWallCollision(false),
              bEnableOnBallPaddleCollision(false),
              bEnableOnPaddleWallCollision(false),
              bEnableOnMovePaddle(false),
              bEnableOnStopPaddle(false)
        {

        }

        bool bEnableOnRestartGame;
        bool bEnableOnPlayerScored;
        bool bEnableOnBallWallCollision;
        bool bEnableOnBallPaddleCollision;
        bool bEnableOnPaddleWallCollision;
        bool bEnableOnMovePaddle;
        bool bEnableOnStopPaddle;
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

            if (eventName == "OnRestartGame")
            {
                afOptions.bEnableOnRestartGame = bEventEnabled;
            }
            else if (eventName == "OnPlayerScored")
            {
                afOptions.bEnableOnPlayerScored = bEventEnabled;
            }
            else if (eventName == "OnBallWallCollision")
            {
                afOptions.bEnableOnBallWallCollision = bEventEnabled;
            }
            else if (eventName == "OnBallPaddleCollision")
            {
                afOptions.bEnableOnBallPaddleCollision = bEventEnabled;
            }
            else if (eventName == "OnPaddleWallCollision")
            {
                afOptions.bEnableOnPaddleWallCollision = bEventEnabled;
            }
            else if (eventName == "OnMovePaddle")
            {
                afOptions.bEnableOnMovePaddle = bEventEnabled;
            }
            else if (eventName == "OnStopPaddle")
            {
                afOptions.bEnableOnStopPaddle = bEventEnabled;
            }
        }

        xmlFile.CloseFile();

        RegisterDelegates(afOptions);

        InitResourceCache("data/aural-feedback.zip", 10);

        return true;
    }

    virtual void vSetAudioSystem(uge::IAudioWeakPointer pAudio)
    {
        m_pAudio = pAudio;
    }

private:

    void RegisterDelegates(const AuralFeedback::Options& options)
    {
        if (options.bEnableOnRestartGame)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnRestartGame);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Restart_Game::sk_EventType);
        }

        if (options.bEnableOnPlayerScored)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnPlayerScored);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Player_Scored::sk_EventType);
        }

        if (options.bEnableOnBallWallCollision)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnBallWallCollision);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Ball_Wall_Collision::sk_EventType);
        }

        if (options.bEnableOnBallPaddleCollision)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnBallPaddleCollision);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Ball_Paddle_Collision::sk_EventType);
        }

        if (options.bEnableOnPaddleWallCollision)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnPaddleWallCollision);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Paddle_Wall_Collision::sk_EventType);
        }

        if (options.bEnableOnMovePaddle)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnMovePaddle);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Move_Paddle::sk_EventType);
        }

        if (options.bEnableOnStopPaddle)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnStopPaddle);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Stop_Paddle::sk_EventType);
        }
    }

    void InitResourceCache(const std::string& fileName, unsigned int sizeMB)
    {
        uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileResource(fileName);
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

    uge::IAudioBuffer* PlaySound(const std::string& fileName, float fVolume, bool bLoop, const uge::Vector3& position = uge::Vector3::g_Zero)
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

    void OnRestartGame(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Restart_Game> pData = std::static_pointer_cast<EvtData_Restart_Game>(pEventData);

        printf("[AuralFeedback] Game restarted!\n");
    }

    void OnPlayerScored(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Player_Scored> pData = std::static_pointer_cast<EvtData_Player_Scored>(pEventData);

        printf("[AuralFeedback] Player %d scored!\n", pData->GetActorID());

        PlaySound("113698__huubjeroen__goalloop.wav", 0.1f, false);
    }

    void OnBallWallCollision(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Ball_Wall_Collision> pData = std::static_pointer_cast<EvtData_Ball_Wall_Collision>(pEventData);

        const uge::Vector3List& collisionPoints = pData->GetCollisionPoints();
        uge::Vector3 collisionPoint = collisionPoints.front();

        printf("[AuralFeedback] Ball collided with wall at (%f, %f, %f)!\n", collisionPoint.x, collisionPoint.y, collisionPoint.z);

        PlaySound("wood_hit_aluminium_1.wav", 0.5f, false, collisionPoint);
    }

    void OnBallPaddleCollision(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Ball_Paddle_Collision> pData = std::static_pointer_cast<EvtData_Ball_Paddle_Collision>(pEventData);

        printf("[AuralFeedback] Ball collided with paddle!\n");

        PlaySound("small_hard_object_strike_large_metal_drum.wav", 0.5f, false);
    }

    void OnPaddleWallCollision(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Paddle_Wall_Collision> pData = std::static_pointer_cast<EvtData_Paddle_Wall_Collision>(pEventData);

        const uge::Vector3List& collisionPoints = pData->GetCollisionPoints();
        uge::Vector3 collisionPoint = collisionPoints.front();

        printf("[AuralFeedback] Paddle collided with wall at (%f, %f, %f)!\n", collisionPoint.x, collisionPoint.y, collisionPoint.z);

        //PlaySound("wood_hit_aluminium_1.wav", 0.5f, false, collisionPoint);
        PlaySound("small_metal_impact.wav", 0.5f, false, collisionPoint);
    }

    void OnMovePaddle(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Move_Paddle> pData = std::static_pointer_cast<EvtData_Move_Paddle>(pEventData);

        printf("[AuralFeedback] Paddle moved!\n");

        // Loop sound, stop when OnStopPaddle.
        if (m_pMovingAudioBuffer == nullptr)
        {
            //m_pMovingAudioBuffer = PlaySound("Footsteps On Soft Foam Play Mat.wav", 1.0f, true);
        }
    }

    void OnStopPaddle(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Stop_Paddle> pData = std::static_pointer_cast<EvtData_Stop_Paddle>(pEventData);

        printf("[AuralFeedback] Paddle stoped!\n");

        //m_pMovingAudioBuffer->vStop();
        //m_pMovingAudioBuffer = nullptr;
    }


private:
    uge::IAudioWeakPointer m_pAudio;
    AuralFeedback::Options m_Options;

    uge::ResourceCache m_ResourceCache;

    uge::IAudioBuffer* m_pMovingAudioBuffer;
};
