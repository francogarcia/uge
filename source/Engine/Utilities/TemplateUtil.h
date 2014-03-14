#pragma once

#include "GameEngineStd.h"

namespace uge
{

    namespace util
    {
        template <class Type>
        std::shared_ptr<Type> MakeSharedPointer(std::weak_ptr<Type> pWeakPtr)
        {
            if (!pWeakPtr.expired())
            {
                return std::shared_ptr<Type>(pWeakPtr);
            }
            else
            {
                return std::shared_ptr<Type>();
            }
        }
    }

}
