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
 */

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#pragma once

#include <Core/Resource/ResourceCache.h>
#include <Utilities/Math/Vector.h>

#include "AudioTypes.h"

namespace uge
{

    class AudioResourceExtraData;

    class IAudioBuffer;
    typedef std::shared_ptr<IAudioBuffer> IAudioBufferSharedPointer;

    class IAudioBuffer
    {
    public:
        IAudioBuffer();
        virtual ~IAudioBuffer();

        virtual void* vGet() = 0;
        virtual ResourceHandleSharedPointer vGetResource() = 0;
        virtual bool vOnRestore() = 0;

        virtual bool vPlay(float fVolume, bool bLoop) = 0;
        virtual bool vPause() = 0;
        virtual bool vStop() = 0;
        virtual bool vResume() = 0;

        virtual bool vTogglePause() = 0;
        
        virtual bool vIsPlaying() = 0;
        virtual bool vIsLooping() const = 0;

        virtual void vSetVolume(float fVolume) = 0;
        virtual float vGetVolume() const = 0;

        virtual void vSetProgress(float fAudioPosition) = 0;
        virtual float vGetProgress() = 0;

        virtual void vSetPosition(const Vector3& position) = 0;
        virtual const Vector3& vGetPosition() const = 0;
    };

    class AudioBuffer;
    typedef std::shared_ptr<AudioBuffer> AudioBufferSharedPointer;

    class AudioBuffer : public IAudioBuffer
    {
    public:
        virtual ~AudioBuffer();

        virtual void* vGet() = 0;
        virtual ResourceHandleSharedPointer vGetResource() override;
        virtual bool vOnRestore() = 0;

        virtual bool vPlay(float fVolume, bool bLoop) = 0;
        virtual bool vPause() = 0;
        virtual bool vStop() = 0;
        virtual bool vResume() = 0;

        virtual bool vTogglePause() = 0;

        virtual bool vIsPlaying() = 0;
        virtual bool vIsLooping() const override;
        
        virtual void vSetVolume(float fVolume) = 0;
        virtual float vGetVolume() const override;

        virtual void vSetProgress(float fAudioPosition) = 0;
        virtual float vGetProgress() = 0;

        virtual void vSetPosition(const Vector3& position) = 0;
        virtual const Vector3& vGetPosition() const override;

    protected:
        AudioBuffer(ResourceHandleSharedPointer pAudioBufferResource);

        ResourceHandleSharedPointer m_pResource;
        bool m_bIsPaused;
        bool m_bIsLooping;
        float m_fVolume;
        Vector3 m_Position;
    };

}
