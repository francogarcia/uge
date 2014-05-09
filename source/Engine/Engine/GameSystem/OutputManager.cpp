/*
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

#include "GameEngineStd.h"

#include "OutputManager.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    OutputManager::OutputManager()
        : m_LastSystemID(NULL_OUTPUT_SYSTEM_ID)
    {

    }

    OutputManager::~OutputManager()
    {

    }

    bool OutputManager::vInit()
    {
        return true;
    }

    bool OutputManager::vPostInit()
    {
        return true;
    }

    bool OutputManager::vDestroy()
    {
        bool bSuccess = true;
        for (auto& system : m_Systems)
        {
            IOutputSharedPointer pSystem = system.second.pSystem;
            bool bSystemSuccess = pSystem->vDestroy();
            if (!bSystemSuccess)
            {
                bSuccess = false;

                LOG_ASSERT("Error destroying the system!");
            }

            pSystem.reset();
        }

        m_LastSystemID = NULL_OUTPUT_SYSTEM_ID;

        return bSuccess;
    }

    bool OutputManager::vUpdate(const unsigned long timeElapsed)
    {
        bool bSuccess = true;
        for (auto& system : m_Systems)
        {
            IOutputSharedPointer pSystem = system.second.pSystem;
            bool bSystemSuccess = pSystem->vUpdate(timeElapsed);
            if (!bSystemSuccess)
            {
                bSuccess = false;

                LOG_ASSERT("Error updating the system!");
            }
        }

        return bSuccess;
    }

    bool OutputManager::vPreRender()
    {
        bool bSuccess = true;
        for (auto& system : m_Systems)
        {
            IOutputSharedPointer pSystem = system.second.pSystem;
            bool bSystemSuccess = pSystem->vPreRender();
            if (!bSystemSuccess)
            {
                bSuccess = false;

                LOG_ASSERT("Error pre-rendering the system!");
            }
        }

        return bSuccess;
    }

    bool OutputManager::vRender()
    {
        bool bSuccess = true;
        for (auto& system : m_Systems)
        {
            IOutputSharedPointer pSystem = system.second.pSystem;
            bool bSystemSuccess = pSystem->vRender();
            if (!bSystemSuccess)
            {
                bSuccess = false;

                LOG_ASSERT("Error rendering the system!");
            }
        }

        return bSuccess;
    }

    bool OutputManager::vPostRender()
    {
        bool bSuccess = true;
        for (auto& system : m_Systems)
        {
            IOutputSharedPointer pSystem = system.second.pSystem;
            bool bSystemSuccess = pSystem->vPostRender();
            if (!bSystemSuccess)
            {
                bSuccess = false;

                LOG_ASSERT("Error post-rendering the system!");
            }
        }

        return bSuccess;
    }

    OutputSystemID OutputManager::AddOutputSystem(IOutputSharedPointer pSystem)
    {
        assert(pSystem != nullptr && "Invalid output system!");

        OutputSystemID systemID = GetNextSystemID();
        assert(systemID != NULL_OUTPUT_SYSTEM_ID && "Error creating the first output system or too many systems were created!");

        OutputSystem system;
        system.pSystem = pSystem;
        system.type = pSystem->vGetOutputType();

        m_Systems.insert(std::make_pair(systemID, system));

        return systemID;
    }

    void OutputManager::RemoveOutputSystem(const OutputSystemID systemID)
    {
        auto& system(m_Systems.find(systemID));
        if (system == m_Systems.end())
        {
            return;
        }

        system->second.pSystem->vDestroy();
        m_Systems.erase(system);
    }

    IOutputWeakPointer OutputManager::GetRawOutputSystem(const OutputSystemID systemID)
    {
        auto& system(m_Systems.find(systemID));
        if (system == m_Systems.end())
        {
            return IOutputWeakPointer();
        }

        IOutputSharedPointer pSystem = system->second.pSystem;
        assert(pSystem != nullptr);

        return IOutputWeakPointer(pSystem);
    }

    IOutputWeakPointer OutputManager::GetRawOutputSystem(const OutputType systemType)
    {
        for (auto& system : m_Systems)
        {
            OutputType outputType = system.second.type;
            if (systemType == outputType)
            {
                IOutputSharedPointer pSystem = system.second.pSystem;
                assert(pSystem != nullptr);

                return IOutputWeakPointer(pSystem);
            }
        }

        LOG_ERROR("No system was found!");

        return IOutputWeakPointer();
    }

    const OutputManager::OutputSubsystemMap& OutputManager::GetOutputSystems() const
    {
        return m_Systems;
    }

    OutputManager::OutputSubsystemMap& OutputManager::GetOutputSystems()
    {
        return m_Systems;
    }

    OutputSystemID OutputManager::GetNextSystemID()
    {
        return ++m_LastSystemID;
    }

}
