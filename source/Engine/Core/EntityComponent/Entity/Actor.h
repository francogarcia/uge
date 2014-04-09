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
 * @file Actor.h
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include "ActorTypes.h"
#include "../Component/ActorComponent.h"

namespace uge
{

    /**
     * @class Actor
     *  Defines actors to be used by the game.
     */
    class Actor
    {
        /// Actors can only be created by the ActorFactory class.
        friend class ActorFactory;

    public:
        static const ActorID NULL_ACTOR_ID = 0u;

        /**
         *  Constructor.
         * @param id : the identifier which will be used for the actor.
         */
        explicit Actor(const ActorID id);

        /**
         *  Destructor.
         */
        ~Actor();

        /**
         *  Instanciates the game object.
         * @param pInitXMLData : pointer to a XML element containing the object's load data.
         */
        void Init(XMLElement* pInitXMLData);

        /**
         *  Initializes the game object after it was instanciated.
         */
        void PostInit();

        /**
         *  Updates the object.
         * @param dt : time elapsed since the last update.
         */
        void Update(const unsigned long dt);

        /**
         *  Destroys the object, freeing the memory used by the actor.
         */
        void Destroy();

        /**
         *  Returns the actor unique identifier.
         * @return : the actor ID.
         */
        const ActorID GetActorID() const;

        /**
         *  Fecthes the actor type.
         * @return : a string containing the name of the actor.
         */
        const std::string GetActorType() const;

        /**
         *  Retrieves a components associated with this actor by its identifier.
         * @return : a pointer to the requested component.
         */
        template <class ComponentType>
        std::weak_ptr<ComponentType> GetComponent(const ComponentID componentID);

        /**
         *  Retrieves a components associated with this actor by its name.
         * @return : a pointer to the requested component.
         */
        template <class ComponentType>
        std::weak_ptr<ComponentType> GetComponent(const std::string& componentName);

        /**
         *  Gets all the components associated to the actor.
         * @return : a pointer to a map containing all the components of which the actor is composed.
         */
        const ActorComponentMap* GetActorComponents();

        /**
         *  Converts all the data of the actor object to XML.
         * @return : a string with the XML data.
         */
        std::string SerializeActorToXML();

    private:
        /**
         *  Adds a new component to this actor.
         * @param pComponent : a pointer to the new component.
         */
        void AddComponent(ActorComponentSharedPointer pComponent);

        /// Unique identifer for an actor object.
        ActorID m_ActorID;
        /// The name of the component.
        std::string m_ActorType;
        /// The components the actor has.
        ActorComponentMap m_ActorComponents;
        /// The name of the file this actor was loaded from.
        std::string m_ActorResourceFileName;
    };

    template <class ComponentType>
    std::weak_ptr<ComponentType> Actor::GetComponent(const ComponentID componentID)
    {
        ActorComponentMap::iterator componentIt(m_ActorComponents.find(componentID));
        if (componentIt != m_ActorComponents.end())
        {
            ActorComponentSharedPointer pActorComponent(componentIt->second);
            std::shared_ptr<ComponentType> pSharedComponent(std::static_pointer_cast<ComponentType>(pActorComponent));
            std::weak_ptr<ComponentType> pWeakComponent(pSharedComponent);

            return pWeakComponent;
        }

        return std::weak_ptr<ComponentType>();
    }

    template <class ComponentType>
    std::weak_ptr<ComponentType> Actor::GetComponent(const std::string& componentName)
    {
        ComponentID componentID = Component::GetComponentID(componentName);

        return GetComponent<ComponentType>(componentID);
    }

}
