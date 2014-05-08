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

#include <Engine/GameApplication/BaseGameApplication.h>

#include <IO/Output/OutputFactory.h>

#include "../Logic/PongGameLogic.h"

#include "../View/AuralView/PongAuralHumanView.h"
#include "../View/GraphicalView/PongGraphicalHumanView.h"

// TODO: select the game view to be loaded from the profile.
#define PONG_GRAPHICAL_PROFILE 1
//#define PONG_AURAL_PROFILE     0

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

            m_OutputManager.vPostInit();
        }
        // END TEMPORARY CODE

        const uge::GameplaySettings::GameplaySettingsData& gameplaySettings = m_CurrentPlayerProfile.GetGameplaySettings().GetGameplaySettingsData();
        m_pGameLogic->vSetPlayerProfileFileName(gameplaySettings.entitySpecializationResource);

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
        m_PlayerProfiles.SetActiveProfile("Average User: Default");
#elif PONG_AURAL_PROFILE
        m_PlayerProfiles.SetActiveProfile("Visually Impaired: Blind");
#endif
        m_CurrentPlayerProfile = m_PlayerProfiles.GetActiveProfile();

        m_OutputFactory.Init();
        const uge::OutputSettings& outputSettings = m_CurrentPlayerProfile.GetOutputSettings();
        uge::IOutputSharedPointer pGraphics(m_OutputFactory.CreateOutputSubsystem("Ogre", outputSettings));
        uge::IOutputSharedPointer pAudio(m_OutputFactory.CreateOutputSubsystem("OpenAL-Soft", outputSettings));

        m_AudioID = m_OutputManager.AddOutputSystem(pAudio);
        assert(m_AudioID != uge::NULL_OUTPUT_SYSTEM_ID);

        m_GraphicsID = m_OutputManager.AddOutputSystem(pGraphics);
        assert(m_GraphicsID != uge::NULL_OUTPUT_SYSTEM_ID);

        return m_OutputManager.vInit();
    }

    uge::IGameViewSharedPointer CreateGameView()
    {
        uge::IGraphicsWeakPointer pWeakGraphics = m_OutputManager.GetOutputSystem<uge::IGraphics>(m_GraphicsID);
        uge::IGraphicsSharedPointer pGraphics = pWeakGraphics.lock();
        uge::IAudioWeakPointer pWeakAudio = m_OutputManager.GetOutputSystem<uge::IAudio>(m_AudioID);
        uge::IAudioSharedPointer pAudio = pWeakAudio.lock();

#if PONG_GRAPHICAL_PROFILE
        uge::IGameViewSharedPointer pGameView(LIB_NEW PongGraphicalHumanView(pGraphics,
                                                                             pAudio,
                                                                             m_Resources.GetResourceCache(),
                                                                             m_PlayerProfiles.GetActiveProfile()));
#elif PONG_AURAL_PROFILE
        uge::IGameViewSharedPointer pGameView(LIB_NEW PongAuralHumanView(pGraphics,
                                                                         pAudio,
                                                                         m_Resources.GetResourceCache(),
                                                                         m_PlayerProfiles.GetActiveProfile()));
#endif


        return pGameView;
    }

private:
    uge::PlayerProfile m_CurrentPlayerProfile;

    uge::OutputFactory m_OutputFactory;

    uge::OutputSystemID m_GraphicsID;
    uge::OutputSystemID m_AudioID;
};
