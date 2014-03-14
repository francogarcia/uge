#include <Utilities/System/Clock.h>
#include <Utilities/System/Time.h>

#include <iostream>

int main()
{
#ifdef _DEBUG
    int debugFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    debugFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
    _CrtSetDbgFlag(debugFlag);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    {
#endif

        uge::Time::Clock clock;
        clock.Init();

        uge::Time::TimePoint startTime = uge::Time::GetTime();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        uge::Time::TimePoint finalTime = uge::Time::GetTime();

        std::cout << "Time difference:" << std::endl;
        std::cout << "In seconds: " << uge::Time::GetDeltaAsSeconds(finalTime, startTime) << " s." << std::endl;
        std::cout << "In milliseconds: " << uge::Time::GetDeltaAsMilliseconds(finalTime, startTime) << " ms." << std::endl;
        std::cout << "In microseconds: " << uge::Time::GetDeltaAsMicroseconds(finalTime, startTime) << " us." << std::endl;
        std::cout << "In nanoseconds: " << uge::Time::GetDeltaAsNanoseconds(finalTime, startTime) << " ns." << std::endl;

        std::cout << "Time elapsed since the clock creation: " << clock.GetTimeElapsed() << "s." << std::endl;
        
        clock.Init(); // Reset the clock.
        std::cout << "Time elapsed since the clock was reinitialized: " << clock.GetTimeElapsed() << "s." << std::endl;

#ifdef _DEBUG
    }
    std::cerr << "Memory Leaks? " << ((_CrtDumpMemoryLeaks() == 1) ? "yes" : "no") << std::endl;

#endif

    return 0;
}
