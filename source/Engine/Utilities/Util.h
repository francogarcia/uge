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

#pragma once

#include "Utilities/String/StringUtil.h"

namespace uge
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
