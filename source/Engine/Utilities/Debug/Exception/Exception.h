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

#include "GameEngineStd.h"

/**
 * @class Exeception
 * Base Exception class.
 */
class Exception : public std::exception
{
public:
    /**
     *  Throws an exception when created, with the errorMessage message.
     * @param errorMessage : the error message that will be shown.
     */
    Exception(const std::string& errorMessage) throw()
        : errorMessage(errorMessage)
    {

    }

    /**
     *  Destructor.
     */
    virtual ~Exception()
    {

    }

protected:
    /// The exception's error message.
    std::string errorMessage;
};

/**
 * @class Exeception
 * Base Run-Time Error Exception class.
 */
class RunTimeError : public std::runtime_error
{
public:
    /**
     *  Throws an exception when created, with the errorMessage message.
     * @param errorMessage : a error message.
     */
    RunTimeError(const std::string& errorMessage) : std::runtime_error(errorMessage)
    {

    }
};
