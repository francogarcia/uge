#pragma once

#include "IScene.h"
#include "SceneNodeProperties.h"

namespace uge
{
    class ISceneNodeRenderer
    {
    public:
        ISceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties);
        virtual ~ISceneNodeRenderer();

        virtual bool vPreRender() = 0;
        virtual bool vRender() = 0;
        //virtual bool vRenderChildren(IScene* pScene) = 0;
        virtual bool vPostRender() = 0;

        virtual bool vIsVisible() const = 0;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) = 0;
        virtual bool vRemoveChild(ActorID actorID) = 0;
    };
}
