/*
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

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
