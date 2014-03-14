#pragma once

#include <Core/Scene/ICameraRenderer.h>
#include <Core/Scene/CameraNode.h>

namespace uge
{
    class OpenALSoftSceneRenderer;

    class OpenALSoftCamera : public ICameraRenderer
    {
        friend class OpenALSoftSceneRenderer;

    public:
        OpenALSoftCamera();
        virtual ~OpenALSoftCamera();

        virtual bool vOnUpdate(ICameraNodeSharedPointer pCamera) override;

    private:
        void Init(ICameraNodeSharedPointer pICameraNode);
        void UpdateTransform(ICameraNodeSharedPointer pICameraNode);
    };
}
