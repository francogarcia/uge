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

#include "../Events/GameEvents.h"

namespace sg
{

namespace GameState
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

}
