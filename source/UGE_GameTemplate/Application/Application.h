#pragma once

#include <Engine/GameApplication/BaseGameApplication.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "../Logic/GameLogic.h"

#include "../View/HumanView.h"

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

        // Move to views.
        // TODO / FIXME : TEMPORARY CODE - load this according to the profile settings.
        {
            uge::IGameViewSharedPointer pGameView = CreateGameView();
            vAddGameView(pGameView);

#ifdef UGE_DEBUG_PHYSICS
            std::shared_ptr<sg::HumanView> pCastGameView = std::dynamic_pointer_cast<sg::HumanView>(pGameView);
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
        pGameLogic = LIB_NEW sg::GameLogic;

        return pGameLogic;
    }

    virtual std::wstring vGetGameTitle() const override
    {
        return L"GameName!";
    }

    virtual bool vInitOutputSystems()
    {
        // TODO: refactor this -> vInitPlayerProfile or something.
        m_PlayerProfiles.SetCurrentProfile("Average User: Default");
        //m_PlayerProfiles.SetCurrentProfile("Visually Impaired: Blind");
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
        uge::IGameViewSharedPointer pGameView(LIB_NEW sg::HumanView(m_Output.GetGraphics(),
                                                                    m_Output.GetAudio(),
                                                                    m_Resources.GetResourceCache(),
                                                                    m_PlayerProfiles.GetCurrentProfile()));

        return pGameView;
    }

private:
    uge::PlayerProfile m_CurrentPlayerProfile;
};

}
