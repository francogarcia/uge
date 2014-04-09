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

/**
 * @file ActorFactory.cpp
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "ActorFactory.h"

#include "../Component/CollidableComponent.h"
#include "../Component/MoveableComponent.h"
#include "../Component/TransformableComponent.h"

#include "../Component/Implementation/BulletPhysicsComponent.h"
//#include "../Component/Implementation/BulletPhysicsBoxComponent.h"
//#include "../Component/Implementation/BulletPhysicsSphereComponent.h"
#include "../Component/Implementation/OgreGraphicalComponent.h"
#include "../Component/Implementation/OpenALSoftAudioComponent.h"
#include "../Component/Implementation/YSEAudioComponent.h"

#include <Utilities/Debug/Logger.h>

// TODO: something similar:
//#define REGISTER_EVENT(eventClass) g_eventFactory.Register<eventClass>(eventClass::sk_EventType)

namespace uge
{

    ActorFactory::ActorFactory()
    {
        m_LastActorID = Actor::NULL_ACTOR_ID;

        // TODO: insert possible component types (graphics, audio, physics...).
        m_ComponentFactory.Register<Component::MoveableComponent>(Component::GetComponentID(Component::MoveableComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::TransformableComponent>(Component::GetComponentID(Component::TransformableComponent::g_ComponentName));

        // Component implementations.
        m_ComponentFactory.Register<Component::BulletPhysicsComponent>(Component::GetComponentID(Component::BulletPhysicsComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::CollidableComponent>(Component::GetComponentID(Component::CollidableComponent::g_ComponentName));
        //m_ComponentFactory.Register<Component::BulletPhysicsBoxComponent>(Component::GetComponentID(Component::BulletPhysicsBoxComponent::g_ComponentName));
        //m_ComponentFactory.Register<Component::BulletPhysicsSphereComponent>(Component::GetComponentID(Component::BulletPhysicsSphereComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::OgreGraphicalComponent>(Component::GetComponentID(Component::OgreGraphicalComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::OpenALSoftAudioComponent>(Component::GetComponentID(Component::OpenALSoftAudioComponent::g_ComponentName));
        m_ComponentFactory.Register<Component::YSEAudioComponent>(Component::GetComponentID(Component::YSEAudioComponent::g_ComponentName));
    }

    ActorFactory::~ActorFactory()
    {

    }

    ActorSharedPointer ActorFactory::CreateActor(const std::string& actorResourceFileName,
                                                 XMLElement* pActorSpecificData)
    {
        assert(actorResourceFileName != "" && "Invalid XML file to load the actor!");
        XMLFile xmlFile;
        xmlFile.OpenFile(actorResourceFileName, File::FileMode::FileReadOnly);
        if (!xmlFile.IsGood())
        {
            LOG_ERROR(std::string("XML file could not be opened: " + actorResourceFileName + "."));
        }

        XMLElement xmlRootElement(xmlFile.GetRootElement());
        assert(xmlRootElement.IsGood() && "Invalid Root in XML File!");

        ActorID actorID = GetNextActorID();
        assert(actorID != Actor::NULL_ACTOR_ID && "Error creating the first actor or too many actors were created!");

        ActorSharedPointer pActor(LIB_NEW Actor(actorID));
        pActor->Init(&xmlRootElement);

        for (XMLElement xmlElement = xmlRootElement.GetFirstChildElement();
             xmlElement.IsGood();
             xmlElement = xmlElement.GetNextSiblingElement())
        {
            ActorComponentSharedPointer pActorComponent(vCreateComponent(&xmlElement));
            if (pActorComponent != nullptr)
            {
                pActor->AddComponent(pActorComponent);
                pActorComponent->SetOwner(pActor);
            }
            else
            {
                return ActorSharedPointer();
            }
        }

        if (pActorSpecificData != nullptr)
        {
            ModifyActor(pActor, pActorSpecificData);
        }

        pActor->PostInit();

        xmlFile.CloseFile();

        return pActor;
    }

    void ActorFactory::ModifyActor(ActorSharedPointer pActor, XMLElement* pSpecificData)
    {
        for (XMLElement pNode = pSpecificData->GetFirstChildElement();
             pNode.IsGood(); pNode = pNode.GetNextSiblingElement())
        {
            ComponentID componentID = Component::GetComponentID(pNode.GetNodeValue());
            std::weak_ptr<Component::ActorComponent> pActorComponent = pActor->GetComponent<Component::ActorComponent>(componentID);
            if (!pActorComponent.expired())
            {
                ActorComponentSharedPointer pComponent = pActorComponent.lock();
                assert(pComponent != nullptr);
                
                pComponent->vInit(&pNode);
                pComponent->vOnChange();
            }
            else
            {
                ActorComponentSharedPointer pComponent = vCreateComponent(&pNode);
                if (pComponent != nullptr)
                {
                    pActor->AddComponent(pComponent);
                    pComponent->SetOwner(pActor);
                }
                else
                {
                    LOG_ERROR("Could not create the component!");
                }
            }
        }
    }

    ActorComponentSharedPointer ActorFactory::vCreateComponent(XMLElement* pSpecificData)
    {
        std::string componentName = pSpecificData->GetNodeValue();
        ActorComponentSharedPointer pActorComponent(m_ComponentFactory.Create(Component::GetComponentID(componentName)));

        if (pActorComponent != nullptr)
        {
            if (!pActorComponent->vInit(pSpecificData))
            {
                LOG_ERROR("The component could not be initialized!");

                return ActorComponentSharedPointer();
            }
        }
        else
        {
            LOG_ERROR("The component could not be created!");

            return ActorComponentSharedPointer();
        }

        return pActorComponent;
    }

    const ActorID ActorFactory::GetNextActorID()
    {
        return ++m_LastActorID;
    }

}
