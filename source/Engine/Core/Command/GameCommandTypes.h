#pragma once

#include "GameEngineStd.h"

namespace uge
{
    // UID, like the event.
    typedef unsigned int GameCommandID;

    enum class GameCommandType : unsigned int
    {
        ACTION,
        STATE,
        RANGE,

        INVALID
    };
}
