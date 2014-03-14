#include "GameEngineStd.h"

#include "OpenALSoftSceneRenderer.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Resource/ResourceCache.h>

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudioResource.h>

namespace uge
{

    OpenALSoftSceneRenderer::OpenALSoftSceneRenderer(IAudioSharedPointer pAudioRenderer,
                                                     ResourceCache& resourceCache)
        : IAudioSceneRenderer(pAudioRenderer),
          m_pAudioRenderer(nullptr),
          m_ResourceCache(resourceCache),
          m_pScene(nullptr)
    {
        m_pAudioRenderer = std::dynamic_pointer_cast<OpenALSoftAudio>(pAudioRenderer);

        RegisterResourceLoaders();
    }

    OpenALSoftSceneRenderer::~OpenALSoftSceneRenderer()
    {
        m_SceneNodes.clear();

        m_pAudioRenderer = nullptr;
    }

    void OpenALSoftSceneRenderer::CreateScene(const IScene* const pScene)
    {
        assert(pScene != nullptr && "Invalid scene!");

        m_pScene = pScene;

        // Parse all scene nodes and create the ogre scene nodes.
        SceneNodeSharedPointer pRootNode = std::dynamic_pointer_cast<SceneNode>(pScene->vGetRootSceneNode());
        AddSceneNodeToScene(pRootNode);
    }

    const IScene* const OpenALSoftSceneRenderer::GetScene() const
    {
        return m_pScene;
    }

    bool OpenALSoftSceneRenderer::vOnUpdate(const unsigned long timeElapsed)
    {
        for (auto& sceneNodeIterator : m_SceneNodes)
        {
            OpenALSoftSceneNodeRenderer& sceneNode = sceneNodeIterator.second;
            sceneNode.vPreRender();
        }

        return true;
    }

    bool OpenALSoftSceneRenderer::vOnRender()
    {
        for (auto& sceneNodeIterator : m_SceneNodes)
        {
            OpenALSoftSceneNodeRenderer& sceneNode = sceneNodeIterator.second;
            sceneNode.vRender();
            sceneNode.vPostRender();
        }

        return true;
    }

    bool OpenALSoftSceneRenderer::vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        SceneNodeSharedPointer pAudioSceneNode = std::dynamic_pointer_cast<SceneNode>(pSceneNode);
        if (pAudioSceneNode != nullptr)
        {
            AddSceneNodeToScene(pAudioSceneNode);
        }

        return true;
    }

    bool OpenALSoftSceneRenderer::vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        auto& nodeIterator = m_SceneNodes.find(actorID);
        assert(nodeIterator != m_SceneNodes.end() && "Actor not found!");

        // Remove the child scene nodes, if necessary.
        const SceneNodeList& nodeChildren = pSceneNode->vGetChildren();
        for (auto& childSceneNode : nodeChildren)
        {
            ActorID childActorID = childSceneNode->vGetNodeProperties()->GetActorID();
            vOnRemoveChild(childActorID, childSceneNode);
        }

        // Stop the sound.
        OpenALSoftSceneNodeRenderer& audioSceneNode = nodeIterator->second;
        audioSceneNode.m_pAudioBuffer->vStop();

        // Remove the node.
        m_SceneNodes.erase(nodeIterator);

        return true;
    }

    void OpenALSoftSceneRenderer::vOnSetCamera(ICameraNodeSharedPointer pCamera)
    {
        m_Camera.Init(pCamera);
    }

    void OpenALSoftSceneRenderer::vOnUpdateCamera(ICameraNodeSharedPointer pCamera)
    {
        m_Camera.vOnUpdate(pCamera);
    }

    IAudioSharedPointer OpenALSoftSceneRenderer::vGetAudioRenderer()
    {
        return m_pAudioRenderer;
    }

    void OpenALSoftSceneRenderer::RegisterResourceLoaders()
    {
        // OGG loader.
        m_ResourceCache.RegisterLoader(std::shared_ptr<IResourceLoader>(LIB_NEW OpenALSoftOggResourceLoader));
        // WAVE loader.
        m_ResourceCache.RegisterLoader(std::shared_ptr<IResourceLoader>(LIB_NEW OpenALSoftWaveResourceLoader));
    }

    void OpenALSoftSceneRenderer::AddSceneNodeToScene(SceneNodeSharedPointer pSceneNode)
    {
        ActorID actorID = pSceneNode->vGetNodeProperties()->GetActorID();
        // FIXME: Some nodes might not have a render component.
        if (actorID == Actor::NULL_ACTOR_ID)
        {
            return;
        }
        
        ActorSharedPointer pActor = pSceneNode->vGetNodeProperties()->GetActor().lock();
        if(pActor->GetComponent<Component::OpenALSoftAudioComponent>(Component::OpenALSoftAudioComponent::g_ComponentName).expired())
        {
            return;
        }

        // Add to the renderer map.
        auto& newNodeIterator = m_SceneNodes.insert(std::pair<ActorID, OpenALSoftSceneNodeRenderer>(actorID,
                                                                                                    CreateSceneNode(pSceneNode->vGetNodeProperties())));
        assert((actorID == Actor::NULL_ACTOR_ID || newNodeIterator.second) && "This node already exists in the scene!");

        // Add the node's children (if any) to the scene.
        const SceneNodeList& nodeChildren = pSceneNode->vGetChildren();
        for (auto& childSceneNode : nodeChildren)
        {
            AddSceneNodeToScene(std::dynamic_pointer_cast<SceneNode>(childSceneNode));
        }
    }

    OpenALSoftSceneNodeRenderer OpenALSoftSceneRenderer::CreateSceneNode(const SceneNodeProperties* const pSceneNodeProperties)
    {
        ActorSharedPointer pActor = pSceneNodeProperties->GetActor().lock();

        Component::OpenALSoftAudioComponentSharedPointer pRenderComponent =
            pActor->GetComponent<Component::OpenALSoftAudioComponent>(Component::OpenALSoftAudioComponent::g_ComponentName).lock();

        Resource resourceFile(pRenderComponent->GetFileName());
        ResourceHandleSharedPointer pResource = m_ResourceCache.GetHandle(&resourceFile);
        uge::IAudioBuffer* pAudioBuffer = m_pAudioRenderer->vInitAudioBuffer(pResource);        
        pAudioBuffer->vSetVolume(pRenderComponent->GetVolume());
        pAudioBuffer->vSetProgress(pRenderComponent->GetInitialProgress());

        return OpenALSoftSceneNodeRenderer(pSceneNodeProperties, pAudioBuffer);
    }
}
