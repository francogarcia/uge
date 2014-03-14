#pragma once

#include <Core/Scene/ICameraRenderer.h>
#include <Core/Scene/CameraNode.h>

namespace uge
{
    class OgreSceneRenderer;

    class OgreCamera : public ICameraRenderer
    {
        friend class OgreSceneRenderer;

    public:
        OgreCamera();
        virtual ~OgreCamera();

        virtual bool vOnUpdate(ICameraNodeSharedPointer pICameraNode) override;

    private:
        void Init(ICameraNodeSharedPointer pICameraNode, const std::string& cameraName, Ogre::SceneManager* pOgreSceneManager);
        void UpdateTransform(ICameraNodeSharedPointer pICameraNode);

        Ogre::SceneManager* GetOgreSceneManager();

        Ogre::Camera* GetOgreCamera();

    private:
        Ogre::Camera* m_pOgreCamera;
        Ogre::SceneManager* m_pOgreSceneManager;
    };
}
