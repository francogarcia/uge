#pragma once

namespace uge
{
    enum class AudioType : unsigned int
    {
        SoundEffect,
        AmbientSoundEffect,
        Music,
        Speech
    };

    enum class AudioFileType : unsigned char
    {
        DEFAULT_TYPE,
        OGG = DEFAULT_TYPE,
        WAVE,
        MIDI,
        FLAC,
        AIFF,
        RAW,
        MP3,

        COUNT,
        UNKNOWN
    };

    // The size of this array is SoundType::SOUND_TYPE_COUNT. Elements are in the same order.
    extern char* g_pSoundTypeExtensions[];
}
