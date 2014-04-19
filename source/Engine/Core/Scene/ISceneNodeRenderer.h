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
 */

#pragma once

#include "IScene.h"
#include "SceneNodeProperties.h"

namespace uge
{
    class ISceneNodeRenderer
    {
    public:
        ISceneNodeRenderer(const SceneNodeProperties* const pSceneNodeProperties);
        virtual ~ISceneNodeRenderer();

        virtual bool vPreRender() = 0;
        virtual bool vRender() = 0;
        //virtual bool vRenderChildren(IScene* pScene) = 0;
        virtual bool vPostRender() = 0;

        virtual bool vIsVisible() const = 0;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) = 0;
        virtual bool vRemoveChild(ActorID actorID) = 0;
    };
}
