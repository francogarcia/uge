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

#include "SceneManager.h"

#include <Core/EntityComponent/Entity/Actor.h>
#include <Core/EntityComponent/Component/TransformableComponent.h>

#include <Core/Scene/SceneEvents.h>

namespace uge
{
    SceneManager::SceneManager() : m_pScene(nullptr)
    {


    }

    SceneManager::~SceneManager()
    {
        if (m_pScene != nullptr)
        {
            Destroy();
        }
    }

    bool SceneManager::Init()
    {
        m_pScene = LIB_NEW Scene();

        return true;
    }

    bool SceneManager::Destroy()
    {
        SAFE_DELETE(m_pScene);

        return true;
    }

    bool SceneManager::Update(const unsigned long timeElapsed)
    {
        return m_pScene->vOnUpdate(timeElapsed);
    }

    bool SceneManager::AddSceneNode(ActorID actorID, ISceneNodeSharedPointer pSceneNode)
    {
        if (!m_pScene->vAddChild(actorID, pSceneNode))
        {
            assert(0 && "Error inserting scene node!");

            return false;
        }

        std::shared_ptr<EvtData_Scene_Node_Attached> pEvent(LIB_NEW EvtData_Scene_Node_Attached(actorID,
                                                                                                pSceneNode->vGetNodeProperties()->GetWorldTransform()));
        uge::IEventManager::Get()->vQueueEvent(pEvent);

        return true;
    }

    ISceneNodeSharedPointer SceneManager::CreateAndAddSceneNode(ActorSharedPointer pActor)
    {
        Component::TransformableComponentSharedPointer pActorPositionComponent =
            pActor->GetComponent<Component::TransformableComponent>(Component::TransformableComponent::g_ComponentName).lock();
        Matrix4 actorInitialTransform;

        //actorInitialTransform.MakeTranslationMatrix(pActorPositionComponent->GetPosition());
        //actorInitialTransform = pActorPositionComponent->GetTransform();
        actorInitialTransform.MakeTransform(pActorPositionComponent->GetPosition(),
                                            pActorPositionComponent->GetScale(),
                                            pActorPositionComponent->GetRotation());

        ActorID actorID = pActor->GetActorID();
        ISceneNodeSharedPointer pSceneNode(LIB_NEW SceneNode(actorID,
                                                             pActor,
                                                             RenderPass::Actor,
                                                             &actorInitialTransform,
                                                             nullptr));
        if (!AddSceneNode(actorID, pSceneNode))
        {
            assert(0 && "Error creating the actor's scene node!");
        }

        return pSceneNode;
    }

    bool SceneManager::RemoveSceneNode(ActorID actorID)
    {
        ISceneNodeSharedPointer pSceneNode = m_pScene->vFindActor(actorID);
        assert(pSceneNode != nullptr && "The scene not was not found!");

        std::shared_ptr<EvtData_Scene_Node_Removed> pEvent(LIB_NEW EvtData_Scene_Node_Removed(actorID));
        uge::IEventManager::Get()->vTriggerEvent(pEvent);

        if (!m_pScene->vRemoveChild(actorID))
        {
            return false;
        }

        return true;
    }

    ISceneNodeSharedPointer SceneManager::GetSceneNode(ActorID actorID)
    {
        return m_pScene->vFindActor(actorID);
    }

    Scene* SceneManager::GetScene() const
    {
        return m_pScene;
    }
}
