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

#include <IO/Output/Audio/Audio.h>

namespace uge
{
    class YSEAudio : public Audio
    {
    public:
        /// The name of the subsystem.
        static const char* g_Name;

        YSEAudio();
        ~YSEAudio();

        virtual bool vInit(const OutputSettings& outputSettings) override;
        virtual bool vPostInit() override;
        virtual bool vDestroy() override;

        virtual bool vUpdate(const unsigned long timeElapsed) override;

        virtual bool vPreRender() override;
        virtual bool vRender() override;
        virtual bool vPostRender() override;

        virtual bool vIsActive() override;

        virtual IAudioBuffer* vInitAudioBuffer(ResourceHandleSharedPointer pHandle) override;
        virtual void vReleaseAudioBuffer(IAudioBuffer* pAudioBuffer) override;

        virtual const std::string vGetName() const override;

    private:

    };
}
