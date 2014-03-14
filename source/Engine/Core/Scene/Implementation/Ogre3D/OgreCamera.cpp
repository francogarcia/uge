#include "GameEngineStd.h"

#include "OgreCamera.h"

#include <Utilities/Math/Conversion/OgreMathConversion.h>

namespace uge
{
    OgreCamera::OgreCamera()
        : ICameraRenderer(), m_pOgreCamera(nullptr), m_pOgreSceneManager(nullptr)
    {

    }

    OgreCamera::~OgreCamera()
    {

    }

    bool OgreCamera::vOnUpdate(ICameraNodeSharedPointer pCamera)
    {
        UpdateTransform(pCamera);

        return true;
    }

    void OgreCamera::Init(ICameraNodeSharedPointer pICameraNode,
                          const std::string& cameraName,
                          Ogre::SceneManager* pOgreSceneManager)
    {
        assert(pOgreSceneManager != nullptr && "Invalid scene manager!");

        m_pOgreSceneManager = pOgreSceneManager;

        m_pOgreCamera = m_pOgreSceneManager->createCamera(cameraName);
        UpdateTransform(pICameraNode);
    }

    void OgreCamera::UpdateTransform(ICameraNodeSharedPointer pICameraNode)
    {
        std::shared_ptr<CameraNode> pCameraNode = std::dynamic_pointer_cast<CameraNode>(pICameraNode);
        m_pOgreCamera->setPosition(ToOgreMath(pCameraNode->GetPosition()));
        m_pOgreCamera->setOrientation(ToOgreMath(pCameraNode->GetRotation()));
        //m_pOgreCamera->lookAt(Ogre::Vector3(0.0f, 0.0f, -300.0f));
        //const Frustum frustum = pCameraNode->vGetFrustum();
        //m_pOgreCamera->setNearClipDistance(frustum.GetNearPlaneDistance());
        //m_pOgreCamera->setFarClipDistance(frustum.GetFarPlaneDistance());
        //m_pOgreCamera->setAspectRatio(frustum.GetAspectRatio());

        m_pOgreCamera->setCustomProjectionMatrix(true, ToOgreMath(pCameraNode->vGetProjectionMatrix()));
        //m_pOgreCamera->setCustomViewMatrix(true, ToOgreMath(pCameraNode->vGetViewMatrix()));
    }

    Ogre::SceneManager* OgreCamera::GetOgreSceneManager()
    {
        return m_pOgreSceneManager;
    }

    Ogre::Camera* OgreCamera::GetOgreCamera()
    {
        return m_pOgreCamera;
    }
}
