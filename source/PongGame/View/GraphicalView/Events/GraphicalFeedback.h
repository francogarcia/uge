#pragma once

#include <Core/Events/IEventManager.h>
#include <IO/Output/Graphics/Graphics.h>

#include "../../../Events/PongEvents.h"

class GraphicalFeedback
{
public:
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


    GraphicalFeedback(const GraphicalFeedback::Options& options, uge::IGraphicsWeakPointer pGraphics)
        : m_Options(options), m_pGraphics(pGraphics)
    {
        RegisterDelegates(options);
    }

    ~GraphicalFeedback()
    {
        m_pGraphics.reset();
    }

private:

    void RegisterDelegates(const GraphicalFeedback::Options& options)
    {
        if (options.bEnableOnRestartGame)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnRestartGame);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Restart_Game::sk_EventType);
        }

        if (options.bEnableOnPlayerScored)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnPlayerScored);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Player_Scored::sk_EventType);
        }

        if (options.bEnableOnBallWallCollision)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnBallWallCollision);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Ball_Wall_Collision::sk_EventType);
        }

        if (options.bEnableOnBallPaddleCollision)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnBallPaddleCollision);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Ball_Paddle_Collision::sk_EventType);
        }

        if (options.bEnableOnPaddleWallCollision)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnPaddleWallCollision);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Paddle_Wall_Collision::sk_EventType);
        }

        if (options.bEnableOnMovePaddle)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnMovePaddle);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Move_Paddle::sk_EventType);
        }

        if (options.bEnableOnStopPaddle)
        {
            uge::EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &GraphicalFeedback::OnStopPaddle);
            uge::IEventManager::Get()->vAddListener(functionDelegate, EvtData_Stop_Paddle::sk_EventType);
        }
    }

    void OnRestartGame(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Restart_Game> pData = std::static_pointer_cast<EvtData_Restart_Game>(pEventData);
    }

    void OnPlayerScored(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Player_Scored> pData = std::static_pointer_cast<EvtData_Player_Scored>(pEventData);
    }

    void OnBallWallCollision(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Ball_Wall_Collision> pData = std::static_pointer_cast<EvtData_Ball_Wall_Collision>(pEventData);
    }

    void OnBallPaddleCollision(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Ball_Paddle_Collision> pData = std::static_pointer_cast<EvtData_Ball_Paddle_Collision>(pEventData);
    }

    void OnPaddleWallCollision(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Paddle_Wall_Collision> pData = std::static_pointer_cast<EvtData_Paddle_Wall_Collision>(pEventData);
    }

    void OnMovePaddle(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Move_Paddle> pData = std::static_pointer_cast<EvtData_Move_Paddle>(pEventData);
    }

    void OnStopPaddle(uge::IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Stop_Paddle> pData = std::static_pointer_cast<EvtData_Stop_Paddle>(pEventData);
    }

private:
    uge::IGraphicsWeakPointer m_pGraphics;
    GraphicalFeedback::Options m_Options;

};
