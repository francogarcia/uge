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
 * @file PatternTemplates.h
 *  Defines templates for design patterns.
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
