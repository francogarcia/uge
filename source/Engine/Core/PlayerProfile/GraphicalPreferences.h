#pragma once

#include <Utilities/File/XMLFile.h>

namespace uge
{
    class GraphicalPreferences
    {
    public:
        struct WindowSettings
        {
            unsigned int width;
            unsigned int height;
            unsigned int pixelDepth;
            bool bVSync;
            bool bFullScreen;
        };

        struct RendererSettings
        {
            std::string name;
        };

        struct TextSettings
        {
            std::string fontName;
            unsigned int fontSize;
            bool bUseSubtitles;
        };

        GraphicalPreferences();
        virtual ~GraphicalPreferences();

        virtual bool vInit(XMLElement* pXMLData);

        const GraphicalPreferences::WindowSettings& GetWindowSettings() const;
        const GraphicalPreferences::RendererSettings& GetRendererSettings() const;
        const GraphicalPreferences::TextSettings& GetTextSettings() const;

        // Allow window to be resized.
        GraphicalPreferences::WindowSettings& GetWindowSettings();

    protected:
        GraphicalPreferences::WindowSettings m_WindowSettings;
        GraphicalPreferences::RendererSettings m_RendererSettings;
        GraphicalPreferences::TextSettings m_TextSettings;
    };
}
