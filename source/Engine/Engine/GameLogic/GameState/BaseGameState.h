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

#include "IGameState.h"

namespace uge
{

    namespace GameState
    {

        class BaseGameState : public IGameState
        {
        public:
            BaseGameState();
            virtual ~BaseGameState();

            virtual bool vInit(BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) = 0;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const = 0;

        protected:
            BaseGameLogic* m_pGameLogic;

            unsigned long m_LifeTime;
        };

        class Uninitialized : public BaseGameState
        {
            friend class BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            Uninitialized();
            virtual ~Uninitialized();

            virtual bool vInit(BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;

        private:

        };

        class Initializing : public BaseGameState
        {
            friend class BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            Initializing();
            virtual ~Initializing();

            virtual bool vInit(BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;

        };

        class Running : public BaseGameState
        {
            friend class BaseGameLogic;

        public:
            /// The name of the state.
            static const char* g_Name;

            Running();
            virtual ~Running();

            virtual bool vInit(BaseGameLogic* pGameLogic) override;
            virtual bool vTailorToProfile(const std::string& xmlResourceFilename) override;
            virtual bool vDestroy() override;

            virtual bool vOnUpdate(unsigned long timeElapsed) override;
            virtual bool vOnRender(unsigned long timeElapsed) override;

            virtual const std::string vGetName() const override;
        };

    }

}
