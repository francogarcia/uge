#include "GameEngineStd.h"

#include "Scene.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/Events/DefaultEvents.h>

namespace uge
{
    Scene::Scene()
        : IScene(), m_MatrixStack(), m_pRootNode(nullptr)
    {
        m_pRootNode.reset(LIB_NEW RootSceneNode());
    }

    Scene::~Scene()
    {

    }

    ISceneNodeSharedPointer Scene::vGetRootSceneNode() const
    {
        return m_pRootNode;
    }

    bool Scene::vOnUpdate(const unsigned long timeElapsed)
    {
        if (m_pRootNode == nullptr)
        {
            return false;
        }

        return m_pRootNode->vOnUpdate(this, timeElapsed);
    }

    bool Scene::vAddChild(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        if (actorID != Actor::NULL_ACTOR_ID)
        {
            auto& pSceneNodeIterator = m_ActorMap.find(actorID);
            assert(pSceneNodeIterator == m_ActorMap.end() && "Actor is already in the scene!");
        }

        m_ActorMap[actorID] = pSceneNode;

        bool bSuccess = m_pRootNode->vAddChild(pSceneNode);
        // Update the children position.
        pSceneNode->vOnUpdate(this, 0u);
        for (auto& pChildSceneNode : pSceneNode->vGetChildren())
        {
            uge::ActorID childActorID = pChildSceneNode->vGetNodeProperties()->GetActorID();
            bSuccess &= vAddChildrenToMap(childActorID, pChildSceneNode);
            vNotifyNewChildrenNode(childActorID, pChildSceneNode);
        }

        return bSuccess;
    }

    bool Scene::vAddChildrenToMap(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        if (actorID != Actor::NULL_ACTOR_ID)
        {
            auto& pSceneNodeIterator = m_ActorMap.find(actorID);
            assert(pSceneNodeIterator == m_ActorMap.end() && "Actor is already in the scene!");
        }

        m_ActorMap[actorID] = pSceneNode;

        bool bSuccess = true;
        for (auto& pChildSceneNode : pSceneNode->vGetChildren())
        {
            uge::ActorID childActorID = pChildSceneNode->vGetNodeProperties()->GetActorID();
            bSuccess &= vAddChildrenToMap(childActorID, pChildSceneNode);
        }

        return bSuccess;
    }

    ISceneNodeSharedPointer Scene::vFindActor(ActorID actorID)
    {
        auto& sceneNodeIterator = m_ActorMap.find(actorID);
        if (sceneNodeIterator == m_ActorMap.end())
        {
            return ISceneNodeSharedPointer();
        }

        return sceneNodeIterator->second;
    }

    bool Scene::vRemoveChild(ActorID actorID)
    {
        if (actorID == Actor::NULL_ACTOR_ID)
        {
            return false;
        }

        SceneNodeSharedPointer pSceneNode = std::dynamic_pointer_cast<SceneNode>(vFindActor(actorID));
        for (auto& pChildSceneNode : pSceneNode->vGetChildren())
        {
            uge::ActorID childActorID = pChildSceneNode->vGetNodeProperties()->GetActorID();
            vRemoveChildrenFromMap(childActorID);
        }
        pSceneNode->m_Children.clear();

        m_ActorMap.erase(actorID);

        ISceneNode* pParentNode = pSceneNode->vGetParent();

        return pParentNode->vRemoveChild(actorID);
    }

    void Scene::vRemoveChildrenFromMap(ActorID actorID)
    {
        SceneNodeSharedPointer pSceneNode = std::dynamic_pointer_cast<SceneNode>(vFindActor(actorID));
        for (auto& pChildSceneNode : pSceneNode->vGetChildren())
        {
            uge::ActorID childActorID = pChildSceneNode->vGetNodeProperties()->GetActorID();
            m_ActorMap.erase(childActorID);
        }
        pSceneNode->m_Children.clear();

        m_ActorMap.erase(actorID);
    }

    void Scene::vPushSetMatrix(const Matrix4& toWorld)
    {
        m_MatrixStack.Push();
        m_MatrixStack.ApplyLocal(toWorld);

        //Matrix4 localTransform = vGetTopMatrix();
    }

    void Scene::vPopMatrix()
    {
        m_MatrixStack.Pop();
    }

    const Matrix4& Scene::vGetTopMatrix() const
    {
        return m_MatrixStack.Top();
    }

    void Scene::vNotifyNewChildrenNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        // TODO: finish this.
        // The position of the child nodes might have changed, thus an event is dispatched to inform
        // other systems about the change.
        //std::shared_ptr<EvtData_Scene_Node_Attached> pEvent(LIB_NEW EvtData_Scene_Node_Attached(actorID, pSceneNode->vGetNodeProperties()->GetWorldTransform()));
        //IEventManager::Get()->vQueueEvent(pEvent);

        for (auto& pChildSceneNode : pSceneNode->vGetChildren())
        {
            uge::ActorID childActorID = pChildSceneNode->vGetNodeProperties()->GetActorID();
            vNotifyNewChildrenNode(childActorID, pChildSceneNode);
        }
    }
}
