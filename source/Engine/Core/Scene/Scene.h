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

#include "CameraNode.h"
#include "IScene.h"
#include "ISceneRenderer.h"
#include "SceneNode.h"

namespace uge
{
    class Scene : public IScene
    {
    public:
        Scene();
        ~Scene();

        virtual bool vOnUpdate(const unsigned long timeElapsed) override;

        virtual ISceneNodeSharedPointer vGetRootSceneNode() const override;

        virtual bool vAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;
        virtual ISceneNodeSharedPointer vFindActor(ActorID actorID) override;
        virtual bool vRemoveChild(ActorID actorID) override;

        virtual void vPushSetMatrix(const Matrix4& toWorld) override;
        virtual void vPopMatrix() override;
        virtual const Matrix4& vGetTopMatrix() const override;

    protected:
        virtual bool vAddChildrenToMap(ActorID actorID, ISceneNodeSharedPointer pSceneNode);
        virtual void vRemoveChildrenFromMap(ActorID actorID);

        virtual void vNotifyNewChildrenNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode);

    protected:
        MatrixStack m_MatrixStack;
        
        SceneNodeSharedPointer m_pRootNode;

        SceneActorMap m_ActorMap;
    };
}
