#include <Core/Task/Task.h>
#include <Core/Task/TaskManager.h>
#include <Core/Task/DefaultTasks/TimeDelayTask.h>

#include <Utilities/System/Time.h>

class PrintTask : public uge::Task
{
public:
    explicit PrintTask(std::string message, const unsigned long times)
    {
        m_Message = message;
        m_Times = times;
        m_Counter = 0;
    }

protected:
    virtual void vOnUpdate(const unsigned long dt)
    {
        if (m_Counter < m_Times)
        {
            std::cout << m_Message << std::endl;
            ++m_Counter;
        }
        else
        {
            Succeed();
        }
    }

private:
    unsigned long m_Times;
    unsigned long m_Counter;
    std::string m_Message;
};

int main()
{
#ifdef _DEBUG
    int debugFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    debugFlag |= _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF;
    _CrtSetDbgFlag(debugFlag);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    {
#endif

        // Tasks
        uge::TaskManager m_TaskManager;

        uge::TaskSharedPointer pDelayTask(LIB_NEW uge::TimeDelayTask(5000));
        m_TaskManager.AttachTask(pDelayTask);

        uge::TaskSharedPointer pAnotherDelayTask(LIB_NEW uge::TimeDelayTask(1000));
        pDelayTask->AttachChild(pAnotherDelayTask);

        uge::TaskSharedPointer pTask(LIB_NEW PrintTask("foo", 100));
        m_TaskManager.AttachTask(pTask);

        pTask.reset(LIB_NEW PrintTask("bar", 150));
        m_TaskManager.AttachTask(pTask);

        uge::Time::TimePoint startTime = uge::Time::GetTime();

        while (m_TaskManager.GetTaskCount() > 0)
        {
            uge::Time::TimePoint currentTime = uge::Time::GetTime();
#if _DEBUG
            unsigned long deltaMilliseconds = uge::Time::GetDeltaAsMilliseconds(currentTime, startTime);
            std::cout << "Time elapsed: " << deltaMilliseconds << " ms." << std::endl;
#else
            // Milliseconds times is too fast for those tasks.
            unsigned long deltaMilliseconds = Time::GetDeltaAsNanoseconds(currentTime, startTime);
            deltaMilliseconds /= 100;
            std::cout << "Time elapsed: " << deltaMilliseconds << " ns." << std::endl;
#endif

            m_TaskManager.UpdateTasks(deltaMilliseconds);

            startTime = currentTime;
        }

#ifdef _DEBUG
    }
    std::cerr << "Memory Leaks? " << ((_CrtDumpMemoryLeaks() == 1) ? "yes" : "no") << std::endl;

#endif

    return 0;
}
