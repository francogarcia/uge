/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include <Core/Physics/IPhysics.h>
#include <Core/Physics/PhysicsMaterial.h>

#include "BulletDebugDrawer.h"

// FIXME: this should go to a branch.
//#define UGE_EXPERIMENTAL_GHOST 1

namespace uge
{
    class BulletPhysics : public IPhysics
    {
    public:
        BulletPhysics();
        virtual ~BulletPhysics();

        virtual bool vInit() override;
        virtual bool vDestroy() override;

        virtual bool vUpdate(unsigned long timeElapsed) override;
        virtual void vSyncVisibleScene() override;

        virtual void vSetGravity(const Vector3& gravity) override;

        virtual void vAddActor(ActorWeakPointer pActor) override;

        virtual void vAddSphere(float fRadius, ActorWeakPointer pActor, const std::string& density, const std::string& material) override;
        virtual void vAddBox(const Vector3& dimensions, ActorWeakPointer pActor, const std::string& density, const std::string& material) override;
        virtual void vAddPlane(const Vector3& normal, float fConstant, ActorWeakPointer pActor, const std::string& material) override;

        virtual void vRemoveActor(ActorID actorID) override;

        virtual void vCreateTrigger(ActorWeakPointer pActor, const Vector3& position, const float fDimension) override;
        virtual void vApplyForce(ActorID actorID, const Vector3& direction, const float fNewtons) override;
        virtual void vApplyTorque(ActorID actorID, const Vector3& direction, const float fNewtons) override;
        virtual bool vKinematicMove(ActorID actorID, const Matrix4& transform) override;

        virtual void vRotateY(ActorID actorID, float fAngle, float fTime) override;
        virtual float vGetOrientationY(ActorID actorID) override;
        virtual void vStopActor(ActorID actorID) override;

        virtual const Vector3 vGetVelocity(ActorID actorID) override;
        virtual void vSetVelocity(ActorID actorID, const Vector3& velocity) override;
        virtual const Vector3 vGetAngularVelocity(ActorID actorID) override;
        virtual void vSetAngularVelocity(ActorID actorID, const Vector3& velocity) override;

        virtual void vSetLinearFactor(ActorID actorID, const Vector3& linearFactor) override;
        virtual void vSetAngularFactor(ActorID actorID, const Vector3& angularFactor) override;

        virtual void vTranslate(ActorID actorID, const Vector3& offset) override;
        virtual void vSetTransform(ActorID actorID, const Matrix4& transform) override;
        virtual const Matrix4 vGetTransform(ActorID actorID) override;

        virtual void vEnableDebug(ISceneRendererSharedPointer pRenderer) override;
        virtual void vDisableDebug() override;

    private:
        void RegisterEvents();

        void RegisterEventDelegates();
        void UnregisterEventDelegates();
        void SceneNodeAttachedDelegate(IEventDataSharedPointer pEventData);
        //void SceneNodeRemovedDelegate(IEventDataSharedPointer pEventData);

        void AddShape(ActorSharedPointer pActor, btCollisionShape* pCollisionShape, float fMass, bool bIsKinematic, const std::string& physicsMaterialName);
        void AddActor(ActorID actorID, ActorWeakPointer pActor);

        void LoadMaterialData();
        PhysicsMaterial GetMaterialData(const std::string& materialName);
        float GetSpecificGravity(const std::string& densityName);

        btRigidBody* GetRigidBody(ActorID actorID) const;
        ActorID GetActorID(const btRigidBody* pRigidBody) const;
#ifdef UGE_EXPERIMENTAL_GHOST
        btPairCachingGhostObject* GetGhost(ActorID actorID) const;

        /*void UpdateGhostIfExists(ActorID actorID, const Matrix4& transform);*/
        bool RecoverActorFromPenetration(ActorID actorID);
#endif

        void RemoveCollisionObject(btCollisionObject* pCollisionObject);

        static void BulletInternalTickCallback(btDynamicsWorld* const pWorld, const btScalar timeStep);

        void SendCollisionPairAddEventData(const btPersistentManifold* pManifold, const btRigidBody* pFirstRigidBody, const btRigidBody* pSecondRigidBody);
        void SendCollisionPairRemoveEventData(const btRigidBody* pFirstRigidBody, const btRigidBody* pSecondRigidBody);

    private:
        typedef std::map<ActorID, btRigidBody*> ActorToRigidBodyMap;
        typedef std::map<const btRigidBody*, ActorID> RigidBodyToActorMap;
#ifdef UGE_EXPERIMENTAL_GHOST
        typedef std::map<ActorID, btPairCachingGhostObject*> ActorToGhostMap;
#endif

        typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;
        typedef std::set<CollisionPair> CollisionPairs;

        btDynamicsWorld* m_pDynamicsWorld;
        btBroadphaseInterface* m_pBroadphaseInterface;
        btCollisionDispatcher* m_pCollisionDispatcher;
        btConstraintSolver* m_pConstraintSolver;
        btCollisionConfiguration* m_pCollisionConfiguration; // btDefaultCollisionConfiguration

        DensityTable m_DensityTable;
        PhysicsMaterialTable m_MaterialTable;

        WeakActorMap m_Actors;
        ActorToRigidBodyMap m_ActorRigidBodies;
#ifdef UGE_EXPERIMENTAL_GHOST
        ActorToGhostMap m_ActorGhosts;
#endif
        RigidBodyToActorMap m_RigidBodiesActor;

        CollisionPairs m_PreviousTickCollisionPairs;

        CDebugDraw* m_pDebugDrawer;
    };
}
