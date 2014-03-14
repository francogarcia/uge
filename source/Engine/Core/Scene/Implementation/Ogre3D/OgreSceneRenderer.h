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
        // TODO: Going to be refactored.
        void Load();
        void CreateLights();
        void LoadResources();

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
