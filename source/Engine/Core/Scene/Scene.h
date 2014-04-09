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
