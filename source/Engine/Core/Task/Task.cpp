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

#include "GameEngineStd.h"

#include "Task.h"

namespace uge
{

    Task::Task() : m_State(Task::TaskState::Uninitialized),
        m_pChild(nullptr)
    {

    }

    Task::~Task()
    {
        if (m_pChild)
        {
            m_pChild->vOnAbort();
        }
    }

    void Task::Succeed()
    {
        assert(IsAlive() && "Task wasn't running or paused!");

        m_State = Task::TaskState::Succeeded;
    }

    void Task::Fail()
    {
        assert(IsAlive() && "Task wasn't running or paused!");

        m_State = Task::TaskState::Failed;
    }

    void Task::Pause()
    {
        if (m_State == Task::TaskState::Running)
        {
            m_State = Task::TaskState::Paused;
        }
    }

    void Task::UnPause()
    {
        if (m_State == Task::TaskState::Paused)
        {
            m_State = Task::TaskState::Running;
        }
    }

    const Task::TaskState Task::GetState() const
    {
        return m_State;
    }

    void Task::SetState(Task::TaskState newState)
    {
        m_State = newState;
    }

    bool Task::IsAlive() const
    {
        return (m_State == Task::TaskState::Running ||
                m_State == Task::TaskState::Paused);
    }

    bool Task::IsDead() const
    {
        return (m_State == Task::TaskState::Succeeded ||
                m_State == Task::TaskState::Failed ||
                m_State == Task::TaskState::Aborted);
    }

    bool Task::IsRemoved() const
    {
        return (m_State == Task::TaskState::Removed);
    }

    bool Task::IsPaused() const
    {
        return (m_State == Task::TaskState::Paused);
    }

    void Task::AttachChild(TaskSharedPointer pChild)
    {
        assert(pChild != nullptr && "Invalid child!");

        if (m_pChild)
        {
            m_pChild->AttachChild(pChild);
        }
        else
        {
            m_pChild = pChild;
        }
    }

    TaskSharedPointer Task::RemoveChild()
    {
        if (m_pChild != nullptr)
        {
            TaskSharedPointer pChild = m_pChild;
            m_pChild.reset();

            return pChild;
        }

        return TaskSharedPointer();
    }

    TaskSharedPointer Task::PeekChild()
    {
        return m_pChild;
    }

    void Task::vOnInit()
    {
        m_State = Task::TaskState::Running;
    }

    void Task::vOnSuccess()
    {

    }

    void Task::vOnFail()
    {

    }

    void Task::vOnAbort()
    {

    }

}
