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
