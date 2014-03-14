#include <Utilities/Debug/Logger.h>

/*

LogConfig.xml

<LogConfig>
    <Log tag="TAG"             debugger="1" file="1"/>
    <Log tag="Debugger only"   debugger="1" file="0"/>
    <Log tag="Log file only"   debugger="0" file="1"/>
</LogConfig>

 */

int main()
{
    // Create the log file using the configuration file.
    // The log file is created in "data/debug/log{_d}.log".
    uge::debug::log::Init("data/debug/LogConfig.xml");

    // The logger can be used with the following function:
    uge::debug::log::Log("TAG", "Error message", __FUNCTION__, __FILE__, __LINE__);
    // The TAG must exists - it can be one of the default ones or defined in the log configuration file.
    
    // Or with these macros:
    LOG_INFO("Information: "); // Uses INFO tag.
    LOG_WARNING("Warning: "); // Uses WARNING tag.
    
    LOG_ASSERT(true && "Message"); // Logs the assertion case it evaluates to false.    
    LOG_FATAL("Fatal Error!"); // The game cannot continue to run if this happens.
    LOG_ERROR("Error: "); // Serious, but non-fatal errors.
    
    // Destroy the log file.
    uge::debug::log::Destroy();

    return 0;
}
