/*
 * (c) Copyright 2014 Franco Eusébio Garcia
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

#include <Engine/GameApplication/BaseGameApplication.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "../Logic/GameLogic.h"

#include "../Views/AverageUser/View/HumanView.h"
#include "../Views/Blind/View/AudioHumanView.h"
#include "../Views/MotorImpairment/View/MotorImpairmentHumanView.h"

namespace sg
{

    class Application : public uge::BaseGameApplication
    {
    public:
        Application()
        {

        }

        ~Application()
        {

        }

        virtual bool vInit() override
        {
            if (!uge::BaseGameApplication::vInit())
            {
                return false;
            }

            uge::IGameViewSharedPointer pGameView = CreateGameView();
            if (pGameView == nullptr)
            {
                return false;
            }

            m_OutputManager.vPostInit();

            const uge::GameplaySettings::GameplaySettingsData& gameplaySettings = m_CurrentPlayerProfile.GetGameplaySettings().GetGameplaySettingsData();
            m_pGameLogic->vSetPlayerProfileFileName(gameplaySettings.entitySpecializationResource);

            return true;
        }

        virtual uge::BaseGameLogic* vCreateGameLogic() override
        {
            uge::BaseGameLogic* pGameLogic;
            pGameLogic = LIB_NEW sg::GameLogic;

            return pGameLogic;
        }

        virtual std::wstring vGetGameTitle() const override
        {
            return L"Spaceship!";
        }

        virtual bool vInitPlayerProfiles() override
        {
            if (!uge::BaseGameApplication::vInitPlayerProfiles())
            {
                return false;
            }

            uge::XMLFile currentProfileResource;
            currentProfileResource.OpenFile("data/config/player_profiles/active_profile.xml", uge::File::FileMode::FileReadOnly);

            uge::XMLElement xmlRoot = currentProfileResource.GetRootElement();
            uge::XMLElement profileElement = xmlRoot.GetFirstChildElement("PlayerProfile");

            std::string profileResource = "";
            profileElement.GetAttribute("name", &profileResource);

            m_PlayerProfiles.SetActiveProfile(profileResource);
            m_CurrentPlayerProfile = m_PlayerProfiles.GetActiveProfile();

            return true;
        }

        virtual bool vInitOutputSystems() override
        {
            const uge::OutputSettings& outputSettings = m_CurrentPlayerProfile.GetOutputSettings();
            const uge::OutputSettings::OutputSettingsData& outputSettingsData = outputSettings.GetOutputSettingsData();

            for (const auto& subsystem : outputSettingsData.subsystems)
            {
                std::string name = subsystem.first;
                const uge::OutputSubsystemSettings::OutputSubsystemSettingsData& data = subsystem.second.GetOutputSubsystemSettingsData();
            }

            std::string graphicsName = outputSettings.GetOutputSettingsData().subsystems.at("ogre").GetOutputSubsystemSettingsData().name;
            std::string audioName = outputSettings.GetOutputSettingsData().subsystems.at("openal-soft").GetOutputSubsystemSettingsData().name;
           
            uge::IOutputSharedPointer pGraphics(m_pOutputSystemFactory->CreateOutputSubsystem(graphicsName, outputSettings));
            uge::IOutputSharedPointer pAudio(m_pOutputSystemFactory->CreateOutputSubsystem(audioName, outputSettings));

            m_AudioID = m_OutputManager.AddOutputSystem(pAudio);
            assert(m_AudioID != uge::NULL_OUTPUT_SYSTEM_ID);

            m_GraphicsID = m_OutputManager.AddOutputSystem(pGraphics);
            assert(m_GraphicsID != uge::NULL_OUTPUT_SYSTEM_ID);

            return m_OutputManager.vInit();
        }

        bool vInitResourceCache() override
        {
            const std::string resourceFileName = "data/data.zip";
            int resourceCacheSizeMB = 100; // 100MB

#if SG_USE_DEVELOPMENT_RESOURCE_FILE
            uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileDevelopmentResource(resourceFileName, "./", uge::ZipFileDevelopmentResource::Mode::Editor);
#else
            uge::IResourceFile* pResourceFile = LIB_NEW uge::ZipFileResource(resourceFileName);
#endif

            return m_Resources.Init(resourceCacheSizeMB, pResourceFile);
        }

        uge::IGameViewSharedPointer CreateGameView()
        {
            // FIXME: this should be a factory.
            std::string profileName = m_CurrentPlayerProfile.GetProfileName();
            if (profileName == "Average User: Default")
            {
                uge::IGraphicsWeakPointer pWeakGraphics = m_OutputManager.GetOutputSystem<uge::IGraphics>(m_GraphicsID);
                uge::IGraphicsSharedPointer pGraphics = pWeakGraphics.lock();
                uge::IAudioWeakPointer pWeakAudio = m_OutputManager.GetOutputSystem<uge::IAudio>(m_AudioID);
                uge::IAudioSharedPointer pAudio = pWeakAudio.lock();

                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::HumanView(pGraphics,
                                                                            pAudio,
                                                                            m_Resources.GetResourceCache(),
                                                                            m_PlayerProfiles.GetActiveProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::HumanView> pCastGameView = std::dynamic_pointer_cast<sg::HumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }
            else if (profileName == "Motor Impairment")
            {
                uge::IGraphicsWeakPointer pWeakGraphics = m_OutputManager.GetOutputSystem<uge::IGraphics>(m_GraphicsID);
                uge::IGraphicsSharedPointer pGraphics = pWeakGraphics.lock();
                uge::IAudioWeakPointer pWeakAudio = m_OutputManager.GetOutputSystem<uge::IAudio>(m_AudioID);
                uge::IAudioSharedPointer pAudio = pWeakAudio.lock();

                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::MotorImpairmentHumanView(pGraphics,
                                                                                           pAudio,
                                                                                           m_Resources.GetResourceCache(),
                                                                                           m_PlayerProfiles.GetActiveProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::MotorImpairmentHumanView> pCastGameView = std::dynamic_pointer_cast<sg::MotorImpairmentHumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }
            else if (profileName == "Visual Impairment: Low Vision")
            {
                uge::IGraphicsWeakPointer pWeakGraphics = m_OutputManager.GetOutputSystem<uge::IGraphics>(m_GraphicsID);
                uge::IGraphicsSharedPointer pGraphics = pWeakGraphics.lock();
                uge::IAudioWeakPointer pWeakAudio = m_OutputManager.GetOutputSystem<uge::IAudio>(m_AudioID);
                uge::IAudioSharedPointer pAudio = pWeakAudio.lock();

                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::HumanView(pGraphics,
                                                                            pAudio,
                                                                            m_Resources.GetResourceCache(),
                                                                            m_PlayerProfiles.GetActiveProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::HumanView> pCastGameView = std::dynamic_pointer_cast<sg::HumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }
            else if (profileName == "Cognitive Impairment")
            {
                uge::IGraphicsWeakPointer pWeakGraphics = m_OutputManager.GetOutputSystem<uge::IGraphics>(m_GraphicsID);
                uge::IGraphicsSharedPointer pGraphics = pWeakGraphics.lock();
                uge::IAudioWeakPointer pWeakAudio = m_OutputManager.GetOutputSystem<uge::IAudio>(m_AudioID);
                uge::IAudioSharedPointer pAudio = pWeakAudio.lock();

                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::HumanView(pGraphics,
                                                                            pAudio,
                                                                            m_Resources.GetResourceCache(),
                                                                            m_PlayerProfiles.GetActiveProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::HumanView> pCastGameView = std::dynamic_pointer_cast<sg::HumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }
            else if (profileName == "Visual Impairment: Blind")
            {
                uge::IGraphicsWeakPointer pWeakGraphics = m_OutputManager.GetOutputSystem<uge::IGraphics>(m_GraphicsID);
                uge::IGraphicsSharedPointer pGraphics = pWeakGraphics.lock();
                uge::IAudioWeakPointer pWeakAudio = m_OutputManager.GetOutputSystem<uge::IAudio>(m_AudioID);
                uge::IAudioSharedPointer pAudio = pWeakAudio.lock();

                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::AudioHumanView(pGraphics,
                                                                                 pAudio,
                                                                                 m_Resources.GetResourceCache(),
                                                                                 m_PlayerProfiles.GetActiveProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::AudioHumanView> pCastGameView = std::dynamic_pointer_cast<sg::AudioHumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }

            assert(0 && std::string("Invalid profile name: + " + profileName + "!").c_str());

            return nullptr;
        }

    private:
        uge::PlayerProfile m_CurrentPlayerProfile;

        uge::OutputSystemID m_GraphicsID;
        uge::OutputSystemID m_AudioID;
    };

}
