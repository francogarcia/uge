/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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

namespace uge
{

    class BaseGameLogic;

    class IGameState
    {
    public:
        IGameState();
        virtual ~IGameState();

        virtual bool vInit(BaseGameLogic* pGameLogic) = 0;
        virtual bool vTailorToProfile(const std::string& xmlResourceFilename) = 0;
        virtual bool vDestroy() = 0;

        virtual bool vOnUpdate(unsigned long timeElapsed) = 0;
        virtual bool vOnRender(unsigned long timeElapsed) = 0;

        virtual const std::string vGetName() const = 0;
    };

}
