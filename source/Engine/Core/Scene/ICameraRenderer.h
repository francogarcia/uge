#pragma once

#include "IScene.h"
#include "ISceneNode.h"

namespace uge
{
    class ICameraRenderer
    {
    public:
        ICameraRenderer();
        virtual ~ICameraRenderer();

        //virtual void vOnSetTarget(ISceneNodeSharedPointer pTargetNode) = 0;
        //virtual void vOnClearTarget() = 0;

        virtual bool vOnUpdate(ICameraNodeSharedPointer pCamera)  = 0;

        //virtual void vOnSetCameraOffset(const Vector4& cameraOffset) = 0;
    };
}
