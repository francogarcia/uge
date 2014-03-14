#include "GameEngineStd.h"

#include "YSESceneNodeRenderer.h"

#include <Core/Scene/IScene.h>

namespace uge
{
    YSESceneNodeRenderer::YSESceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties, IAudioBuffer* pAudioBuffer)
        : ISceneNodeRenderer(pSceneNodeProperties), m_pSceneNodeProperties(pSceneNodeProperties),
          m_pAudioBuffer(pAudioBuffer)
    {
        assert(pAudioBuffer != nullptr && "Invalid audio buffer!");
    }

    YSESceneNodeRenderer::~YSESceneNodeRenderer()
    {
        m_pAudioBuffer = nullptr;
    }

    bool YSESceneNodeRenderer::vPreRender()
    {
        //const Matrix4& transform = m_pSceneNodeProperties->GetToWorld();
        const Matrix4& transform = m_pSceneNodeProperties->GetWorldTransform();
        m_pAudioBuffer->vSetPosition(transform.GetPositionVector());

        return true;
    }

    bool YSESceneNodeRenderer::vRender()
    {
        if (!m_pAudioBuffer->vIsPlaying())
        {
            ActorSharedPointer pActor = m_pSceneNodeProperties->GetActor().lock();

            std::shared_ptr<Component::YSEAudioComponent> pAudioComponent =
                pActor->GetComponent<Component::YSEAudioComponent>(Component::YSEAudioComponent::g_ComponentName).lock();
            m_pAudioBuffer->vPlay(pAudioComponent->GetVolume(), pAudioComponent->GetLooping());
        }

        // TODO: print this to a log.
        //Vector3 pos = m_pAudioBuffer->vGetPosition();
        //printf("[YSE] %s: (%f, %f, %f)\n", m_pSceneNodeProperties->GetName().c_str(), pos.x, pos.y, pos.z);

        return true;
    }

    bool YSESceneNodeRenderer::vPostRender()
    {
        return true;
    }

    bool YSESceneNodeRenderer::vIsVisible() const
    {
        // TODO: add sound occlusion.

        return true;
    }

    bool YSESceneNodeRenderer::vAddChild(ISceneNodeSharedPointer pChildNode)
    {
        return true;
    }

    bool YSESceneNodeRenderer::vRemoveChild(ActorID actorID)
    {
        return true;
    }

}
