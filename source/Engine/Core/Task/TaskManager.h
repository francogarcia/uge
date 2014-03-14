/**
 * @file TaskManager.h
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Mike McShaffry (Mr. Mike)
 * David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include "Task.h"

namespace uge
{

    class TaskManager
    {
    public:
        TaskManager();
        ~TaskManager();

        unsigned int UpdateTasks(const unsigned long dt);
        TaskWeakPointer AttachTask(TaskSharedPointer pTask);
        void AbortAllTasks(const bool bAbortImmediately);

        unsigned int GetTaskCount() const;


    private:
        void ClearAllTasks();

        typedef std::list<TaskSharedPointer> TaskList;

        TaskList m_TaskList;
    };

}
