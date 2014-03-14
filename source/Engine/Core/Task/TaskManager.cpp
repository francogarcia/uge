/**
 * @file TaskManager.cpp
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "GameEngineStd.h"

#include "TaskManager.h"

namespace uge
{

    TaskManager::TaskManager()
    {

    }

    TaskManager::~TaskManager()
    {
        ClearAllTasks();
    }

    unsigned int TaskManager::UpdateTasks(const unsigned long dt)
    {
        unsigned short int successfulTaskCount = 0;
        unsigned short int failedTaskCount = 0;

        TaskList::iterator taskIt = m_TaskList.begin();
        while (taskIt != m_TaskList.end())
        {
            TaskSharedPointer pCurrentTask = *taskIt;

            TaskList::iterator currentTaskIt = taskIt;
            ++taskIt;

            if (pCurrentTask->GetState() == Task::TaskState::Uninitialized)
            {
                pCurrentTask->vOnInit();
            }

            if (pCurrentTask->GetState() == Task::TaskState::Running)
            {
                pCurrentTask->vOnUpdate(dt);
            }

            if (pCurrentTask->IsDead())
            {
                switch (pCurrentTask->GetState())
                {
                    case Task::TaskState::Succeeded:
                    {
                        pCurrentTask->vOnSuccess();

                        TaskSharedPointer pChildTask = pCurrentTask->RemoveChild();
                        if (pChildTask != nullptr)
                        {
                            AttachTask(pChildTask);
                        }
                        else
                        {
                            ++successfulTaskCount;
                        }

                        break;
                    }

                    case Task::TaskState::Failed:
                    {
                        pCurrentTask->vOnFail();
                        ++failedTaskCount;

                        break;
                    }

                    case Task::TaskState::Aborted:
                    {
                        pCurrentTask->vOnAbort();
                        ++failedTaskCount;

                        break;
                    }
                }

                m_TaskList.erase(currentTaskIt);
            }
        }

        return ((successfulTaskCount << 16) | failedTaskCount);
    }

    TaskWeakPointer TaskManager::AttachTask(TaskSharedPointer pTask)
    {
        m_TaskList.push_back(pTask);

        return TaskWeakPointer(pTask);
    }

    void TaskManager::AbortAllTasks(const bool bAbortImmediately)
    {
        TaskList::iterator taskIt = m_TaskList.begin();
        while (taskIt != m_TaskList.end())
        {
            TaskList::iterator currentTaskIt = taskIt;
            ++taskIt;

            TaskSharedPointer pTask = *currentTaskIt;
            if (pTask->IsAlive())
            {
                pTask->SetState(Task::TaskState::Aborted);

                if (bAbortImmediately)
                {
                    pTask->vOnAbort();
                    m_TaskList.erase(currentTaskIt);
                }
            }
        }
    }

    unsigned int TaskManager::GetTaskCount() const
    {
        return m_TaskList.size();
    }

    void TaskManager::ClearAllTasks()
    {
        m_TaskList.clear();
    }

}
