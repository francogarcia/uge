#include "GameEngineStd.h"

#include "YSECamera.h"

#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>

#include <Utilities/Math/Conversion/YSEMathConversion.h>

namespace uge
{
    YSECamera::YSECamera()
        : ICameraRenderer()
    {

    }

    YSECamera::~YSECamera()
    {

    }

    bool YSECamera::vOnUpdate(ICameraNodeSharedPointer pICameraNode)
    {
        UpdateTransform(pICameraNode);

        return true;
    }

    void YSECamera::Init(ICameraNodeSharedPointer pICameraNode)
    {
        UpdateTransform(pICameraNode);
    }

    void YSECamera::UpdateTransform(ICameraNodeSharedPointer pICameraNode)
    {
        std::shared_ptr<CameraNode> pCameraNode = std::dynamic_pointer_cast<CameraNode>(pICameraNode);

        const Vector3& position = pCameraNode->GetPosition();
        const Vector3& forwardVector = pCameraNode->GetDirection();
        const Vector3& upVector = Vector3::g_Up;

        YSE::Listener.pos(ToYSEMath(position));
        YSE::Listener.orn(ToYSEMath(forwardVector),
                          ToYSEMath(upVector));
        //YSE::Listener.vel();
    }
}
