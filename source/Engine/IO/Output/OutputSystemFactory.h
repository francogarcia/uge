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

#include <Core/PlayerProfile/OutputSettings/OutputSettings.h>
#include <Utilities/PatternTemplates.h>

#include "IOutput.h"

namespace uge
{

    class OutputSystemFactory
    {
    public:
        OutputSystemFactory();
        ~OutputSystemFactory();

        void Init();

        IOutput* CreateOutputSubsystem(const std::string& systemName, const OutputSettings& outputSettings);

    protected:
        virtual void vInitFactory();

    protected:
        GenericObjectFactory<IOutput, std::string> m_Factory;
    };

}
