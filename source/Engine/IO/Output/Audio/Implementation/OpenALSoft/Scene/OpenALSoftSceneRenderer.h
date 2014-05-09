/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
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

#include <IO/Output/Audio/Implementation/OpenALSoft/OpenALSoftAudio.h>
#include <IO/Output/Scene/ISceneRenderer.h>

#include "OpenALSoftCamera.h"
#include "OpenALSoftSceneNodeRenderer.h"

namespace uge
{
    class OpenALSoftSceneRenderer;
    typedef std::shared_ptr<OpenALSoftSceneRenderer> OpenALSoftSceneRendererSharedPointer;

    class ResourceCache;

    class OpenALSoftSceneRenderer : public IAudioSceneRenderer
    {
    public:
        OpenALSoftSceneRenderer();
        ~OpenALSoftSceneRenderer();

        virtual bool vInit(IOutputSharedPointer pSystem, ResourceCache* pResourceCache) override;

        virtual void vCreateScene(const IScene* const pScene) override;
        virtual const IScene* const vGetScene() const override;

        virtual bool vOnUpdate(const unsigned long timeElapsed) override;
        virtual bool vOnRender() override;

        virtual bool vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;
        virtual bool vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) override;

        virtual void vOnSetCamera(ICameraNodeSharedPointer pCamera) override;
        virtual void vOnUpdateCamera(ICameraNodeSharedPointer pCamera) override;

        virtual IAudioSharedPointer vGetAudioRenderer() override;

        virtual OutputType vGetOutputType() const override
        {
            return OutputType::Aural;
        }

    private:
        // Internal use.
        void RegisterResourceLoaders();

        void AddSceneNodeToScene(SceneNodeSharedPointer pSceneNode);
        OpenALSoftSceneNodeRenderer CreateSceneNode(const SceneNodeProperties* const pSceneNodeProperties);

    private:
        std::shared_ptr<OpenALSoftAudio> m_pAudioRenderer;
        ResourceCache* m_pResourceCache;

        const IScene* m_pScene;
        std::map<ActorID, OpenALSoftSceneNodeRenderer> m_SceneNodes;

        OpenALSoftCamera m_Camera;
    };
}
