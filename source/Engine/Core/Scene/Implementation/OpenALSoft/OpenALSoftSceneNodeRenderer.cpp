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

#include "OpenALSoftSceneNodeRenderer.h"

#include <Core/Scene/IScene.h>

namespace uge
{
    OpenALSoftSceneNodeRenderer::OpenALSoftSceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties, IAudioBuffer* pAudioBuffer)
        : ISceneNodeRenderer(pSceneNodeProperties), m_pSceneNodeProperties(pSceneNodeProperties),
          m_pAudioBuffer(pAudioBuffer)
    {
        assert(pAudioBuffer != nullptr && "Invalid audio buffer!");
    }

    OpenALSoftSceneNodeRenderer::~OpenALSoftSceneNodeRenderer()
    {
        m_pAudioBuffer = nullptr;
    }

    bool OpenALSoftSceneNodeRenderer::vPreRender()
    {
        //const Matrix4& transform = m_pSceneNodeProperties->GetToWorld();
        const Matrix4& transform = m_pSceneNodeProperties->GetWorldTransform();
        m_pAudioBuffer->vSetPosition(transform.GetPositionVector());

        return true;
    }

    bool OpenALSoftSceneNodeRenderer::vRender()
    {
        if (!m_pAudioBuffer->vIsPlaying())
        {
            ActorSharedPointer pActor = m_pSceneNodeProperties->GetActor().lock();

            std::shared_ptr<Component::OpenALSoftAudioComponent> pAudioComponent =
                pActor->GetComponent<Component::OpenALSoftAudioComponent>(Component::OpenALSoftAudioComponent::g_ComponentName).lock();
            m_pAudioBuffer->vPlay(pAudioComponent->GetVolume(), pAudioComponent->GetLooping());
        }

        // TODO: print this to a log.
        //Vector3 pos = m_pAudioBuffer->vGetPosition();
        //printf("[OpenALSoft] %s: (%f, %f, %f)\n", m_pSceneNodeProperties->GetName().c_str(), pos.x, pos.y, pos.z);

        return true;
    }

    bool OpenALSoftSceneNodeRenderer::vPostRender()
    {
        return true;
    }

    bool OpenALSoftSceneNodeRenderer::vIsVisible() const
    {
        // TODO: add sound occlusion.

        return true;
    }

    bool OpenALSoftSceneNodeRenderer::vAddChild(ISceneNodeSharedPointer pChildNode)
    {
        return true;
    }

    bool OpenALSoftSceneNodeRenderer::vRemoveChild(ActorID actorID)
    {
        return true;
    }

}
