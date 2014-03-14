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
