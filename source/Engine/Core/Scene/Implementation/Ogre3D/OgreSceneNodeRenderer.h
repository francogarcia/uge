#pragma once

#include <Core/EntityComponent/Component/Implementation/OgreGraphicalComponent.h>
#include <Core/Scene/ISceneNodeRenderer.h>
#include <Core/Scene/SceneNode.h>

namespace uge
{

    class OgreSceneNodeRenderer;
    typedef std::shared_ptr<OgreSceneNodeRenderer> OgreSceneNodeSharedPointer;

    class OgreSceneRenderer;

    class OgreSceneNodeRenderer : public ISceneNodeRenderer
    {
        friend class OgreSceneRenderer;

    public:
        OgreSceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties);
        virtual ~OgreSceneNodeRenderer();

        virtual bool vPreRender() override;
        virtual bool vRender() override;
        virtual bool vPostRender() override;

        virtual bool vIsVisible() const override;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) override;
        virtual bool vRemoveChild(ActorID actorID) override;

    protected:
        const SceneNodeProperties* const m_pSceneNodeProperties;

        //Component::OgreGraphicalComponentWeakPointer m_pRenderComponent;
        Ogre::Entity* m_pEntity;
        Ogre::SceneNode* m_pOgreSceneNode;
    };

}
