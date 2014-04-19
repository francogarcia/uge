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

#include "NullPhysics.h"

#include <Core/Events/DefaultEvents.h>
#include <Core/Events/IEventManager.h>

namespace uge
{
    NullPhysics::NullPhysics()
    {

    }

    NullPhysics::~NullPhysics()
    {

    }

    bool NullPhysics::vInit()
    {
        return true;
    }

    bool NullPhysics::vDestroy()
    {
        return true;
    }

    bool NullPhysics::vUpdate(unsigned long timeElapsed)
    {
        return true;
    }

    void NullPhysics::vSyncVisibleScene()
    {

    }

    void NullPhysics::vSetGravity(const Vector3& gravity)
    {

    }

    void NullPhysics::vAddActor(ActorWeakPointer pActor)
    {

    }

    void NullPhysics::vAddSphere(float fRadius, ActorWeakPointer pActor, const std::string& density, const std::string& material)
    {

    }

    void NullPhysics::vAddBox(const Vector3& dimensions, ActorWeakPointer pActor, const std::string& density, const std::string& material)
    {

    }

    void NullPhysics::vAddPlane(const Vector3& normal, float fConstant, ActorWeakPointer pActor, const std::string& material)
    {

    }

    void NullPhysics::vRemoveActor(ActorID actorID)
    {

    }

    void NullPhysics::vCreateTrigger(ActorWeakPointer pActor, const Vector3& position, const float fDimension)
    {

    }

    void NullPhysics::vApplyForce(ActorID actorID, const Vector3& direction, const float fNewtons)
    {

    }

    void NullPhysics::vApplyTorque(ActorID actorID, const Vector3& direction, const float fNewtons)
    {

    }

    bool NullPhysics::vKinematicMove(ActorID actorID, const Matrix4& transform)
    {
        std::shared_ptr<EvtData_Move_Actor> pEvent(LIB_NEW EvtData_Move_Actor(actorID, transform));
        IEventManager::Get()->vQueueEvent(pEvent);

        return true;
    }

    void NullPhysics::vRotateY(ActorID actorID, float fAngle, float fTime)
    {

    }

    float NullPhysics::vGetOrientationY(ActorID actorID)
    {
        return 0.0f;
    }

    void NullPhysics::vStopActor(ActorID actorID)
    {

    }

    const Vector3 NullPhysics::vGetVelocity(ActorID actorID)
    {
        return Vector3();
    }

    void NullPhysics::vSetVelocity(ActorID actorID, const Vector3& velocity)
    {

    }

    const Vector3 NullPhysics::vGetAngularVelocity(ActorID actorID)
    {
        return Vector3();
    }

    void NullPhysics::vSetAngularVelocity(ActorID actorID, const Vector3& velocity)
    {

    }

    void NullPhysics::vSetLinearFactor(ActorID actorID, const Vector3& linearFactor)
    {

    }

    void NullPhysics::vSetAngularFactor(ActorID actorID, const Vector3& angularFactor)
    {

    }

    void NullPhysics::vTranslate(ActorID actorID, const Vector3& offset)
    {

    }

    void NullPhysics::vSetTransform(ActorID actorID, const Matrix4& transform)
    {
        vKinematicMove(actorID, transform);
    }

    const Matrix4 NullPhysics::vGetTransform(ActorID actorID)
    {
        return Matrix4();
    }

    void NullPhysics::vEnableDebug(ISceneRendererSharedPointer pRenderer)
    {

    }

    void NullPhysics::vDisableDebug()
    {

    }
}
