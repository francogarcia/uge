#include <Utilities/System/SystemInformation.h>

int main()
{
#ifdef _DEBUG
    int debugFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    debugFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
    _CrtSetDbgFlag(debugFlag);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    {
#endif

        // System information gathering
        uge::SystemInformation systemInfo;
        systemInfo.Init();

        unsigned long long cpuSpeed = systemInfo.GetCPUSpeedInMHz();
        unsigned int cpuCores = systemInfo.GetTotalCPUCores();
        long long totalRAM = systemInfo.GetSystemRAMInMB();
        long long freeRAM = systemInfo.GetAvailableSystemRAMInMB();
        std::vector<std::string> diskNames = systemInfo.GetDiskNames();
        std::vector<unsigned long long> diskFreeSpace = systemInfo.GetFreeDiskSpaceInBytes();

        systemInfo.Destroy();

#ifdef _DEBUG
    }
    std::cerr << "Memory Leaks? " << ((_CrtDumpMemoryLeaks() == 1) ? "yes" : "no") << std::endl;

#endif

    return 0;
}
