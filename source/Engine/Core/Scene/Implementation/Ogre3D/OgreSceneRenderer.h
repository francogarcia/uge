#pragma once

#include <Core/Scene/IScene.h>
#include <Core/Scene/ISceneRenderer.h>
#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>

#include "OgreCamera.h"
#include "OgreSceneNodeRenderer.h"

namespace uge
{
    class OgreSceneRenderer;
    typedef std::shared_ptr<OgreSceneRenderer> OgreSceneRendererSharedPointer;

    class ResourceCache;

    class OgreSceneRenderer : public IGraphicalSceneRenderer
    {
    public:
        OgreSceneRenderer(IGraphicsSharedPointer pGraphicalRenderer, ResourceCache& resourceCache);
        ~OgreSceneRenderer();

        virtual void CreateScene(const IScene* const pScene) override;
        virtual const IScene* const GetScene() const override;

        virtual bool vOnUpdate(const unsigned long timeElapsed) override;
        virtual bool vOnRender() override;

        virtual bool vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;
        virtual bool vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;

        virtual void vOnSetCamera(ICameraNodeSharedPointer pCamera) override;
        virtual void vOnUpdateCamera(ICameraNodeSharedPointer pCamera) override;

        virtual IGraphicsSharedPointer vGetGraphicalRenderer() override;

        virtual OutputType vGetOutputType() const override
        {
            return OutputType::Graphical;
        }

    public:
        // Internal use.
        Ogre::SceneManager* GetOgreSceneManager()
        {
            return m_pOgreSceneManager;
        }

    public:
        // Going to be refactored.
        void Load()
        {
            LoadResources();
            CreateLights();
        }

        void CreateLights()
        {
            // Create the lights.
            m_pOgreSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
            Ogre::Light* pLight = m_pOgreSceneManager->createLight("Light");
            pLight->setPosition(20.0f, 80.0f, 50.f);
        }

        void LoadResources()
        {
            // Audio and graphics resources.
            Ogre::ResourceGroupManager& resourceGroupManager = Ogre::ResourceGroupManager::getSingleton();
            resourceGroupManager.addResourceLocation("ogre/media/packs/Sinbad.zip", "Zip");
            //resourceGroupManager.addResourceLocation("data/audio/music/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/graphics/effects/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/graphics/materials/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/graphics/meshes/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/graphics/particles/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/graphics/terrains/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/graphics/textures/", "FileSystem");
            resourceGroupManager.addResourceLocation("data/debug/", "FileSystem");
            resourceGroupManager.initialiseAllResourceGroups();
        }

    private:
        void AddSceneNodeToScene(SceneNodeSharedPointer pSceneNode, Ogre::SceneNode* pOgreParentNode);

        void CreateOgreSceneNode(OgreSceneNodeRenderer* pNode, Ogre::SceneNode* pParentNode);
        void SetOgreSceneNodePosition(Ogre::SceneNode* pOgreSceneNode, const SceneNodeProperties* const pSceneNodeProperties);

        void RemoveOgreSceneNode(OgreSceneNodeRenderer* pNodeRenderer);

    private:
        IGraphicsSharedPointer m_pGraphicalRenderer;
        ResourceCache& m_ResourceCache;
        
        const IScene* m_pScene;
        std::map<ActorID, OgreSceneNodeRenderer> m_OgreSceneNodes;

        OgreCamera m_OgreCamera;

        // Ogre
        Ogre::Root* m_pOgreRoot;
        Ogre::SceneManager* m_pOgreSceneManager;
    };
}
