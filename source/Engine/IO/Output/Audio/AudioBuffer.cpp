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

#include "GameEngineStd.h"

#include "Audio.h"

namespace uge
{

    IAudioBuffer::IAudioBuffer()
    {

    }

    IAudioBuffer::~IAudioBuffer()
    {

    }

    AudioBuffer::AudioBuffer(ResourceHandleSharedPointer pAudioBufferResource)
        : m_pResource(pAudioBufferResource), m_bIsPaused(true), m_bIsLooping(false), m_fVolume(0.0f), m_Position(0.0f, 0.0f, 0.0f)
    {

    }

    AudioBuffer::~AudioBuffer()
    {

    }

    ResourceHandleSharedPointer AudioBuffer::vGetResource()
    {
        return m_pResource;
    }

    bool AudioBuffer::vIsLooping() const
    {
        return m_bIsLooping;
    }

    float AudioBuffer::vGetVolume() const
    {
        return m_fVolume;
    }

    const Vector3& AudioBuffer::vGetPosition() const
    {
        return m_Position;
    }

}
