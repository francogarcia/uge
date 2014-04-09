/*
  * (c) Copyright 2014 Franco Eus�bio Garcia
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

//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alext.h>

#include <cTinyOAL.h>

#include <IO/Output/Audio/Audio.h>

namespace uge
{
    class OpenALSoftAudio : public Audio
    {
    public:
        OpenALSoftAudio(unsigned int totalBuffers = 4);
        ~OpenALSoftAudio();

        virtual bool vIsActive() override;

        virtual void vUpdate(unsigned long timeElapsed) override;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) override;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) override;

        virtual bool vInit() override;
        virtual bool vDestroy() override;

    private:
        TinyOAL::cTinyOAL* m_pTinyOAL;
        unsigned int m_TotalBuffers;
        unsigned int m_TotalSoundsBeingPlayed;
    };
}
