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

#include <yse.hpp>

#include <IO/Output/Audio/AudioBuffer.h>


namespace uge
{
    class YSEAudioBuffer : public AudioBuffer
    {
    public:
        YSEAudioBuffer(ResourceHandleSharedPointer pAudioBufferResource);
        ~YSEAudioBuffer();

        virtual void* vGet() override;
        virtual bool vOnRestore() override;

        virtual bool vPlay(float fVolume, bool bLoop) override;
        virtual bool vPause() override;
        virtual bool vStop() override;
        virtual bool vResume() override;

        virtual bool vTogglePause() override;

        virtual bool vIsPlaying() override;
        virtual bool vIsLooping() const override;

        virtual void vSetVolume(float fVolume) override;
        virtual float vGetVolume() const override;

        virtual void vSetProgress(float fAudioPosition) override;
        virtual float vGetProgress() override;

        virtual void vSetPosition(const Vector3& position) override;

    private:
        YSE::sound* m_pAudioBuffer;
    };
}
