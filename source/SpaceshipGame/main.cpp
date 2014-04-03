#include "SpaceshipGameStd.h"

#define UGE_ENABLE_PHYSICS  1
//#define UGE_DEBUG_PHYSICS   1

#define SG_USE_DEVELOPMENT_RESOURCE_FILE 1

// Game specific headers
#include "Application/Application.h"

// UGE headers.
#include <Utilities/Debug/Logger.h>

int main()
{
    uge::debug::log::Init("data/debug/LogConfig.xml");
    //LOG_INFO("Game started.");

    sg::Application game;
    game.vInit();
    game.vRun();
    game.vDestroy();

    //LOG_INFO("Game finished.");
    uge::debug::log::Destroy();

    return 0;
}
