/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

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
