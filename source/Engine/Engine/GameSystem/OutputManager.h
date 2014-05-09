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

#pragma once

#include <IO/Output/Audio/Audio.h>
#include <IO/Output/Audio/AudioTask.h>

#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
    typedef unsigned int OutputSystemID;
    const OutputSystemID NULL_OUTPUT_SYSTEM_ID = 0;

    class OutputManager
    {
    public:
        struct OutputSystem
        {
            OutputType type;
            IOutputSharedPointer pSystem;
        };

        typedef std::map<OutputSystemID, OutputSystem> OutputSubsystemMap;

        OutputManager();
        virtual ~OutputManager();

        virtual bool vInit();
        virtual bool vPostInit();
        virtual bool vDestroy();

        virtual bool vUpdate(const unsigned long timeElapsed);

        virtual bool vPreRender();
        virtual bool vRender();
        virtual bool vPostRender();

        OutputSystemID AddOutputSystem(IOutputSharedPointer pSystem);
        void RemoveOutputSystem(const OutputSystemID systemID);

        IOutputWeakPointer GetRawOutputSystem(const OutputSystemID systemID);
        template <class OutputSystemType>
        std::weak_ptr<OutputSystemType> GetOutputSystem(const OutputSystemID systemID);

        IOutputWeakPointer GetRawOutputSystem(const OutputType systemType);
        template <class OutputSystemType>
        std::weak_ptr<OutputSystemType> GetOutputSystem(const OutputType systemType);

        const OutputSubsystemMap& GetOutputSystems() const;
        OutputSubsystemMap& GetOutputSystems();

    private:
        OutputSystemID GetNextSystemID();

    protected:
        // Systems
         OutputSubsystemMap m_Systems;

        OutputSystemID m_LastSystemID;
    };

    template <class OutputSystemType>
    std::weak_ptr<OutputSystemType> OutputManager::GetOutputSystem(const OutputSystemID systemID)
    {
        IOutputWeakPointer pWeakSystem = GetRawOutputSystem(systemID);
        if (pWeakSystem.expired())
        {
            return std::weak_ptr<OutputSystemType>();
        }

        // There is no way to cast a weak pointer from one type to another.
        // Convert to shared pointer first then cast it to the template type.
        std::shared_ptr<OutputSystemType> pSystem = std::static_pointer_cast<OutputSystemType>(pWeakSystem.lock());

        return std::weak_ptr<OutputSystemType>(pSystem);
    }

    template <class OutputSystemType>
    std::weak_ptr<OutputSystemType> OutputManager::GetOutputSystem(const OutputType systemType)
    {
        IOutputWeakPointer pWeakSystem = GetRawOutputSystem(systemType);
        if (pWeakSystem.expired())
        {
            return std::weak_ptr<OutputSystemType>();
        }

        // There is no way to cast a weak pointer from one type to another.
        // Convert to shared pointer first then cast it to the template type.
        std::shared_ptr<OutputSystemType> pSystem = std::static_pointer_cast<OutputSystemType>(pWeakSystem.lock());

        return std::weak_ptr<OutputSystemType>(pSystem);
    }

}
