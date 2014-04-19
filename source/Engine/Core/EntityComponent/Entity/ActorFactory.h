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
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include "Actor.h"
#include "ActorTypes.h"

#include <Utilities/Math/MathSTD.h>
#include <Utilities/PatternTemplates.h>

namespace uge
{

    /**
     * @class ActorFactory
     *  Creates actors to be used by the game.
     */
    class ActorFactory
    {
    public:
        /**
         *  Constructor.
         */
        ActorFactory();

        /**
         *  Destructor.
         */
        ~ActorFactory();

        /**
         *  Creates a new actor from a XML file.
         * @param actorResourceFileName : file name from which the actor's archetype will be loaded.
         * @param pActorSpecificData : specific data to be loaded into the actor, after the archetype
         *                             was loaded. Set this to nullptr to ignore.
         * @return : a pointer to the actor created.
         */
        ActorSharedPointer CreateActor(const std::string& actorResourceFileName,
                                       XMLElement* pActorSpecificData);

        /**
         *  Changes the data from an existing actor, loading new values from a XML element.
         * @param pActor : pointer to an existing actor.
         * @param pActorSpecificData : specific data to be loaded into the actor, after the archetype
         *                             was loaded.
         */
        void ModifyActor(ActorSharedPointer pActor, XMLElement* pSpecificData);

    protected:
        /**
         *  This method can be implemented by a subclass to create game-specific C++ components.
         * @param pActorSpecificData : specific data to be loaded into the actor, after the archetype
         *                             was loaded.
         */
        virtual ActorComponentSharedPointer vCreateComponent(XMLElement* pSpecificData);

        /// Implements a factory pattern to be used on the creation of new actors.
        GenericObjectFactory<Component::ActorComponent, ComponentID> m_ComponentFactory;

    private:
        /**
         *  Retrieves the next identifier for a new actor.
         * The last ID is incremented in order to generate the new one.
         * @return : an unique ID for a new acto.r
         */
        const ActorID GetNextActorID();

        /// Stores the last issued actor ID, to avoid duplicates.
        ActorID m_LastActorID;
    };

}
