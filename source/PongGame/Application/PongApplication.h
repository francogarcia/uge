#pragma once

#include <Engine/GameApplication/BaseGameApplication.h>

#include "../Logic/PongGameLogic.h"

#include "../View/AuralView/PongAuralHumanView.h"
#include "../View/GraphicalView/PongGraphicalHumanView.h"

// TODO: select the game view to be loaded from the profile.
#define PONG_GRAPHICAL_PROFILE 0
#define PONG_AURAL_PROFILE     1

class PongApplication : public uge::BaseGameApplication
{
public:
    PongApplication()
    {

    }

    ~PongApplication()
    {

    }

    virtual bool vInit() override
    {
        if (!uge::BaseGameApplication::vInit())
        {
            return false;
        }

        // Move to views.
        // TODO / FIXME : TEMPORARY CODE - load this according to the profile settings.
        {
            uge::IGameViewSharedPointer pGameView = CreateGameView();
            vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS

#if PONG_GRAPHICAL_PROFILE
            std::shared_ptr<PongGraphicalHumanView> pCastGameView = std::dynamic_pointer_cast<PongGraphicalHumanView>(pGameView);
#elif PONG_AURAL_PROFILE
            std::shared_ptr<PongAuralHumanView> pCastGameView = std::dynamic_pointer_cast<PongAuralHumanView>(pGameView);
#endif

            m_pGameLogic->vEnablePhysicsDebug(pCastGameView->GetPhysicsDebugRenderer());
#endif

            m_Output.PostInit();
        }
        // END TEMPORARY CODE

        const uge::GameplayPreferences::GameplaySettings& gameplaySettings = m_CurrentPlayerProfile.GetGameplayPreferences().GetGameplaySettings();
        m_pGameLogic->vSetPlayerProfileFileName(gameplaySettings.entitySpecializationFileName);

        return true;
    }

    virtual uge::BaseGameLogic* vCreateGameLogic() override
    {
        uge::BaseGameLogic* pGameLogic;
        pGameLogic = LIB_NEW PongGameLogic;

        return pGameLogic;
    }

    virtual std::wstring vGetGameTitle() const override
    {
        return L"Ping-Pong!";
    }

    virtual bool vInitOutputSystems()
    {
        // TODO: refactor this -> vInitPlayerProfile or something.
#if PONG_GRAPHICAL_PROFILE
        m_PlayerProfiles.SetCurrentProfile("Average User: Default");
#elif PONG_AURAL_PROFILE
        m_PlayerProfiles.SetCurrentProfile("Visually Impaired: Blind");
#endif
        m_CurrentPlayerProfile = m_PlayerProfiles.GetCurrentProfile();

        // Graphics
        uge::IGraphicsSharedPointer pGraphics(LIB_NEW uge::OgreGraphics(vGetGameTitle(), m_CurrentPlayerProfile.GetGraphicalPreferences()));

        // Audio
        const int TOTAL_BUFFERS = 32;
        uge::IAudioSharedPointer pAudio(LIB_NEW uge::OpenALSoftAudio(TOTAL_BUFFERS));

        return m_Output.Init(pGraphics,
                             pAudio);
    }

    uge::IGameViewSharedPointer CreateGameView()
    {
#if PONG_GRAPHICAL_PROFILE
        uge::IGameViewSharedPointer pGameView(LIB_NEW PongGraphicalHumanView(m_Output.GetGraphics(),
                                                                             m_Output.GetAudio(),
                                                                             m_Resources.GetResourceCache(),
                                                                             m_PlayerProfiles.GetCurrentProfile()));
#elif PONG_AURAL_PROFILE
        uge::IGameViewSharedPointer pGameView(LIB_NEW PongAuralHumanView(m_Output.GetGraphics(),
                                                                         m_Output.GetAudio(),
                                                                         m_Resources.GetResourceCache(),
                                                                         m_PlayerProfiles.GetCurrentProfile()));
#endif


        return pGameView;
    }

private:
    uge::PlayerProfile m_CurrentPlayerProfile;
};
