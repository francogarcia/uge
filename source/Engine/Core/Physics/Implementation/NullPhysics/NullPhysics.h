#pragma once

#include <Core/Physics/IPhysics.h>

namespace uge
{
    class NullPhysics : public IPhysics
    {
    public:
        NullPhysics();
        virtual ~NullPhysics();

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
        virtual void vDisableDebug();
    };
}
