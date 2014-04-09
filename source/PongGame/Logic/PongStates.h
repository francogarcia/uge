/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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
  */

#pragma once

#include <Core/EntityComponent/Component/TransformableComponent.h>
#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>

#include <Core/Events/IEventManager.h>
#include <Core/Events/DefaultEvents.h>

#include <Core/Physics/Implementation/BulletPhysics/BulletPhysics.h>
#include <Core/Physics/Implementation/NullPhysics/NullPhysics.h>

#include <Engine/GameLogic/BaseGameLogic.h>
#include <Engine/GameLogic/GameState/BaseGameState.h>

#include "../Events/PongEvents.h"

namespace PongState
{

    //class Uninitialized : public uge::GameState::BaseGameState
    //{
    //    friend class uge::BaseGameLogic;

    //public:
    //    /// The name of the state.
    //    static const char* g_Name;

    //    Uninitialized();
    //    virtual ~Uninitialized();

    //    virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
    //    virtual bool vDestroy() override;

    //    virtual bool vOnUpdate(unsigned long timeElapsed) override;
    //    virtual bool vOnRender(unsigned long timeElapsed) override;

    //    virtual const std::string vGetName() const override;

    //private:

    //};

    class Initializing : public uge::GameState::Initializing
    {
        friend class uge::BaseGameLogic;

    public:
        Initializing();
        virtual ~Initializing();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;
    };

    class SplashScreen : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        SplashScreen();
        virtual ~SplashScreen();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

    class MainMenu : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        MainMenu();
        virtual ~MainMenu();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

    class Running : public uge::GameState::Running
    {
        friend class uge::BaseGameLogic;

    public:
        Running();
        virtual ~Running();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

    private:
        struct CollisionInfo
        {
            uge::Vector3 sumNormalForce;
            uge::Vector3 sumFrictionForce;
            uge::Vector3List collisionPoints;
        };

        void AddToActorNameToIDMap(uge::ActorSharedPointer pActor);
        void LoadProfile(const std::string& xmlResourceFilename);

        uge::Vector3 GetPosition(uge::ActorID actorID);
        void SetPosition(uge::ActorID actorID, uge::Vector3& newPosition);
        void ApplyForce(uge::ActorID actorID, uge::Vector3& direction, float fNewtons);
        void ApplyImpulse(uge::ActorID actorID, uge::Vector3& direction, float fNewtons);
        void StopActor(uge::ActorID actorID);
        void SetMaxVelocity(uge::ActorID actorID);

        uge::Vector3 GetPosition(uge::ActorSharedPointer pActor);
        void SetPosition(uge::ActorSharedPointer pActor, uge::Vector3& newPosition);
        void ApplyForce(uge::ActorSharedPointer pActor, uge::Vector3& direction, float fNewtons);
        void ApplyImpulse(uge::ActorSharedPointer pActor, uge::Vector3& direction, float fNewtons);
        void StopActor(uge::ActorSharedPointer pActor);
        void SetMaxVelocity(uge::ActorSharedPointer pActor);

        void HandleBallCollision(uge::ActorID collisionActorID, const CollisionInfo& info);
        void HandleBallWallCollision(uge::ActorID collisionActorID, const CollisionInfo& info);
        void HandleBallPaddleCollision(uge::ActorID collisionActorID, const CollisionInfo& info);

        void HandlePaddleWallCollision(uge::ActorID actorA, uge::ActorID actorB, const CollisionInfo& info);

        void HandleGoal(uge::ActorID collisionActorID, const CollisionInfo& info);
        void HandleRebound(uge::ActorID collisionActorID, const CollisionInfo& info);

        // Event handlers.
        void RegisterDelegates();
        void UnregisterDelegates();

        void PaddleStartedMovingDelegate(uge::IEventDataSharedPointer pEventData);
        void PaddleStoppedMovingDelegate(uge::IEventDataSharedPointer pEventData);
        void CollisionStartedDelegate(uge::IEventDataSharedPointer pEventData);

    private:
        // Scene Actors
        uge::ActorSharedPointer m_pPaddle1;
        uge::ActorID m_Paddle1ID;
        uge::ActorSharedPointer m_pPaddle2;
        uge::ActorID m_Paddle2ID;

        uge::ActorSharedPointer m_pBall;
        uge::ActorID m_BallID;

        uge::ActorSharedPointer m_pLeftWall;
        uge::ActorID m_LeftWallID;
        uge::ActorSharedPointer m_pRightWall;
        uge::ActorID m_RightWallID;
        uge::ActorSharedPointer m_pTopWall;
        uge::ActorID m_TopWallID;
        uge::ActorSharedPointer m_pBottomWall;
        uge::ActorID m_BottomWallID;

        uge::ActorID m_PlaneID;

        std::map<std::string, uge::ActorID> m_ActorNameToID;

        // Game information.
        unsigned int m_Paddle1Score;
        unsigned int m_Paddle2Score;
    };

    class Paused : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        Paused();
        virtual ~Paused();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

    class HiScores : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        HiScores();
        virtual ~HiScores();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

    class NewGame : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        NewGame();
        virtual ~NewGame();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

    class GameOver : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        GameOver();
        virtual ~GameOver();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

    class Exiting : public uge::GameState::BaseGameState
    {
        friend class uge::BaseGameLogic;

    public:
        /// The name of the state.
        static const char* g_Name;

        Exiting();
        virtual ~Exiting();

        virtual bool vInit(uge::BaseGameLogic* pGameLogic) override;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
        virtual bool vDestroy() override;

        virtual bool vOnUpdate(unsigned long timeElapsed) override;
        virtual bool vOnRender(unsigned long timeElapsed) override;

        virtual const std::string vGetName() const override;
    };

}
