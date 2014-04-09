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

#pragma once

#include <Core/Scene/IScene.h>

#include <IO/Output/IOutput.h>
#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Graphics/Graphics.h>

#include "ISceneNode.h"

namespace uge
{
    typedef unsigned int SceneRendererID;

    class ISceneRenderer;
    typedef std::shared_ptr<ISceneRenderer> ISceneRendererSharedPointer;
    typedef std::vector<ISceneRendererSharedPointer> ISceneRendererList;
    typedef std::map<SceneRendererID, ISceneRendererSharedPointer> ISceneRendererMap;

    class IAudioSceneRenderer;
    typedef std::shared_ptr<IAudioSceneRenderer> IAudioSceneRendererSharedPointer;

    class IGraphicalSceneRenderer;
    typedef std::shared_ptr<IGraphicalSceneRenderer> IGraphicalSceneRendererSharedPointer;

    class ISceneRenderer
    {
    public:
        ISceneRenderer();
        virtual ~ISceneRenderer();

        virtual void CreateScene(const IScene* const pScene) = 0;
        virtual const IScene* const GetScene() const = 0;

        virtual bool vOnUpdate(const unsigned long timeElapsed) = 0;
        virtual bool vOnRender() = 0;

        virtual bool vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;
        virtual bool vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;

        virtual void vOnSetCamera(ICameraNodeSharedPointer pCamera) = 0;
        virtual void vOnUpdateCamera(ICameraNodeSharedPointer pCamera) = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

    class IAudioSceneRenderer : public ISceneRenderer
    {
    public:
        IAudioSceneRenderer(IAudioSharedPointer pAudioRenderer);
        virtual ~IAudioSceneRenderer();

        virtual void CreateScene(const IScene* const pScene) = 0;
        virtual const IScene* const GetScene() const = 0;

        virtual bool vOnUpdate(const unsigned long timeElapsed) = 0;
        virtual bool vOnRender() = 0;

        virtual bool vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;
        virtual bool vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;

        virtual void vOnSetCamera(ICameraNodeSharedPointer pCamera) = 0;
        virtual void vOnUpdateCamera(ICameraNodeSharedPointer pCamera) = 0;

        virtual IAudioSharedPointer vGetAudioRenderer() = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

    class IGraphicalSceneRenderer : public ISceneRenderer
    {
    public:
        IGraphicalSceneRenderer(IGraphicsSharedPointer pGraphicalRenderer);
        virtual ~IGraphicalSceneRenderer();

        virtual void CreateScene(const IScene* const pScene) = 0;
        virtual const IScene* const GetScene() const = 0;

        virtual bool vOnUpdate(const unsigned long timeElapsed) = 0;
        virtual bool vOnRender() = 0;

        virtual bool vOnAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;
        virtual bool vOnRemoveChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode) = 0;

        virtual void vOnSetCamera(ICameraNodeSharedPointer pCamera) = 0;
        virtual void vOnUpdateCamera(ICameraNodeSharedPointer pCamera) = 0;

        virtual IGraphicsSharedPointer vGetGraphicalRenderer() = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

}
