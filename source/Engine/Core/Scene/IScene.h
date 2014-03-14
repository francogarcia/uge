#pragma once

#include "ISceneNode.h"
#include "ISceneRenderer.h"

namespace uge
{
    class IScene
    {
    public:
        IScene();
        virtual ~IScene();

        virtual bool vOnUpdate(const unsigned long timeElapsed) = 0;

        virtual ISceneNodeSharedPointer vGetRootSceneNode() const = 0;

        virtual bool vAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;
        virtual ISceneNodeSharedPointer vFindActor(ActorID actorID) = 0;
        virtual bool vRemoveChild(ActorID actorID) = 0;

        virtual void vPushSetMatrix(const Matrix4& toWorld) = 0;
        virtual void vPopMatrix() = 0;
        virtual const Matrix4& vGetTopMatrix() const = 0;
    };

}