#pragma once

#include <Utilities/Math/MathStd.h>
#include <Core/EntityComponent/Entity/ActorTypes.h>

namespace uge
{
    class IScene;

    class ISceneNode;
    typedef std::shared_ptr<ISceneNode> ISceneNodeSharedPointer;
    typedef std::vector<ISceneNodeSharedPointer> SceneNodeList;
    typedef std::map<ActorID, ISceneNodeSharedPointer> SceneActorMap;

    class ICameraNode;
    typedef std::shared_ptr<ICameraNode> ICameraNodeSharedPointer;

    class SceneNodeProperties;

    class ISceneNode
    {
    public:
        ISceneNode();
        virtual ~ISceneNode();

        virtual const SceneNodeProperties* const vGetNodeProperties() const = 0;

        virtual void vSetTransform(const Matrix4* pToWorld, const Matrix4* pFromWorld) = 0;

        virtual bool vOnUpdate(IScene* pScene, const unsigned long timeElapsed) = 0;

        virtual bool vAddChild(ISceneNodeSharedPointer pChildNode) = 0;
        virtual bool vRemoveChild(ActorID actorID) = 0;

        virtual const SceneNodeList& vGetChildren() const = 0;

        virtual ISceneNode* vGetParent() const = 0;

    //protected:
    //    virtual void vSetParent(ISceneNode* pParentNode) = 0;
    //    virtual void vRemoveChild(ISceneNode* pChildNode) = 0;
    };

    class ICameraNode
    {
    public:
        ICameraNode();
        virtual ~ICameraNode();

        virtual const Frustum& vGetFrustum() const = 0;

        virtual void vSetTarget(ISceneNodeSharedPointer pTargetNode) = 0;
        virtual ISceneNodeSharedPointer vGetTarget() const = 0;
        virtual void vClearTarget() = 0;

        virtual Matrix4 vGetWorldViewProjection(IScene* pScene) const = 0;
        virtual bool vSetViewMatrix() = 0;

        virtual const Matrix4& vGetProjectionMatrix() const = 0;
        virtual const Matrix4& vGetViewMatrix() const = 0;

        virtual void vSetCameraOffset(const Vector4& cameraOffset) = 0;
        virtual void vSetCameraOrientation(const float kYaw, const float kPitch, const float kRoll) = 0;
        virtual void vSetCameraOrientation(const Quaternion& rotation) = 0;
    };
}
