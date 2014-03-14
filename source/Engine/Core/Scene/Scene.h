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
