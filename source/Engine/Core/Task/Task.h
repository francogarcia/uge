/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

namespace uge
{

    // Forward declarations.
    class Task;
    class TaskManager;

    typedef std::shared_ptr<Task> TaskSharedPointer;
    typedef std::weak_ptr<Task> TaskWeakPointer;

    class Task
    {
    public:
        enum class TaskState : unsigned char
        {
            Uninitialized = 0,
            Removed,
            Running,
            Paused,
            Succeeded,
            Failed,
            Aborted
        };

        Task();
        ~Task();

        void Succeed();
        void Fail();

        void Pause();
        void UnPause();

        const Task::TaskState GetState() const;
        bool IsAlive() const;
        bool IsDead() const;
        bool IsRemoved() const;
        bool IsPaused() const;

        void AttachChild(TaskSharedPointer pChild);
        TaskSharedPointer RemoveChild();
        TaskSharedPointer PeekChild();

    protected:
        virtual void vOnInit();
        virtual void vOnUpdate(const unsigned long dt) = 0;
        virtual void vOnSuccess();
        virtual void vOnFail();
        virtual void vOnAbort();

    private:
        friend class TaskManager;

        void SetState(Task::TaskState newState);

        TaskState m_State;
        TaskSharedPointer m_pChild;
    };

}
