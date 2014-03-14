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
