/*
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

#pragma once

#include <Core/Scene/IScene.h>

#include <IO/Output/Graphics/Implementation/Ogre3D/OgreGraphics.h>
#include <IO/Output/Scene/ISceneRenderer.h>

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
        OgreSceneRenderer();
        ~OgreSceneRenderer();

        virtual bool vInit(IOutputSharedPointer pSystem, ResourceCache* pResourceCache) override;

        virtual void vCreateScene(const IScene* const pScene) override;
        virtual const IScene* const vGetScene() const override;

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
        OgreGraphicsSharedPointer m_pGraphicalRenderer;
        ResourceCache* m_pResourceCache;
        
        const IScene* m_pScene;
        std::map<ActorID, OgreSceneNodeRenderer> m_OgreSceneNodes;

        OgreCamera m_OgreCamera;

        // Ogre
        Ogre::Root* m_pOgreRoot;
        Ogre::SceneManager* m_pOgreSceneManager;
    };
}
