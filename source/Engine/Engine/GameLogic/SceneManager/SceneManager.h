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
 */

#pragma once

#include <Core/Scene/IScene.h>
#include <Core/Scene/Scene.h>

namespace uge
{
    class SceneManager
    {
    public:
        SceneManager();

        ~SceneManager();

        bool Init();

        bool Destroy();

        bool Update(const unsigned long timeElapsed);

        bool AddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode);

        ISceneNodeSharedPointer CreateAndAddSceneNode(ActorSharedPointer pActor);

        bool RemoveSceneNode(ActorID actorID);

        ISceneNodeSharedPointer GetSceneNode(ActorID actorID);

        Scene* GetScene() const;

    private:
        // Scene
        Scene* m_pScene;
    };

}
