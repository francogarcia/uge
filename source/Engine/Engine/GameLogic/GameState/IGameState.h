#pragma once

namespace uge
{

    class BaseGameLogic;

    class IGameState
    {
    public:
        IGameState();
        virtual ~IGameState();

        virtual bool vInit(BaseGameLogic* pGameLogic) = 0;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) = 0;
        virtual bool vDestroy() = 0;

        virtual bool vOnUpdate(unsigned long timeElapsed) = 0;
        virtual bool vOnRender(unsigned long timeElapsed) = 0;

        virtual const std::string vGetName() const = 0;
    };

}
