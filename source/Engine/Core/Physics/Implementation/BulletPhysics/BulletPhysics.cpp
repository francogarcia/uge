/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "BulletPhysics.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>
#include <Core/EntityComponent/Component/Implementation/BulletPhysicsComponent.h>
#include <Core/Events/DefaultEvents.h>
#include <Core/Resource/XMLResource.h>
#include <Core/Scene/SceneEvents.h>

#include <Utilities/String/StringUtil.h>

#include "ActorMotionState.h"

// FIXME: this should be removed when debug drawer is abstracted.
#include <IO/Output/Graphics/Implementation/Ogre3D/Scene/OgreSceneRenderer.h>

namespace uge
{
    BulletPhysics::BulletPhysics()
        : m_pDynamicsWorld(nullptr),
          m_pBroadphaseInterface(nullptr),
          m_pCollisionDispatcher(nullptr),
          m_pConstraintSolver(nullptr),
          m_pCollisionConfiguration(nullptr),
          m_pDebugDrawer(nullptr)
    {
        RegisterEvents();
    }

    BulletPhysics::~BulletPhysics()
    {
        if (m_pDynamicsWorld != nullptr)
        {
            vDestroy();
        }
    }

    bool BulletPhysics::vInit()
    {
        LoadMaterialData();

        m_pCollisionConfiguration = LIB_NEW btDefaultCollisionConfiguration();
        m_pCollisionDispatcher = LIB_NEW btCollisionDispatcher(m_pCollisionConfiguration);
        m_pBroadphaseInterface = LIB_NEW btDbvtBroadphase();
        m_pConstraintSolver = /*LIB_NEW*/ new btSequentialImpulseConstraintSolver();
        m_pDynamicsWorld = /*LIB_NEW*/ new btDiscreteDynamicsWorld(m_pCollisionDispatcher,
                                                                   m_pBroadphaseInterface,
                                                                   m_pConstraintSolver,
                                                                   m_pCollisionConfiguration);

        if ((m_pCollisionConfiguration == nullptr) ||
            (m_pCollisionDispatcher == nullptr) ||
            (m_pBroadphaseInterface == nullptr) ||
            (m_pConstraintSolver == nullptr) ||
            (m_pDynamicsWorld == nullptr))
        {
            assert(0 && "Error initializing the physics system!");

            return false;
        }


        m_pDynamicsWorld->setInternalTickCallback(BulletInternalTickCallback);
        m_pDynamicsWorld->setWorldUserInfo(this);

#ifdef UGE_EXPERIMENTAL_GHOST
        //btBroadphaseInterface* pSweepBP = new btAxisSweep3();
        m_pDynamicsWorld->getDispatchInfo().m_allowedCcdPenetration = 0.0001f;

        //btGhostPairCallback* pGhostPairCallback = new btGhostPairCallback();
        //m_pDynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
        //m_pBroadphaseInterface->getOverlappingPairCache()->setInternalGhostPairCallback(pGhostPairCallback);
#endif

        RegisterEventDelegates();

        SAFE_DELETE(m_pDebugDrawer);

        return true;
    }

    bool BulletPhysics::vDestroy()
    {
        UnregisterEventDelegates();

        for (int remainingObjects = m_pDynamicsWorld->getNumCollisionObjects() - 1; remainingObjects >= 0; --remainingObjects)
        {
            btCollisionObject* const pObject = m_pDynamicsWorld->getCollisionObjectArray()[remainingObjects];
            RemoveCollisionObject(pObject);
        }

        m_ActorRigidBodies.clear();
        m_RigidBodiesActor.clear();

        SAFE_DELETE(m_pDebugDrawer);

        SAFE_DELETE(m_pDynamicsWorld);
        SAFE_DELETE(m_pConstraintSolver);
        SAFE_DELETE(m_pBroadphaseInterface);
        SAFE_DELETE(m_pCollisionDispatcher);
        SAFE_DELETE(m_pCollisionConfiguration);

        return true;
    }

    bool BulletPhysics::vUpdate(unsigned long timeElapsed)
    {
        const int maxSubsteps = 4;
        // Converts from nanoseconds to seconds.
        float fTimeElapsedSeconds = timeElapsed * 10e-9;

        m_pDynamicsWorld->stepSimulation(fTimeElapsedSeconds, maxSubsteps);

        if (m_pDebugDrawer != nullptr)
        {
            m_pDebugDrawer->Update();
        }

        return true;
    }

    void BulletPhysics::vSyncVisibleScene()
    {
        for (const auto& it : m_ActorRigidBodies)
        {
            const ActorID actorID = it.first;

            const ActorMotionState* const pMotionState = static_cast<ActorMotionState*>(it.second->getMotionState());
            assert(pMotionState != nullptr);

            ActorSharedPointer pActor = m_Actors[actorID].lock();
            assert(pActor != nullptr && "Actor is no longer in the scene!");

            Component::TransformableComponentSharedPointer pTransformComponent =
                pActor->GetComponent<Component::TransformableComponent>(Component::TransformableComponent::g_ComponentName).lock();
            if (pTransformComponent != nullptr)
            {
                if (pTransformComponent->GetTransform() != pMotionState->m_WorldToPositionTransform)
                {
                    const Matrix4& worldToPosition = pMotionState->m_WorldToPositionTransform;

                    //pTransformComponent->SetTransform(pMotionState->m_WorldToPositionTransform);
                    // Bullet ignores the scaling, so we update just the position and rotation of the actor.
                    pTransformComponent->SetPosition(worldToPosition.GetPositionVector());
                    pTransformComponent->SetRotation(worldToPosition.GetRotationQuaternion());

                    std::shared_ptr<EvtData_Move_Actor> pEvent(LIB_NEW EvtData_Move_Actor(actorID, pTransformComponent->GetTransform()));
                    IEventManager::Get()->vQueueEvent(pEvent);

#ifdef UGE_EXPERIMENTAL_GHOST
                    //UpdateGhostIfExists(actorID, pMotionState->m_WorldToPositionTransform);
#endif
                }
            }
        }
    }

    void BulletPhysics::vSetGravity(const Vector3& gravity)
    {
        m_pDynamicsWorld->setGravity(ToBulletMath(gravity));
    }

    void BulletPhysics::vAddActor(ActorWeakPointer pActor)
    {
        ActorSharedPointer pSharedActor = pActor.lock();
        assert(pSharedActor != nullptr && "Invalid actor!");

        Component::BulletPhysicsComponentSharedPointer pPhysicsComponent =
            pSharedActor->GetComponent<Component::BulletPhysicsComponent>(uge::Component::BulletPhysicsComponent::g_ComponentName).lock();
        pPhysicsComponent->SetPhysicsSystem(this);
        pPhysicsComponent->vCreateShape();
    }

    void BulletPhysics::vAddSphere(float fRadius, ActorWeakPointer pActor, const std::string& density, const std::string& material)
    {
        ActorSharedPointer pSharedActor = pActor.lock();
        assert(pSharedActor != nullptr);
        if (pSharedActor == nullptr)
        {
            return;
        }

        btSphereShape* pCollisionShape = new btSphereShape(fRadius);

        float fSpecificGravity = GetSpecificGravity(density);
        float fVolume = (4.0f / 3.0f) * PI * fRadius * fRadius * fRadius;
        btScalar fMass = fVolume * fSpecificGravity;
        bool bIsKinematic = (density == "Kinematic");

        AddShape(pSharedActor, pCollisionShape, fMass, bIsKinematic, material);
        AddActor(pSharedActor->GetActorID(), pActor);
    }

    void BulletPhysics::vAddBox(const Vector3& dimensions, ActorWeakPointer pActor, const std::string& density, const std::string& material)
    {
        ActorSharedPointer pSharedActor = pActor.lock();
        assert(pSharedActor != nullptr);
        if (pSharedActor == nullptr)
        {
            return;
        }

        btBoxShape* pCollisionShape = new btBoxShape(ToBulletMath(dimensions));

        float fSpecificGravity = GetSpecificGravity(density);
        float fVolume = dimensions.x * dimensions.y * dimensions.z;
        btScalar fMass = fVolume * fSpecificGravity;
        bool bIsKinematic = (density == "Kinematic");

        AddShape(pSharedActor, pCollisionShape, fMass, bIsKinematic, material);
        AddActor(pSharedActor->GetActorID(), pActor);
    }

    void BulletPhysics::vAddPlane(const Vector3& normal, float fConstant, ActorWeakPointer pActor, const std::string& material)
    {
        ActorSharedPointer pSharedActor = pActor.lock();
        assert(pSharedActor != nullptr);
        if (pSharedActor == nullptr)
        {
            return;
        }

        btStaticPlaneShape* pCollisionShape = new btStaticPlaneShape(ToBulletMath(normal), fConstant);
        float fMass = 0.0f;

        AddShape(pSharedActor, pCollisionShape, fMass, false, material);
        AddActor(pSharedActor->GetActorID(), pActor);
    }

    void BulletPhysics::vRemoveActor(ActorID actorID)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        if (pRigidBody != nullptr)
        {
            RemoveCollisionObject(pRigidBody);
            m_ActorRigidBodies.erase(actorID);
            m_RigidBodiesActor.erase(pRigidBody);

            pRigidBody = nullptr;
        }
    }

    void BulletPhysics::vCreateTrigger(ActorWeakPointer pActor, const Vector3& position, const float fDimension)
    {
        ActorSharedPointer pSharedActor = pActor.lock();
        assert(pSharedActor != nullptr);

        btBoxShape* pCollisionShape = new btBoxShape(ToBulletMath(position));
        btScalar fMass = 0.0f; // Body cannot be moved.

        Matrix4 transform;
        transform.MakeTranslationMatrix(position);
        ActorMotionState* pMotionState = LIB_NEW ActorMotionState(transform);

        btRigidBody::btRigidBodyConstructionInfo rbInfo(fMass, pMotionState, pCollisionShape, btVector3(0.0f, 0.0f, 0.0f));
        btRigidBody* pRigidBody = new btRigidBody(rbInfo);

        m_pDynamicsWorld->addRigidBody(pRigidBody);

        pRigidBody->setCollisionFlags(pRigidBody->getCollisionFlags() | btRigidBody::CF_NO_CONTACT_RESPONSE);

        ActorID actorID = pSharedActor->GetActorID();
        m_ActorRigidBodies[actorID] = pRigidBody;
        m_RigidBodiesActor[pRigidBody] = actorID;
    }

    void BulletPhysics::vApplyForce(ActorID actorID, const Vector3& direction, const float fNewtons)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        if (pRigidBody != nullptr)
        {
            pRigidBody->setActivationState(DISABLE_DEACTIVATION);

            btVector3 force(direction.x * fNewtons, direction.y * fNewtons, direction.z * fNewtons);
            pRigidBody->applyCentralImpulse(force);
        }
    }

    void BulletPhysics::vApplyTorque(ActorID actorID, const Vector3& direction, const float fNewtons)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        if (pRigidBody != nullptr)
        {
            pRigidBody->setActivationState(DISABLE_DEACTIVATION);

            btVector3 torque(direction.x * fNewtons, direction.y * fNewtons, direction.z * fNewtons);
            pRigidBody->applyTorqueImpulse(torque);
        }
    }

    bool BulletPhysics::vKinematicMove(ActorID actorID, const Matrix4& transform)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        if (pRigidBody != nullptr)
        {
            pRigidBody->setActivationState(DISABLE_DEACTIVATION);

            //btTransform btTransform(ToBulletMath(transform.GetRotationQuaternion()), ToBulletMath(transform.GetPositionVector()));
            //pRigidBody->setWorldTransform(btTransform);
            pRigidBody->setWorldTransform(ToBulletMath(transform));

            std::shared_ptr<EvtData_Move_Actor> pEvent(LIB_NEW EvtData_Move_Actor(actorID, transform));
            IEventManager::Get()->vQueueEvent(pEvent);

            return true;
        }

        return false;
    }

    void BulletPhysics::vRotateY(ActorID actorID, float fAngle, float fTime)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);

        btTransform transform;
        transform.setIdentity();
        transform.getBasis().setEulerYPR(0.0f, fAngle, 0.0f);

        pRigidBody->setCenterOfMassTransform(pRigidBody->getCenterOfMassTransform() * transform);
    }

    float BulletPhysics::vGetOrientationY(ActorID actorID)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);

        const btTransform& transform = pRigidBody->getCenterOfMassTransform();
        btMatrix3x3 rotationMatrix(transform.getBasis());

        btVector3 startVector(0.0f, 0.0f, 1.0f);
        btVector3 endVector = rotationMatrix * startVector;
        endVector.setY(0.0f);

        float fEndLength = endVector.length();
        const float fMINIMUM = 0.001f;
        if (fEndLength < fMINIMUM)
        {
            // Gimbal lock!
            return 0.0f;
        }

        btVector3 cross = startVector.cross(endVector);
        float fSign = (cross.getY() > 0) ? 1.0f : -1.0f;

        return ArcCos((startVector.dot(endVector) / fEndLength) * fSign);
    }

    void BulletPhysics::vStopActor(ActorID actorID)
    {
        vSetVelocity(actorID, Vector3(0.0f, 0.0f, 0.0f));
    }

    const Vector3 BulletPhysics::vGetVelocity(ActorID actorID)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return Vector3();
        }

        btVector3 velocity = pRigidBody->getLinearVelocity();

        return ToMath(velocity);
    }

    void BulletPhysics::vSetVelocity(ActorID actorID, const Vector3& velocity)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return;
        }

        pRigidBody->setLinearVelocity(ToBulletMath(velocity));
    }

    const Vector3 BulletPhysics::vGetAngularVelocity(ActorID actorID)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return Vector3();
        }

        btVector3 velocity = pRigidBody->getAngularVelocity();

        return ToMath(velocity);
    }

    void BulletPhysics::vSetAngularVelocity(ActorID actorID, const Vector3& velocity)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return;
        }

        pRigidBody->setAngularVelocity(ToBulletMath(velocity));
    }

    void BulletPhysics::vSetLinearFactor(ActorID actorID, const Vector3& linearFactor)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return;
        }

        pRigidBody->setLinearFactor(ToBulletMath(linearFactor));
    }

    void BulletPhysics::vSetAngularFactor(ActorID actorID, const Vector3& angularFactor)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return;
        }

        pRigidBody->setAngularFactor(ToBulletMath(angularFactor));
    }

    void BulletPhysics::vTranslate(ActorID actorID, const Vector3& offset)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);
        if (pRigidBody == nullptr)
        {
            return;
        }

        pRigidBody->translate(ToBulletMath(offset));
    }

    void BulletPhysics::vSetTransform(ActorID actorID, const Matrix4& transform)
    {
        vKinematicMove(actorID, transform);
    }

    const Matrix4 BulletPhysics::vGetTransform(ActorID actorID)
    {
        btRigidBody* pRigidBody = GetRigidBody(actorID);
        assert(pRigidBody != nullptr);

        const btTransform& transform = pRigidBody->getCenterOfMassTransform();

        return ToMath(transform);
    }

    void BulletPhysics::vEnableDebug(ISceneRendererSharedPointer pRenderer)
    {
        // TODO: refactor this into a DebugRenderer class.
        OgreSceneRendererSharedPointer pOgreRenderer = std::dynamic_pointer_cast<OgreSceneRenderer>(pRenderer);
        assert(pOgreRenderer != nullptr);

        Ogre::SceneManager* pOgreManager = pOgreRenderer->GetOgreSceneManager();
        m_pDebugDrawer = LIB_NEW CDebugDraw(pOgreManager, m_pDynamicsWorld);
    }

    void BulletPhysics::vDisableDebug()
    {
        SAFE_DELETE(m_pDebugDrawer);
    }

    void BulletPhysics::RegisterEvents()
    {
        REGISTER_EVENT(EvtData_PhysTrigger_Enter);
        REGISTER_EVENT(EvtData_PhysTrigger_Leave);
        REGISTER_EVENT(EvtData_PhysCollision);
        REGISTER_EVENT(EvtData_PhysSeparation);
    }

    void BulletPhysics::RegisterEventDelegates()
    {
        EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &BulletPhysics::SceneNodeAttachedDelegate);
        IEventManager::Get()->vAddListener(functionDelegate, EvtData_Scene_Node_Attached::sk_EventType);
    }

    void BulletPhysics::UnregisterEventDelegates()
    {
        EventListenerDelegate functionDelegate = fastdelegate::MakeDelegate(this, &BulletPhysics::SceneNodeAttachedDelegate);
        IEventManager::Get()->vRemoveListener(functionDelegate, EvtData_New_Actor::sk_EventType);
    }

    void BulletPhysics::SceneNodeAttachedDelegate(IEventDataSharedPointer pEventData)
    {
        std::shared_ptr<EvtData_Scene_Node_Attached> pData = std::static_pointer_cast<EvtData_Scene_Node_Attached>(pEventData);

        ActorID actorID = pData->GetActorID();
        Matrix4 transform = pData->GetTransform();

        // TODO: finish this.
        //vSetTransform(actorID, transform);
    }

    void BulletPhysics::AddShape(ActorSharedPointer pActor, btCollisionShape* pCollisionShape, float fMass, bool bIsKinematic, const std::string& physicsMaterialName)
    {
        assert(pActor != nullptr && "Invalid actor!");

        ActorID actorID = pActor->GetActorID();
        assert(m_ActorRigidBodies.find(actorID) == m_ActorRigidBodies.end() && "This actor already has one physics body!");

        PhysicsMaterial material(GetMaterialData(physicsMaterialName));

        btVector3 localInertia(0.0f, 0.0f, 0.0f);
        if (fMass > 0.0f)
        {
            pCollisionShape->calculateLocalInertia(fMass, localInertia);
        }

        Component::TransformableComponentSharedPointer pActorTransformComponent =
            pActor->GetComponent<Component::TransformableComponent>(Component::TransformableComponent::g_ComponentName).lock();
        if (pActorTransformComponent == nullptr)
        {
            // Physics cannot work on an actor without a TransformComponent.
            return;
        }

        Matrix4 transform(pActorTransformComponent->GetTransform());
        //ActorMotionState* const pMotionState = LIB_NEW ActorMotionState(transform); // Scale must be (1.0f, 1.0f, 1.0f).
        ActorMotionState* const pMotionState = LIB_NEW ActorMotionState(transform.GetPositionVector(), transform.GetRotationQuaternion());
        //pCollisionShape->setLocalScaling(ToBulletMath(transform.GetScaleVector()));

        btRigidBody::btRigidBodyConstructionInfo rbInfo(fMass, pMotionState, pCollisionShape, localInertia);
        rbInfo.m_restitution = material.m_fRestitution;
        rbInfo.m_friction = material.m_fFriction;

        btRigidBody* const pRigidBody = new btRigidBody(rbInfo);
        if (bIsKinematic)
        {
#ifdef UGE_EXPERIMENTAL_GHOST
            pRigidBody->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
#else
            //pRigidBody->setCollisionFlags(pRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
            pRigidBody->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
#endif
            pRigidBody->setActivationState(DISABLE_DEACTIVATION);
        }

        m_pDynamicsWorld->addRigidBody(pRigidBody);

        m_ActorRigidBodies[actorID] = pRigidBody;
        m_RigidBodiesActor[pRigidBody] = actorID;

#ifdef UGE_EXPERIMENTAL_GHOST
        if (bIsKinematic)
        {
            // Add ghost object for rigid body collision.
            btPairCachingGhostObject* pGhostObject = new btPairCachingGhostObject();
            pGhostObject->setCollisionShape(pCollisionShape);
            pGhostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
            btTransform btTransform(ToBulletMath(transform.GetRotationQuaternion()), ToBulletMath(transform.GetPositionVector()));
            pGhostObject->setWorldTransform(btTransform);

            m_ActorGhosts[actorID] = pGhostObject;
        }
#endif
    }

    void BulletPhysics::AddActor(ActorID actorID, ActorWeakPointer pActor)
    {
        m_Actors[actorID] = pActor;
    }

    void BulletPhysics::LoadMaterialData()
    {
        // TODO: use a resource instead.
        //XMLElement xmlRoot = XMLResourceLoader::LoadAndReturnRootElement("data/config/physics.xml");
        XMLFile xmlFile;
        if (!xmlFile.OpenFile("data/config/physics.xml", File::FileMode::FileReadOnly))
        {
            assert(0 && "Could not open the physics config file!");
        }
        XMLElement xmlRoot(xmlFile.GetRootElement());

        assert(xmlRoot.IsGood() && "Could not read the physics data configurtion file!");

        XMLElement materialsElement = xmlRoot.GetFirstChildElement("PhysicsMaterials");
        assert(materialsElement.IsGood());
        for (XMLElement xmlElement = materialsElement.GetFirstChildElement(); xmlElement.IsGood(); xmlElement = xmlElement.GetNextSiblingElement())
        {
            float fRestitution = 0.0f;
            float fFriction = 0.0f;

            xmlElement.GetFloatAttribute("restitution", &fRestitution);
            xmlElement.GetFloatAttribute("friction", &fFriction);

            m_MaterialTable.insert(std::make_pair(xmlElement.GetElementName(), PhysicsMaterial(fRestitution, fFriction)));
        }

        XMLElement densitiesElement = xmlRoot.GetFirstChildElement("DensityTable");
        assert(densitiesElement.IsGood());
        for (XMLElement xmlElement = densitiesElement.GetFirstChildElement(); xmlElement.IsGood(); xmlElement = xmlElement.GetNextSiblingElement())
        {
            std::string value;
            xmlElement.GetElementAsText(value);
            //xmlElement.GetFloatAttribute("density", &fDensity);

            float fDensity = StringToFloat(value);
            m_DensityTable.insert(std::make_pair(xmlElement.GetElementName(), fDensity));
        }

        // Will be removed when using a resource.
        xmlFile.CloseFile();
    }

    float BulletPhysics::GetSpecificGravity(const std::string& densityName)
    {
        float fDensity = 0.0f;
        const auto& it = m_DensityTable.find(densityName);
        if (it != m_DensityTable.end())
        {
            fDensity = it->second;
        }
        else
        {
            assert(0 && "Density not found!");
        }

        return fDensity;
    }

    PhysicsMaterial BulletPhysics::GetMaterialData(const std::string& materialName)
    {
        float fDensity = 0.0f;
        const auto& it = m_MaterialTable.find(materialName);
        if (it != m_MaterialTable.end())
        {
            return it->second;
        }
        else
        {
            assert(0 && "Material not found!");

            return PhysicsMaterial(0.0f, 0.0f);
        }
    }

    btRigidBody* BulletPhysics::GetRigidBody(ActorID actorID) const
    {
        ActorToRigidBodyMap::const_iterator it = m_ActorRigidBodies.find(actorID);
        if (it != m_ActorRigidBodies.end())
        {
            return it->second;
        }

        return nullptr;
    }

    ActorID BulletPhysics::GetActorID(const btRigidBody* pRigidBody) const
    {
        RigidBodyToActorMap::const_iterator it = m_RigidBodiesActor.find(pRigidBody);
        if (it != m_RigidBodiesActor.end())
        {
            return it->second;
        }

        return Actor::NULL_ACTOR_ID;
    }

#ifdef UGE_EXPERIMENTAL_GHOST
    btPairCachingGhostObject* BulletPhysics::GetGhost(ActorID actorID) const
    {
        ActorToGhostMap::const_iterator it = m_ActorGhosts.find(actorID);
        if (it != m_ActorGhosts.end())
        {
            return it->second;
        }

        return nullptr;
    }

    //void BulletPhysics::UpdateGhostIfExists(ActorID actorID, const Matrix4& transform)
    //{
    //    btPairCachingGhostObject* pActorGhost = GetGhost(actorID);
    //    if (pActorGhost == nullptr)
    //    {
    //        return;
    //    }

    //    std::cout << "Actor ghost updated!" << std::endl;

    //    pActorGhost->setActivationState(DISABLE_DEACTIVATION);
    //    pActorGhost->setWorldTransform(ToBulletMath(transform));
    //}

    bool BulletPhysics::RecoverActorFromPenetration(ActorID actorID)
    {
        btPairCachingGhostObject* pActorGhost = GetGhost(actorID);
        if (pActorGhost == nullptr)
        {
            return false;
        }

        btTransform transform = pActorGhost->getWorldTransform();

        btRigidBody* pRigidBody = GetRigidBody(actorID);
        //pRigidBody->setActivationState(DISABLE_DEACTIVATION);
        //pRigidBody->setWorldTransform(transform);


        bool bPenetration = false;
        const int MAX_ATTEMPTS = 4;
        int attemptCount = 0;
        while (attemptCount < MAX_ATTEMPTS)
        {
            ++attemptCount;

            // Here we must refresh the overlapping paircache as the penetrating movement itself or the
            // previous recovery iteration might have used setWorldTransform and pushed us into an object
            // that is not in the previous cache contents from the last timestep, as will happen if we
            // are pushed into a new AABB overlap. Unhandled this means the next convex sweep gets stuck.
            //
            // Do this by calling the broadphase's setAabb with the moved AABB, this will update the broadphase
            // paircache and the ghostobject's internal paircache at the same time.    /BW

            btVector3 minAabb, maxAabb;
            pRigidBody->getCollisionShape()->getAabb(pActorGhost->getWorldTransform(), minAabb, maxAabb);

            btDispatcher* pDispatcher = m_pDynamicsWorld->getDispatcher();
            btBroadphaseProxy* pBroadphaseHandle = pActorGhost->getBroadphaseHandle(); // Is NULL at the moment.
            btBroadphaseInterface* pBroadphaseInterface = m_pDynamicsWorld->getBroadphase();
            pBroadphaseInterface->setAabb(pBroadphaseHandle,
                                          minAabb,
                                          maxAabb,
                                          pDispatcher);

            pDispatcher->dispatchAllCollisionPairs(pActorGhost->getOverlappingPairCache(), m_pDynamicsWorld->getDispatchInfo(), pDispatcher);

            btVector3 currentPosition = pActorGhost->getWorldTransform().getOrigin();

            btScalar maxPen = btScalar(0.0);
            for (int i = 0; i < pActorGhost->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
            {
                btManifoldArray manifoldArray;
                manifoldArray.resize(0);

                btBroadphasePair* collisionPair = &pActorGhost->getOverlappingPairCache()->getOverlappingPairArray()[i];

                if (collisionPair->m_algorithm)
                {
                    collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
                }


                for (int j = 0; j < manifoldArray.size(); j++)
                {
                    btPersistentManifold* manifold = manifoldArray[j];
                    btScalar directionSign = manifold->getBody0() == pActorGhost ? btScalar(-1.0) : btScalar(1.0);
                    for (int p = 0; p < manifold->getNumContacts(); p++)
                    {
                        const btManifoldPoint& pt = manifold->getContactPoint(p);

                        btScalar dist = pt.getDistance();

                        if (dist < 0.0)
                        {
                            if (dist < maxPen)
                            {
                                maxPen = dist;
                                //m_touchingNormal = pt.m_normalWorldOnB * directionSign;//??

                            }
                            currentPosition += pt.m_normalWorldOnB * directionSign * dist * btScalar(0.2);
                            bPenetration = true;
                        }
                        else
                        {
                            //printf("touching %f\n", dist);
                        }
                    }

                    //manifold->clearManifold();
                }
            }
            btTransform newTrans = pActorGhost->getWorldTransform();
            newTrans.setOrigin(currentPosition);
            pActorGhost->setWorldTransform(newTrans);
            //	printf("m_touchingNormal = %f,%f,%f\n",m_touchingNormal[0],m_touchingNormal[1],m_touchingNormal[2]);
        }

        return bPenetration;
    }
#endif

    void BulletPhysics::RemoveCollisionObject(btCollisionObject* pCollisionObject)
    {
        m_pDynamicsWorld->removeCollisionObject(pCollisionObject);

        for (CollisionPairs::iterator it = m_PreviousTickCollisionPairs.begin();
             it != m_PreviousTickCollisionPairs.end();)
        {
            CollisionPairs::iterator next = it;
            ++next;

            if ((it->first == pCollisionObject) || (it->second == pCollisionObject))
            {
                SendCollisionPairRemoveEventData(it->first, it->second);
                m_PreviousTickCollisionPairs.erase(it);
            }

            it = next;
        }

        btRigidBody* pRigidBody = btRigidBody::upcast(pCollisionObject);
        if (pRigidBody != nullptr)
        {
            delete pRigidBody->getMotionState();
            delete pRigidBody->getCollisionShape();
            delete pRigidBody->getUserPointer();
            //delete pRigidBody->getUserPointer();

            for (int bodyConstraints = pRigidBody->getNumConstraintRefs() - 1; bodyConstraints >= 0; --bodyConstraints)
            {
                btTypedConstraint* pConstraint = pRigidBody->getConstraintRef(bodyConstraints);
                m_pDynamicsWorld->removeConstraint(pConstraint);
                SAFE_DELETE(pConstraint);
            }
        }

        delete pCollisionObject;
    }

    void BulletPhysics::BulletInternalTickCallback(btDynamicsWorld* const pWorld, const btScalar timeStep)
    {
        // More info: http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Collision_Callbacks_and_Triggers

        assert(pWorld != nullptr);

        assert(pWorld->getWorldUserInfo() != nullptr);
        BulletPhysics* const pBulletPhysics = static_cast<BulletPhysics*>(pWorld->getWorldUserInfo());

        CollisionPairs currentTickCollisionPairs;

        btDispatcher* const pDispatcher = pWorld->getDispatcher();
        for (int manifoldIndex = 0; manifoldIndex < pDispatcher->getNumManifolds(); ++manifoldIndex)
        {
            const btPersistentManifold* const pManifold = pDispatcher->getManifoldByIndexInternal(manifoldIndex);
            assert(pManifold);

            const btRigidBody* const pFirstBody = static_cast<const btRigidBody*>(pManifold->getBody0());
            const btRigidBody* const pSecondBody = static_cast<const btRigidBody*>(pManifold->getBody1());

            bool bSwapped = pFirstBody > pSecondBody;
            const btRigidBody* const pSortedBodyA = bSwapped ? pSecondBody : pFirstBody;
            const btRigidBody* const pSortedBodyB = bSwapped ? pFirstBody : pSecondBody;

            const CollisionPair thisPair = std::make_pair(pSortedBodyA, pSortedBodyB);
            currentTickCollisionPairs.insert(thisPair);

            if (pBulletPhysics->m_PreviousTickCollisionPairs.find(thisPair) == pBulletPhysics->m_PreviousTickCollisionPairs.end())
            {
                pBulletPhysics->SendCollisionPairAddEventData(pManifold, pFirstBody, pSecondBody);

#ifdef UGE_EXPERIMENTAL_GHOST
                ActorID actorA = pBulletPhysics->GetActorID(pSortedBodyA);
                pBulletPhysics->RecoverActorFromPenetration(actorA);

                ActorID actorB = pBulletPhysics->GetActorID(pSortedBodyB);
                pBulletPhysics->RecoverActorFromPenetration(actorB);
#endif
            }
        }

        CollisionPairs removedCollisionPairs;
        std::set_difference(pBulletPhysics->m_PreviousTickCollisionPairs.begin(), pBulletPhysics->m_PreviousTickCollisionPairs.end(),
                            currentTickCollisionPairs.begin(), currentTickCollisionPairs.end(),
                            std::inserter(removedCollisionPairs, removedCollisionPairs.begin()));

        for (CollisionPairs::const_iterator it = removedCollisionPairs.begin(),
             end = removedCollisionPairs.end(); it != end; ++it)
        {
            const btRigidBody* const pFirstBody = it->first;
            const btRigidBody* const pSecondBody = it->second;

            pBulletPhysics->SendCollisionPairRemoveEventData(pFirstBody, pSecondBody);
        }

        pBulletPhysics->m_PreviousTickCollisionPairs = currentTickCollisionPairs;
    }

    void BulletPhysics::SendCollisionPairAddEventData(const btPersistentManifold* pManifold, const btRigidBody* pFirstRigidBody, const btRigidBody* pSecondRigidBody)
    {
        if ((pFirstRigidBody->getUserPointer() != nullptr) || (pSecondRigidBody->getUserPointer() != nullptr))
        {
            // One of the bodies is a trigger.
            const btRigidBody* pTriggerBody;
            const btRigidBody* pOtherBody;

            if (pFirstRigidBody->getUserPointer())
            {
                pTriggerBody = pFirstRigidBody;
                pOtherBody = pSecondRigidBody;
            }
            else
            {
                pOtherBody = pFirstRigidBody;
                pTriggerBody = pSecondRigidBody;
            }

            // send the trigger event.
            int triggerId = *static_cast<int*>(pTriggerBody->getUserPointer());
            std::shared_ptr<EvtData_PhysTrigger_Enter> pEvent(LIB_NEW EvtData_PhysTrigger_Enter(triggerId, GetActorID(pOtherBody)));
            IEventManager::Get()->vQueueEvent(pEvent);
        }
        else
        {
            ActorID firstActorID = GetActorID(pFirstRigidBody);
            ActorID secondActorID = GetActorID(pSecondRigidBody);

            if ((firstActorID == Actor::NULL_ACTOR_ID) || (secondActorID == Actor::NULL_ACTOR_ID))
            {
                // something is colliding with a non-actor.  we currently don't send events for that
                return;
            }

            // this pair of colliding objects is new.  send a collision-begun event
            Vector3List collisionPoints;
            Vector3 sumNormalForce;
            Vector3 sumFrictionForce;

            for (int pointIndex = 0; pointIndex < pManifold->getNumContacts(); ++pointIndex)
            {
                const btManifoldPoint& point = pManifold->getContactPoint(pointIndex);

                collisionPoints.push_back(ToMath(point.getPositionWorldOnB()));

                sumNormalForce += ToMath(point.m_combinedRestitution * point.m_normalWorldOnB);
                sumFrictionForce += ToMath(point.m_combinedFriction * point.m_lateralFrictionDir1);
            }

            // send the event for the game
            std::shared_ptr<EvtData_PhysCollision> pEvent(LIB_NEW EvtData_PhysCollision(firstActorID, secondActorID, sumNormalForce, sumFrictionForce, collisionPoints));
            IEventManager::Get()->vQueueEvent(pEvent);
        }
    }

    void BulletPhysics::SendCollisionPairRemoveEventData(const btRigidBody* pFirstRigidBody, const btRigidBody* pSecondRigidBody)
    {
        if ((pFirstRigidBody->getUserPointer() != nullptr) || (pSecondRigidBody->getUserPointer() != nullptr))
        {
            // One of the bodies is a trigger.
            const btRigidBody* pTriggerBody;
            const btRigidBody* pOtherBody;

            if (pFirstRigidBody->getUserPointer())
            {
                pTriggerBody = pFirstRigidBody;
                pOtherBody = pSecondRigidBody;
            }
            else
            {
                pOtherBody = pFirstRigidBody;
                pTriggerBody = pSecondRigidBody;
            }

            // send the trigger event.
            int const triggerId = *static_cast<int*>(pTriggerBody->getUserPointer());
            std::shared_ptr<EvtData_PhysTrigger_Leave> pEvent(LIB_NEW EvtData_PhysTrigger_Leave(triggerId, GetActorID(pOtherBody)));
            IEventManager::Get()->vQueueEvent(pEvent);
        }
        else
        {
            ActorID firstActorID = GetActorID(pFirstRigidBody);
            ActorID secondActorID = GetActorID(pSecondRigidBody);

            if ((firstActorID == Actor::NULL_ACTOR_ID) || (secondActorID == Actor::NULL_ACTOR_ID))
            {
                // collision is ending between some object(s) that don't have actors.  we don't send events for that.
                return;
            }

            std::shared_ptr<EvtData_PhysSeparation> pEvent(LIB_NEW EvtData_PhysSeparation(firstActorID, secondActorID));
            IEventManager::Get()->vQueueEvent(pEvent);
        }
    }
}
