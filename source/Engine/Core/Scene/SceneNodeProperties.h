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

#include <Core/EntityComponent/Entity/ActorTypes.h>
#include <IO/Output/Graphics/Graphics.h>
#include <Utilities/Math/MathStd.h>

namespace uge
{
    class SceneNode;

    class SceneNodeProperties
    {
        friend class SceneNode;

    protected:
        ActorID m_ActorID;
        ActorWeakPointer m_pActor;
        std::string m_Name;
        Matrix4 m_ToWorld;
        Matrix4 m_FromWorld;
        Matrix4 m_WorldTransform;

        float m_fRadius;

        RenderPass m_RenderPass;

    public:
        SceneNodeProperties();
        ~SceneNodeProperties();

        const Matrix4& GetToWorld() const;
        const Matrix4& GetFromWorld() const;
        const Matrix4& GetWorldTransform() const;

        void Transform(Matrix4* toWorld, Matrix4* fromWorld) const;

        const ActorID GetActorID() const;
        const ActorWeakPointer GetActor() const;
        const std::string& GetName() const;
        const float GetRadius() const;
        const RenderPass GetRenderPass() const;
    };
}
