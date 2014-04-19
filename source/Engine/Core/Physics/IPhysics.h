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

#pragma once

#include <Core/EntityComponent/Entity/ActorTypes.h>
#include <IO/Output/Graphics/Graphics.h>
#include <Utilities/Math/MathStd.h>

#include <Core/Scene/ISceneRenderer.h>

#include "PhysicsEvents.h"

namespace uge
{
    class IPhysics;
    typedef std::shared_ptr<IPhysics> IPhysicsSharedPointer;
    typedef std::weak_ptr<IPhysics> IPhysicsWeakPointer;

    class IPhysics
    {
    public:
        IPhysics();
        virtual ~IPhysics();

        virtual bool vInit() = 0;
        virtual bool vDestroy() = 0;

        virtual bool vUpdate(unsigned long timeElapsed) = 0;
        virtual void vSyncVisibleScene() = 0;

        virtual void vSetGravity(const Vector3& gravity) = 0;

        virtual void vAddActor(ActorWeakPointer pActor) = 0;

        virtual void vAddSphere(float fRadius, ActorWeakPointer pActor, const std::string& density, const std::string& material) = 0;
        virtual void vAddBox(const Vector3& dimensions, ActorWeakPointer pActor, const std::string& density, const std::string& material) = 0;
        virtual void vAddPlane(const Vector3& normal, float fConstant, ActorWeakPointer pActor, const std::string& material) = 0;

        virtual void vRemoveActor(ActorID actorID) = 0;

        virtual void vCreateTrigger(ActorWeakPointer pActor, const Vector3& position, const float fDimension) = 0;
        virtual void vApplyForce(ActorID actorID, const Vector3& direction, const float fNewtons) = 0;
        virtual void vApplyTorque(ActorID actorID, const Vector3& direction, const float fNewtons) = 0;
        virtual bool vKinematicMove(ActorID actorID, const Matrix4& transform) = 0;

        virtual void vRotateY(ActorID actorID, float fAngle, float fTime) = 0;
        virtual float vGetOrientationY(ActorID actorID) = 0;
        virtual void vStopActor(ActorID actorID) = 0;
        
        virtual const Vector3 vGetVelocity(ActorID actorID) = 0;
        virtual void vSetVelocity(ActorID actorID, const Vector3& velocity) = 0;
        virtual const Vector3 vGetAngularVelocity(ActorID actorID) = 0;
        virtual void vSetAngularVelocity(ActorID actorID, const Vector3& velocity) = 0;

        virtual void vSetLinearFactor(ActorID actorID, const Vector3& linearFactor) = 0;
        virtual void vSetAngularFactor(ActorID actorID, const Vector3& angularFactor) = 0;

        virtual void vTranslate(ActorID actorID, const Vector3& offset) = 0;
        virtual void vSetTransform(ActorID actorID, const Matrix4& transform) = 0;
        virtual const Matrix4 vGetTransform(ActorID actorID) = 0;

        // TODO: abstract this to a DebugRenderer.
        virtual void vEnableDebug(ISceneRendererSharedPointer pRenderer) = 0;
        virtual void vDisableDebug() = 0;
    };
}
