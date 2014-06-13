/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE.
 *
 * UGE is free software; you can redistribute it and/or
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#pragma once

#include <Core/Events/IEventManager.h>

#include <Core/Resource/ResourceCache.h>
#include <Core/Resource/XMLResource.h>
#include <Core/Resource/ZipFileResource.h>
#include <Core/Script/Lua/ScriptResource.h>

#include <Engine/GameView/ViewFeedback/IViewFeedback.h>

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>

#include "../../../Logic/Events/GameEvents.h"

namespace pg
{

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

            InitResourceCache("data/", 50);

            return true;
        }

        virtual void vSetAudioSystem(uge::IAudioWeakPointer pAudio)
        {
            m_pAudio = pAudio;
        }

    private:

        void RegisterDelegates(const AuralFeedback::Options& options)
        {
            if (options.bEnableOnPlayerScored)
            {
                uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &AuralFeedback::OnPlayerScored);
                uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Player_Scored::sk_EventType);
            }
        }

        void InitResourceCache(const std::string& fileName, unsigned int sizeMB)
        {
            uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileDevelopmentResource(fileName, "./", uge::ZipFileDevelopmentResource::Mode::Editor);
            bool bSuccess = m_ResourceCache.Init(sizeMB, pResourceFile); // 10 MB
            assert(bSuccess && "Could not create the resource cache!");

            uge::IResourceLoaderSharedPointer pCreateXMLLoader = uge::XMLResourceLoader::CreateLoader();
            m_ResourceCache.RegisterLoader(pCreateXMLLoader);
            uge::IResourceLoaderSharedPointer pCreateLuaScriptLoader = uge::lua::LuaScriptResourceLoader::CreateLoader();
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
            std::shared_ptr<pg::MoveActor> pData = std::static_pointer_cast<pg::MoveActor>(pEventData);
        }

        void OnStopActor(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<pg::StopActor> pData = std::static_pointer_cast<pg::StopActor>(pEventData);
        }

        void OnPlayerScored(uge::IEventDataSharedPointer pEventData)
        {
            std::shared_ptr<pg::EvtData_Player_Scored> pData = std::static_pointer_cast<pg::EvtData_Player_Scored>(pEventData);

            printf("[AuralFeedback] Player %d scored!\n", pData->GetActorID());

            PlaySoundEffect("data/audio/effects/aural-feedback/113698__huubjeroen__goalloop.wav", 0.1f, false);
        }

    private:
        uge::IAudioWeakPointer m_pAudio;
        AuralFeedback::Options m_Options;

        uge::ResourceCache m_ResourceCache;

        uge::IAudioBuffer* m_pMovingAudioBuffer;
    };

}
