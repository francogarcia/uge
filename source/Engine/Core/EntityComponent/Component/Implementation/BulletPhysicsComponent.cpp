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

#include "BulletPhysicsComponent.h"

#include <Core/EntityComponent/Component/CollidableComponent.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Utilities/Debug/Logger.h>

namespace uge
{

    namespace Component
    {

        const float kDEFAULT_MAX_VELOCITY = 7.5f;
        const float kDEFAULT_MAX_ANGULAR_VELOCITY = 1.2f;

        const char* BulletPhysicsComponent::g_ComponentName = "BulletPhysicsComponent";

        BulletPhysicsComponent::BulletPhysicsComponent()
            : m_fAcceleration(0.0f),
              m_fAngularAcceleration(0.0f),
              m_fMaxVelocity(kDEFAULT_MAX_VELOCITY),
              m_fMaxAngularVelocity(kDEFAULT_MAX_ANGULAR_VELOCITY),
              m_LinearFactor(1.0f, 1.0f, 1.0f),
              m_AngularFactor(1.0f, 1.0f, 1.0f),
              m_RigidBodyLocalPosition(0.0f, 0.0f, 0.0f),
              m_RigidBodyLocalOrientation(0.0f, 0.0f, 0.0f),
              m_RigidBodyLocalScale(1.0f, 1.0f, 1.0f),
              m_pPhysics()
        {

        }

        BulletPhysicsComponent::~BulletPhysicsComponent()
        {
            if (m_pPhysics != nullptr)
            {
                m_pPhysics->vRemoveActor(GetOwner()->GetActorID());
            }
            else
            {
                // TODO : log warning here - actor was never added to the scene!
            }
            m_pPhysics = nullptr;
        }

        bool BulletPhysicsComponent::vInit(XMLElement* pInitXMLData)
        {
            assert(pInitXMLData != nullptr && "Invalid initialization data!");

            XMLElement xmlElement = pInitXMLData->GetFirstChildElement("LinearFactor");
            if (xmlElement.IsGood())
            {
                xmlElement.GetFloatAttribute("x", &m_LinearFactor.x);
                xmlElement.GetFloatAttribute("y", &m_LinearFactor.y);
                xmlElement.GetFloatAttribute("z", &m_LinearFactor.z);
            }

            xmlElement = pInitXMLData->GetFirstChildElement("AngularFactor");
            if (xmlElement.IsGood())
            {
                xmlElement.GetFloatAttribute("x", &m_AngularFactor.x);
                xmlElement.GetFloatAttribute("y", &m_AngularFactor.y);
                xmlElement.GetFloatAttribute("z", &m_AngularFactor.z);
            }

            xmlElement = pInitXMLData->GetFirstChildElement("MaxVelocity");
            if (xmlElement.IsGood())
            {
                xmlElement.GetFloatAttribute("v", &m_fMaxVelocity);
            }

            xmlElement = pInitXMLData->GetFirstChildElement("MaxAngularVelocity");
            if (xmlElement.IsGood())
            {
                xmlElement.GetFloatAttribute("v", &m_fMaxAngularVelocity);
            }

            //xmlElement = pInitXMLData->GetFirstChildElement("MaxAcceleration");
            //if (xmlElement.IsGood())
            //{
            //    xmlElement.GetFloatAttribute("a", &m_fMaxAcceleration);
            //}

            return true;
        }

        void BulletPhysicsComponent::vPostInit()
        {
            vBuildRigidBodyTransform();
        }

        void BulletPhysicsComponent::vUpdate(const unsigned long dt)
        {

        }

        void BulletPhysicsComponent::vOnChange()
        {

        }

        const std::string BulletPhysicsComponent::vGetName() const
        {
            return g_ComponentName;
        }

        void BulletPhysicsComponent::vApplyForce(const Vector3& direction, const float fNewtons)
        {
            m_pPhysics->vApplyForce(GetOwner()->GetActorID(), direction, fNewtons);
        }

        void BulletPhysicsComponent::vApplyTorque(const Vector3& direction, const float fNewtons)
        {
            m_pPhysics->vApplyTorque(GetOwner()->GetActorID(), direction, fNewtons);
        }

        bool BulletPhysicsComponent::vKinematicMove(const Matrix4& transform)
        {
            return m_pPhysics->vKinematicMove(GetOwner()->GetActorID(), transform);
        }

        void BulletPhysicsComponent::vApplyAcceleration(float fAcceleration)
        {
            m_fAcceleration = fAcceleration;
        }

        void BulletPhysicsComponent::vRemoveAcceleration()
        {
            m_fAcceleration = 0.0f;
        }

        void BulletPhysicsComponent::vApplyAngularAcceleration(float fAcceleration)
        {
            m_fAngularAcceleration = fAcceleration;
        }

        void BulletPhysicsComponent::vRemoveAngularAcceleration()
        {
            m_fAngularAcceleration = 0.0f;
        }

        float BulletPhysicsComponent::vGetMaxVelocity() const
        {
            return m_fMaxVelocity;
        }

        const Vector3 BulletPhysicsComponent::vGetVelocity() const
        {
            return m_pPhysics->vGetVelocity(GetOwner()->GetActorID());
        }

        void BulletPhysicsComponent::vSetVelocity(const Vector3& velocity)
        {
            m_pPhysics->vSetVelocity(GetOwner()->GetActorID(), velocity);
        }

        void BulletPhysicsComponent::vRotateY(float fAngle)
        {
            uge::Component::TransformableComponentSharedPointer pTransformComponent =
                GetOwner()->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            assert(pTransformComponent != nullptr && "Actor must have a transform component!");

            const Matrix4& transform = pTransformComponent->GetTransform();
            Vector3 position = transform.GetPositionVector();

            Matrix4 rotationMatrix;
            rotationMatrix.MakeRotationMatrix(Vector3(0.0f, 1.0f, 0.0f), fAngle);

            vKinematicMove(rotationMatrix);
        }

        void BulletPhysicsComponent::vSetPosition(const Vector3& position)
        {
            uge::Component::TransformableComponentSharedPointer pTransformComponent =
                GetOwner()->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            assert(pTransformComponent != nullptr && "Actor must have a transform component!");

            Matrix4 transform = pTransformComponent->GetTransform();
            transform.SetPositionFromVector(position);

            vKinematicMove(transform);
        }

        void BulletPhysicsComponent::vStop()
        {
            m_pPhysics->vStopActor(GetOwner()->GetActorID());
        }

        void BulletPhysicsComponent::SetPhysicsSystem(IPhysics* pPhysics)
        {
            assert(pPhysics != nullptr && "Invalid physics system!");

            m_pPhysics = pPhysics;
        }

        void BulletPhysicsComponent::vCreateShape()
        {
            if (GetOwner() != nullptr)
            {
                ActorSharedPointer pActor = GetOwner();
                ActorID ownerID = pActor->GetActorID();

                uge::Component::CollidableComponentSharedPointer pCollisionComponent =
                    pActor->GetComponent<uge::Component::CollidableComponent>(uge::Component::CollidableComponent::g_ComponentName).lock();
                assert(pCollisionComponent != nullptr && "Actor must have a transform component!");

                CollidableComponent::Shape collisionShape = pCollisionComponent->GetShape();
                std::string density = pCollisionComponent->GetDensity();
                std::string material = pCollisionComponent->GetMaterial();
                if (collisionShape == CollidableComponent::Shape::Sphere)
                {
                    m_pPhysics->vAddSphere(m_RigidBodyLocalScale.x, GetOwner(), density, material);
                    m_pPhysics->vSetLinearFactor(ownerID, m_LinearFactor);
                    m_pPhysics->vSetAngularFactor(ownerID, m_AngularFactor);
                }
                else if (collisionShape == CollidableComponent::Shape::Box)
                {
                    m_pPhysics->vAddBox(m_RigidBodyLocalScale, GetOwner(), density, material);
                    m_pPhysics->vSetLinearFactor(ownerID, m_LinearFactor);
                    m_pPhysics->vSetAngularFactor(ownerID, m_AngularFactor);
                }
                else if (collisionShape == CollidableComponent::Shape::Plane)
                {
                    CollidableComponent::ShapeData data = pCollisionComponent->GetShapeData();
                    Vector3 planeNormal(data[0], data[1], data[2]); // X, Y, Z
                    float fPlaneConstant = data[3];
                    m_pPhysics->vAddPlane(planeNormal, fPlaneConstant, GetOwner(), material);
                }
                else
                {
                    assert(0 && "Invalid shape!");
                }
            }
        }

        void BulletPhysicsComponent::vBuildRigidBodyTransform()
        {
            // TODO: also create a transform for the center of mass.
            uge::Component::CollidableComponentSharedPointer pCollisionComponent =
                GetOwner()->GetComponent<uge::Component::CollidableComponent>(uge::Component::CollidableComponent::g_ComponentName).lock();
            assert(pCollisionComponent != nullptr && "Actor must have a transform component!");
            CollidableComponent::Shape shape = pCollisionComponent->GetShape();

            if (shape == CollidableComponent::Shape::Plane)
            {
                // Plane does not need a rigid body transform.

                return;
            }

            uge::Component::TransformableComponentSharedPointer pTransformComponent =
                GetOwner()->GetComponent<uge::Component::TransformableComponent>(uge::Component::TransformableComponent::g_ComponentName).lock();
            assert(pTransformComponent != nullptr && "Actor must have a transform component!");

            m_RigidBodyLocalPosition = pTransformComponent->GetPosition();
            m_RigidBodyLocalOrientation = pTransformComponent->GetRotationVector();
            m_RigidBodyLocalScale = pTransformComponent->GetScale();

            // Update the scale with the shape's own size.
            if (shape == CollidableComponent::Shape::Box)
            {
                CollidableComponent::ShapeData data = pCollisionComponent->GetShapeData();
                m_RigidBodyLocalScale.x *= data[0]; // X
                m_RigidBodyLocalScale.y *= data[1]; // Y
                m_RigidBodyLocalScale.z *= data[2]; // Z
            }
            else if (shape == CollidableComponent::Shape::Sphere)
            {
                CollidableComponent::ShapeData data = pCollisionComponent->GetShapeData();
                m_RigidBodyLocalScale.x *= data[0]; // Radius.
            }
        }

    }

}
