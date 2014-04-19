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

#include <Core/EntityComponent/Component/Implementation/YSEAudioComponent.h>
#include <Core/Scene/ISceneNodeRenderer.h>
#include <Core/Scene/SceneNode.h>

#include <IO/Output/Audio/Implementation/YSE/YSEAudio.h>

namespace uge
{

    class YSESceneNodeRenderer;
    typedef std::shared_ptr<YSESceneNodeRenderer> YSESceneNodeSharedPointer;

    class YSESceneRenderer;

    class YSESceneNodeRenderer : public ISceneNodeRenderer
    {
        friend class YSESceneRenderer;

    public:
        YSESceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties, IAudioBuffer* pAudioBuffer);
        virtual ~YSESceneNodeRenderer();

        virtual bool vPreRender() override;
        virtual bool vRender() override;
        virtual bool vPostRender() override;

        virtual bool vIsVisible() const override;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) override;
        virtual bool vRemoveChild(ActorID actorID) override;

    protected:
        const SceneNodeProperties* const m_pSceneNodeProperties;

        IAudioBuffer* m_pAudioBuffer;
    };

}
