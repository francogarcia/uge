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

#include "GameEngineStd.h"

#include "OgreSceneRenderer.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Resource/ResourceCache.h>
#include <Utilities/Math/Conversion/OgreMathConversion.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{
    OgreSceneRenderer::OgreSceneRenderer()
        : m_pGraphicalRenderer(nullptr),
          m_pResourceCache(nullptr),
          m_pScene(nullptr),
          m_pOgreRoot(nullptr), m_pOgreSceneManager(nullptr)
    {
;
    }

    OgreSceneRenderer::~OgreSceneRenderer()
    {
        m_OgreSceneNodes.clear();

        m_pOgreSceneManager = nullptr;
        m_pOgreRoot = nullptr;
    }

    bool OgreSceneRenderer::vInit(IOutputSharedPointer pSystem, ResourceCache* pResourceCache)
    {
        m_pResourceCache = pResourceCache;

        m_pGraphicalRenderer = std::dynamic_pointer_cast<OgreGraphics>(pSystem);
        m_pOgreRoot = m_pGraphicalRenderer->GetOgreRoot();

        m_pOgreSceneManager = m_pOgreRoot->createSceneManager(Ogre::ST_GENERIC);

        // FIXME : refactor and remove this.
        Load();

        return true;
    }

    void OgreSceneRenderer::vCreateScene(const IScene* const pScene)
    {
        assert(pScene != nullptr && "Invalid scene!");

        m_pScene = pScene;

        // Parse all scene nodes and create the ogre scene nodes.
        SceneNodeSharedPointer pRootNode = std::dynamic_pointer_cast<SceneNode>(pScene->vGetRootSceneNode());
        AddSceneNodeToScene(pRootNode, m_pOgreSceneManager->getRootSceneNode());
    }

    const IScene* const OgreSceneRenderer::vGetScene() const
    {
        return m_pScene;
    }

    bool OgreSceneRenderer::vOnUpdate(const unsigned long timeElapsed)
    {
        // Set transform.
        for (auto& ogreSceneNodeIterator : m_OgreSceneNodes)
        {
            OgreSceneNodeRenderer& ogreSceneNode = ogreSceneNodeIterator.second;
            ogreSceneNode.vPreRender();

            //Ogre::SceneNode* pSceneNode = ogreSceneNode.m_pOgreSceneNode;
            //const SceneNodeProperties* const pSceneNodeProperties = ogreSceneNode.m_pSceneNodeProperties;
            //SetOgreSceneNodePosition(pSceneNode, pSceneNodeProperties);
        }

        return true;
    }

    bool OgreSceneRenderer::vOnRender()
    {
        // For debugging purposes only.
        for (auto& ogreSceneNodeIterator : m_OgreSceneNodes)
        {
            OgreSceneNodeRenderer& ogreSceneNode = ogreSceneNodeIterator.second;
            ogreSceneNode.vRender();
        }

        // Let Ogre to handle the rendering.
        return m_pOgreRoot->renderOneFrame();
    }

    bool OgreSceneRenderer::vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        SceneNodeSharedPointer pCastSceneNode = std::dynamic_pointer_cast<SceneNode>(pSceneNode);
        AddSceneNodeToScene(pCastSceneNode, m_pOgreSceneManager->getRootSceneNode());

        return true;
    }

    bool OgreSceneRenderer::vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        auto& nodeIterator = m_OgreSceneNodes.find(actorID);
        if (nodeIterator == m_OgreSceneNodes.end())
        {
            // Actor does not have the component.
            //assert(nodeIterator != m_SceneNodes.end() && "Actor not found!");

            return true;
        }

        // Remove the child scene nodes, if necessary.
        const SceneNodeList& nodeChildren = pSceneNode->vGetChildren();
        for (auto& childSceneNode : nodeChildren)
        {
            ActorID childActorID = childSceneNode->vGetNodeProperties()->GetActorID();
            vOnRemoveChild(childActorID, childSceneNode);
        }

        // Remove the node.
        RemoveOgreSceneNode(&nodeIterator->second);

        m_OgreSceneNodes.erase(nodeIterator);

        return true;
    }

    void OgreSceneRenderer::vOnSetCamera(ICameraNodeSharedPointer pCamera)
    {
        m_OgreCamera.Init(pCamera, "OgreCamera", m_pOgreSceneManager);

        std::shared_ptr<OgreGraphics> pOgreRenderer = std::dynamic_pointer_cast<OgreGraphics>(m_pGraphicalRenderer);
        pOgreRenderer->AddViewport(m_OgreCamera.GetOgreCamera());
    }

    void OgreSceneRenderer::vOnUpdateCamera(ICameraNodeSharedPointer pCamera)
    {
        m_OgreCamera.vOnUpdate(pCamera);
    }

    IGraphicsSharedPointer OgreSceneRenderer::vGetGraphicalRenderer()
    {
        return m_pGraphicalRenderer;
    }

    void OgreSceneRenderer::Load()
    {
        LoadResources();
        CreateLights();
    }

    void OgreSceneRenderer::CreateLights()
    {
        // Create the lights.
        m_pOgreSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
        Ogre::Light* pLight = m_pOgreSceneManager->createLight("Light");
        pLight->setPosition(20.0f, 80.0f, 50.f);
    }

    void OgreSceneRenderer::LoadResources()
    {
        // Audio and graphics resources.
        Ogre::ResourceGroupManager& resourceGroupManager = Ogre::ResourceGroupManager::getSingleton();
        resourceGroupManager.addResourceLocation("data/graphics/effects/", "FileSystem");
        resourceGroupManager.addResourceLocation("data/graphics/materials/", "FileSystem");
        resourceGroupManager.addResourceLocation("data/graphics/meshes/", "FileSystem");
        resourceGroupManager.addResourceLocation("data/graphics/particles/", "FileSystem");
        resourceGroupManager.addResourceLocation("data/graphics/terrains/", "FileSystem");
        resourceGroupManager.addResourceLocation("data/graphics/textures/", "FileSystem");
        resourceGroupManager.addResourceLocation("data/debug/", "FileSystem");
        resourceGroupManager.initialiseAllResourceGroups();
    }

    void OgreSceneRenderer::AddSceneNodeToScene(SceneNodeSharedPointer pSceneNode, Ogre::SceneNode* pParentNode)
    {
        // FIXME: temporary
        ActorSharedPointer pActor = pSceneNode->vGetNodeProperties()->GetActor().lock();
        if (pSceneNode->vGetNodeProperties()->GetActorID() == Actor::NULL_ACTOR_ID)
        {
            return;
        }

        Component::OgreGraphicalComponentWeakPointer pOgreRenderComponent =
            pActor->GetComponent<Component::OgreGraphicalComponent>(Component::OgreGraphicalComponent::g_ComponentName);

        if (pOgreRenderComponent.expired())
        {
            return;
        }
        // END FIXME


        // TODO: refactor this.

        ActorID actorID = pSceneNode->vGetNodeProperties()->GetActorID();
        // Add to the renderer map.
        auto& newNodeIterator = m_OgreSceneNodes.insert(std::pair<ActorID, OgreSceneNodeRenderer>(actorID,
                                                                                                  OgreSceneNodeRenderer(pSceneNode->vGetNodeProperties())));
        assert((actorID == Actor::NULL_ACTOR_ID || newNodeIterator.second) && "This node already exists in the scene!");
        OgreSceneNodeRenderer& ogreSceneNode = newNodeIterator.first->second;

        // Create Ogre node.
        CreateOgreSceneNode(&ogreSceneNode, pParentNode);

        // Add the node's children (if any) to the scene.
        const SceneNodeList& nodeChildren = pSceneNode->vGetChildren();
        for (auto& childSceneNode : nodeChildren)
        {
            AddSceneNodeToScene(std::dynamic_pointer_cast<SceneNode>(childSceneNode), ogreSceneNode.m_pOgreSceneNode);
        }
    }

    void OgreSceneRenderer::CreateOgreSceneNode(OgreSceneNodeRenderer* pNode, Ogre::SceneNode* pParentNode)
    {
        // TODO: refactor this.

        const SceneNodeProperties* const pSceneNodeProperties = pNode->m_pSceneNodeProperties;
        if (pSceneNodeProperties->GetActorID() == Actor::NULL_ACTOR_ID)
        {
            // FIXME: Some nodes might not have a render component.
            // Currently, the available parent is being set (or the root, if none exists).
            pNode->m_pOgreSceneNode = pParentNode;

            return;
        }

        ActorSharedPointer pActor = pSceneNodeProperties->GetActor().lock();

        Component::OgreGraphicalComponentSharedPointer pOgreRenderComponent =
            pActor->GetComponent<Component::OgreGraphicalComponent>(Component::OgreGraphicalComponent::g_ComponentName).lock();

        Ogre::SceneNode* pSceneNode;
        if (pNode->m_pEntity == nullptr)
        {
            std::string sceneNodeName = UIntToString(pActor->GetActorID()) + std::string(" ") + pSceneNodeProperties->GetName();
            pNode->m_pEntity = m_pOgreSceneManager->createEntity(sceneNodeName,
                                                                 pOgreRenderComponent->GetMeshFileName());
            const std::string& materialName = pOgreRenderComponent->GetMaterialFileName();
            if (materialName != "")
            {
                pNode->m_pEntity->setMaterialName(materialName);
            }

            pSceneNode = pParentNode->createChildSceneNode(sceneNodeName);
            pSceneNode->attachObject(pNode->m_pEntity);
        }
        else
        {
            // If the node was detached from another node, it shall not be created again.
            // The existing node is attached to the new parent.
            pSceneNode = pNode->m_pOgreSceneNode;
            pParentNode->addChild(pSceneNode);
        }

        // Set transform.
        SetOgreSceneNodePosition(pSceneNode, pSceneNodeProperties);

        pNode->m_pOgreSceneNode = pSceneNode;
    }

    void OgreSceneRenderer::SetOgreSceneNodePosition(Ogre::SceneNode* pOgreSceneNode, const SceneNodeProperties* const pSceneNodeProperties)
    {
        const Matrix4& toWorld = pSceneNodeProperties->GetToWorld();
        pOgreSceneNode->setPosition(ToOgreMath(toWorld.GetPositionVector()));
        pOgreSceneNode->setScale(ToOgreMath(toWorld.GetScaleVector()));
        pOgreSceneNode->rotate(ToOgreMath(toWorld.GetRotationQuaternion()));
    }

    void OgreSceneRenderer::RemoveOgreSceneNode(OgreSceneNodeRenderer* pNodeRenderer)
    {
        Ogre::Entity* pEntity = pNodeRenderer->m_pEntity;
        Ogre::SceneNode* pSceneNode = pNodeRenderer->m_pOgreSceneNode;

        m_pOgreSceneManager->destroySceneNode(pSceneNode);
        pEntity = nullptr;
        pSceneNode = nullptr;
    }
}
