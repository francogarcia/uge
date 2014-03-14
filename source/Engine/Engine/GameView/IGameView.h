#pragma once

#include <Core/Scene/IScene.h>

namespace uge
{

    typedef unsigned int GameViewID;

    class IGameView;
    typedef std::shared_ptr<IGameView> IGameViewSharedPointer;
    typedef std::list<IGameViewSharedPointer> IGameViewList;

    enum class GameViewType : unsigned char
    {
        HumanView,
        RemoteView,
        AIView,
        RecorderView,
        OtherView,
    };

    class IGameView
    {
    public:
        static const GameViewID NULL_GAME_VIEW_ID = 0u;

        IGameView();
        virtual ~IGameView();

        virtual bool vInit(IScene* pScene) = 0;
        virtual bool vDestroy() = 0;

        virtual GameViewID vGetID() const = 0;
        virtual GameViewType vGetType() const = 0;

        virtual void vOnAttach(GameViewID viewID, ActorID actorID) = 0;
        virtual void vOnRestore() = 0;
        virtual bool vOnUpdate(const unsigned long timeElapsed) = 0;
        virtual bool vOnRender(const unsigned long currentTime, const unsigned timeElapsed) = 0;

        virtual SceneRendererID vAddSceneRenderer(ISceneRendererSharedPointer pRenderer) = 0;
        virtual ISceneRendererSharedPointer vGetSceneRenderer(SceneRendererID rendererID) = 0;
        virtual void vRemoveSceneRenderer(SceneRendererID rendererID) = 0;

    private:
    };

}
