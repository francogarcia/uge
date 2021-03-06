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

#include "GameEngineStd.h"

namespace uge
{

    template <class T>
    class Singleton
    {
    public:
        Singleton()
        {

        }

        ~Singleton()
        {

        }

        static T& Instance()
        {
            static volatile T instance;

            return &instance;
        }

    private:
        Singleton(Singleton const& instance)
        {
            // Disables the copy constructor.
        }

        Singleton& operator=(Singleton const& right)
        {
            // Disables the assignment operator.
        }
    };

    /**
     * @class GenericObjectCreationFunction
     *  Defines a template to instanciate an subclass object from a base class
     * pointer.
     *
     *  This class implementation was extracted from and source code of the book
     * Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
     * David Graham (Rez).
     *  The original source code of the book is licensed under the GNU Lesser General
     * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
     */
    template <class BaseType, class SubType>
    BaseType* GenericObjectCreationFunction(void)
    {
        return LIB_NEW SubType;
    }

    /**
     * @class GenericObjectCreationFunction
     *  Template for the factory design pattern.
     *
     *  This class implementation was extracted from and source code of the book
     * Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
     * David Graham (Rez).
     *  The original source code of the book is licensed under the GNU Lesser General
     * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
     */
    template <class BaseClass, class IdType>
    class GenericObjectFactory
    {
        typedef BaseClass* (*ObjectCreationFunction)(void);
        std::map<IdType, ObjectCreationFunction> m_creationFunctions;

    public:
        ~GenericObjectFactory()
        {
            m_creationFunctions.clear();
        }


        template <class SubClass>
        bool Register(IdType id)
        {
            auto findIt = m_creationFunctions.find(id);
            if (findIt == m_creationFunctions.end())
            {
                m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
                return true;
            }

            return false;
        }

        BaseClass* Create(IdType id)
        {
            auto findIt = m_creationFunctions.find(id);
            if (findIt != m_creationFunctions.end())
            {
                ObjectCreationFunction pFunc = findIt->second;
                return pFunc();
            }

            return nullptr;
        }
    };

}
