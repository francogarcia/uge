#pragma once

#include <Core/Scene/ICameraRenderer.h>
#include <Core/Scene/CameraNode.h>

namespace uge
{
    class YSESceneRenderer;

    class YSECamera : public ICameraRenderer
    {
        friend class YSESceneRenderer;

    public:
        YSECamera();
        virtual ~YSECamera();

        virtual bool vOnUpdate(ICameraNodeSharedPointer pICameraNode) override;

    private:
        void Init(ICameraNodeSharedPointer pICameraNode);
        void UpdateTransform(ICameraNodeSharedPointer pICameraNode);
    };
}
