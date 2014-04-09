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

#include "SceneNodeProperties.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
        SceneNodeProperties::SceneNodeProperties()
            : m_ActorID(Actor::NULL_ACTOR_ID),
              m_fRadius(0.0f),
              m_RenderPass(RenderPass::RenderPass0)
        {

        }

        SceneNodeProperties::~SceneNodeProperties()
        {

        }

        const Matrix4& SceneNodeProperties::GetToWorld() const
        {
            return m_ToWorld;
        }

        const Matrix4& SceneNodeProperties::GetFromWorld() const
        {
            return m_FromWorld;
        }

        const Matrix4& SceneNodeProperties::GetWorldTransform() const
        {
            return m_WorldTransform;
        }

        void SceneNodeProperties::Transform(Matrix4* toWorld, Matrix4* fromWorld) const
        {
            if (toWorld != nullptr)
            {
                *toWorld = m_ToWorld;
            }

            if (fromWorld != nullptr)
            {
                *fromWorld = m_FromWorld;
            }
        }

        const ActorID SceneNodeProperties::GetActorID() const
        {
            return m_ActorID;
        }

        const ActorWeakPointer SceneNodeProperties::GetActor() const
        {
            return m_pActor;
        }

        const std::string& SceneNodeProperties::GetName() const
        {
            return m_Name;
        }

        const float SceneNodeProperties::GetRadius() const
        {
            return m_fRadius;
        }

        const RenderPass SceneNodeProperties::GetRenderPass() const
        {
            return m_RenderPass;
        }
};
