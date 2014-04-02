#pragma once

#include <Engine/GameApplication/BaseGameApplication.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "../Logic/GameLogic.h"

#include "../Views/AverageUser/View/HumanView.h"
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

            m_Output.PostInit();

            const uge::GameplayPreferences::GameplaySettings& gameplaySettings = m_CurrentPlayerProfile.GetGameplayPreferences().GetGameplaySettings();
            m_pGameLogic->vSetPlayerProfileFileName(gameplaySettings.entitySpecializationFileName);

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

            m_PlayerProfiles.SetCurrentProfile(profileResource);
            m_CurrentPlayerProfile = m_PlayerProfiles.GetCurrentProfile();

            return true;
        }

        virtual bool vInitOutputSystems() override
        {
            // Graphics
            uge::IGraphicsSharedPointer pGraphics(LIB_NEW uge::OgreGraphics(vGetGameTitle(), m_CurrentPlayerProfile.GetGraphicalPreferences()));

            // Audio
            const int TOTAL_BUFFERS = 32;
            uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));

            return m_Output.Init(pGraphics,
                                 pAudio);
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
                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::HumanView(m_Output.GetGraphics(),
                                                                            m_Output.GetAudio(),
                                                                            m_Resources.GetResourceCache(),
                                                                            m_PlayerProfiles.GetCurrentProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::HumanView> pCastGameView = std::dynamic_pointer_cast<sg::HumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }
            else if (profileName == "Motor Impairment")
            {
                uge::IGameViewSharedPointer pGameView(LIB_NEW sg::MotorImpairmentHumanView(m_Output.GetGraphics(),
                                                                                           m_Output.GetAudio(),
                                                                                           m_Resources.GetResourceCache(),
                                                                                           m_PlayerProfiles.GetCurrentProfile()));

                vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
                std::shared_ptr<sg::HumanView> pCastGameView = std::dynamic_pointer_cast<sg::HumanView>(pGameView);
                m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

                return pGameView;
            }


            assert(0 && std::string("Invalid profile name: + " + profileName + "!").c_str());

            return nullptr;
        }

    private:
        uge::PlayerProfile m_CurrentPlayerProfile;
    };

}
