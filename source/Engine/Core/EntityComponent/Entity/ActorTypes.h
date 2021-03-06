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

namespace uge
{

    // Forward declarations.
    class Actor;
    namespace Component
    {
        class ActorComponent;
    }

    /// Declaration of the ActorID type for ease of use.
    typedef unsigned int ActorID;

    /// Declaration of the ComponentID type for ease of use.
    typedef unsigned int ComponentID;

    /// Declaration of a shared pointer of an Actor pointer for ease of use.
    typedef std::shared_ptr<Actor> ActorSharedPointer;

    /// Declaration of a weak pointer of an Actor pointer for ease of use.
    typedef std::weak_ptr<Actor> ActorWeakPointer;

    /// Maps an Actor by its ID to its pointer.
    typedef std::map<ActorID, ActorSharedPointer> ActorMap;
    typedef std::map<ActorID, ActorWeakPointer> WeakActorMap;

    /// Declaration of a shared pointer of an ActorComponent pointer for ease of use.
    typedef std::shared_ptr<Component::ActorComponent> ActorComponentSharedPointer;

    /// Maps an Actor's ID to its ActorComponents.
    typedef std::map<ComponentID, ActorComponentSharedPointer> ActorComponentMap;

}
