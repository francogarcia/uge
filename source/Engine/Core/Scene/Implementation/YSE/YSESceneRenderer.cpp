/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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
  */

#include "GameEngineStd.h"

#include "YSESceneRenderer.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Resource/ResourceCache.h>

#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>
#include <IO/Output/Audio/Implementation/YSE/YSEAudioResource.h>

namespace uge
{

    YSESceneRenderer::YSESceneRenderer(IAudioSharedPointer pAudioRenderer,
                                                     ResourceCache& resourceCache)
        : IAudioSceneRenderer(pAudioRenderer),
          m_pAudioRenderer(nullptr),
          m_ResourceCache(resourceCache),
          m_pScene(nullptr)
    {
        m_pAudioRenderer = std::dynamic_pointer_cast<YSEAudio>(pAudioRenderer);

        RegisterResourceLoaders();
    }

    YSESceneRenderer::~YSESceneRenderer()
    {
        m_SceneNodes.clear();

        m_pAudioRenderer = nullptr;
    }

    void YSESceneRenderer::CreateScene(const IScene* const pScene)
    {
        assert(pScene != nullptr && "Invalid scene!");

        m_pScene = pScene;

        // Parse all scene nodes and create the ogre scene nodes.
        SceneNodeSharedPointer pRootNode = std::dynamic_pointer_cast<SceneNode>(pScene->vGetRootSceneNode());
        AddSceneNodeToScene(pRootNode);
    }

    const IScene* const YSESceneRenderer::GetScene() const
    {
        return m_pScene;
    }

    bool YSESceneRenderer::vOnUpdate(const unsigned long timeElapsed)
    {
        for (auto& sceneNodeIterator : m_SceneNodes)
        {
            YSESceneNodeRenderer& sceneNode = sceneNodeIterator.second;
            sceneNode.vPreRender();
        }

        return true;
    }

    bool YSESceneRenderer::vOnRender()
    {
        for (auto& sceneNodeIterator : m_SceneNodes)
        {
            YSESceneNodeRenderer& sceneNode = sceneNodeIterator.second;
            sceneNode.vRender();
            sceneNode.vPostRender();
        }

        return true;
    }

    bool YSESceneRenderer::vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        SceneNodeSharedPointer pAudioSceneNode = std::dynamic_pointer_cast<SceneNode>(pSceneNode);
        if (pAudioSceneNode != nullptr)
        {
            AddSceneNodeToScene(pAudioSceneNode);
        }

        return true;
    }

    bool YSESceneRenderer::vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        auto& nodeIterator = m_SceneNodes.find(actorID);
        if (nodeIterator == m_SceneNodes.end())
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

        // Stop the sound.
        YSESceneNodeRenderer& audioSceneNode = nodeIterator->second;
        audioSceneNode.m_pAudioBuffer->vStop();

        // Remove the node.
        m_SceneNodes.erase(nodeIterator);

        return true;
    }

    void YSESceneRenderer::vOnSetCamera(ICameraNodeSharedPointer pCamera)
    {
        m_Camera.Init(pCamera);
    }

    void YSESceneRenderer::vOnUpdateCamera(ICameraNodeSharedPointer pCamera)
    {
        m_Camera.vOnUpdate(pCamera);
    }

    IAudioSharedPointer YSESceneRenderer::vGetAudioRenderer()
    {
        return m_pAudioRenderer;
    }

    void YSESceneRenderer::RegisterResourceLoaders()
    {
        // OGG loader.
        m_ResourceCache.RegisterLoader(std::shared_ptr<IResourceLoader>(LIB_NEW YSEOggResourceLoader));
        // WAVE loader.
        m_ResourceCache.RegisterLoader(std::shared_ptr<IResourceLoader>(LIB_NEW YSEWaveResourceLoader));
    }

    void YSESceneRenderer::AddSceneNodeToScene(SceneNodeSharedPointer pSceneNode)
    {
        ActorID actorID = pSceneNode->vGetNodeProperties()->GetActorID();
        // FIXME: Some nodes might not have a render component.
        if (actorID == Actor::NULL_ACTOR_ID)
        {
            return;
        }

        ActorSharedPointer pActor = pSceneNode->vGetNodeProperties()->GetActor().lock();
        if(pActor->GetComponent<Component::YSEAudioComponent>(Component::YSEAudioComponent::g_ComponentName).expired())
        {
            return;
        }

        // Add to the renderer map.
        auto& newNodeIterator = m_SceneNodes.insert(std::pair<ActorID, YSESceneNodeRenderer>(actorID,
                                                                                                    CreateSceneNode(pSceneNode->vGetNodeProperties())));
        assert((actorID == Actor::NULL_ACTOR_ID || newNodeIterator.second) && "This node already exists in the scene!");

        // Add the node's children (if any) to the scene.
        const SceneNodeList& nodeChildren = pSceneNode->vGetChildren();
        for (auto& childSceneNode : nodeChildren)
        {
            AddSceneNodeToScene(std::dynamic_pointer_cast<SceneNode>(childSceneNode));
        }
    }

    YSESceneNodeRenderer YSESceneRenderer::CreateSceneNode(const SceneNodeProperties* const pSceneNodeProperties)
    {
        ActorSharedPointer pActor = pSceneNodeProperties->GetActor().lock();

        Component::YSEAudioComponentSharedPointer pRenderComponent =
            pActor->GetComponent<Component::YSEAudioComponent>(Component::YSEAudioComponent::g_ComponentName).lock();

        Resource resourceFile(pRenderComponent->GetFileName());
        ResourceHandleSharedPointer pResource = m_ResourceCache.GetHandle(&resourceFile);
        uge::IAudioBuffer* pAudioBuffer = m_pAudioRenderer->vInitAudioBuffer(pResource);        
        pAudioBuffer->vSetVolume(pRenderComponent->GetVolume());
        pAudioBuffer->vSetProgress(pRenderComponent->GetInitialProgress());

        return YSESceneNodeRenderer(pSceneNodeProperties, pAudioBuffer);
    }
}
