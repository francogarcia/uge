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

#include <Core/Resource/ResourceCache.h>
#include <IO/Output/IOutput.h>

#include "AudioBuffer.h"
#include "AudioResource.h"
#include "AudioTypes.h"

namespace uge
{

    class AudioResourceExtraData;
    class IAudio;
    typedef std::shared_ptr<IAudio> IAudioSharedPointer;
    typedef std::weak_ptr<IAudio> IAudioWeakPointer;

    class IAudio : public IOutput
    {
    public:
        virtual ~IAudio();

        virtual bool vIsActive() = 0;

        virtual bool vInit(const OutputSettings& outputSettings) = 0;
        virtual bool vPostInit() = 0;
        virtual bool vDestroy() = 0;

        virtual bool vUpdate(const unsigned long timeElapsed) = 0;

        virtual bool vPreRender() = 0;
        virtual bool vRender() = 0;
        virtual bool vPostRender() = 0;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) = 0;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) = 0;

        virtual void vStopAllSounds() = 0;
        virtual void vPauseAllSounds() = 0;
        virtual void vResumeAllSounds() = 0;

        virtual const std::string vGetName() const = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

    class Audio : public IAudio
    {
    public:
        Audio();
        virtual ~Audio();

        virtual bool vIsActive() = 0;

        virtual bool vInit(const OutputSettings& outputSettings) = 0;
        virtual bool vPostInit() = 0;
        virtual bool vDestroy() override;

        virtual bool vUpdate(const unsigned long timeElapsed) = 0;

        virtual bool vPreRender() = 0;
        virtual bool vRender() = 0;
        virtual bool vPostRender() = 0;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) = 0;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) = 0;

        virtual void vStopAllSounds() override;
        virtual void vPauseAllSounds() override;
        virtual void vResumeAllSounds() override;

        bool HasSoundCard();
        bool IsPaused() const;

        virtual OutputType vGetOutputType() const override
        {
            return OutputType::Aural;
        }

    protected:
        typedef std::list<IAudioBuffer*> AudioBufferList;

        AudioBufferList m_Samples;
        bool m_bAllPaused;
        bool m_bIsInitialized;
    };

}
