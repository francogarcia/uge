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
 */

#pragma once

#include "InputTypes.h"

namespace uge
{

    namespace InputMapping
    {
        class GameCommand
        {
        public:
            GameCommand();
            ~GameCommand();

            void Init(const std::string& gameCommandListFilename);

            Action GetAction(const std::string& actionName) const;
            State GetState(const std::string& stateName) const;
            Range GetRange(const std::string& rangeName) const;

        private:
            std::map<std::string, Action> m_Actions;
            std::map<std::string, State> m_States;
            std::map<std::string, Range> m_Ranges;
        };
    }

}
