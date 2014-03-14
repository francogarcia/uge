#include "GameEngineStd.h"

#include "GraphicalPreferences.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{
    GraphicalPreferences::GraphicalPreferences()
    {

    }

    GraphicalPreferences::~GraphicalPreferences()
    {

    }

    bool GraphicalPreferences::vInit(XMLElement* pXMLData)
    {
        LOG_ASSERT(pXMLData != nullptr && "Invalid initialization data!");

        XMLElement xmlElement = pXMLData->GetFirstChildElement("Window");
        if (xmlElement.IsGood())
        {
            xmlElement.GetUnsignedIntAttribute("width", &m_WindowSettings.width);
            xmlElement.GetUnsignedIntAttribute("height", &m_WindowSettings.height);
            xmlElement.GetUnsignedIntAttribute("pixel_depth", &m_WindowSettings.pixelDepth);
            xmlElement.GetBoolAttribute("vsync", &m_WindowSettings.bVSync);
            xmlElement.GetBoolAttribute("fullscreen", &m_WindowSettings.bFullScreen);

            xmlElement = pXMLData->GetFirstChildElement("Renderer");
            if (xmlElement.IsGood())
            {
                xmlElement.GetAttribute("name", &m_RendererSettings.name);

                xmlElement = pXMLData->GetFirstChildElement("Text");
                if (xmlElement.IsGood())
                {
                    XMLElement textElement = xmlElement.GetFirstChildElement("Font");
                    if (xmlElement.IsGood())
                    {
                        textElement.GetAttribute("resource", &m_TextSettings.fontName);
                        textElement.GetUnsignedIntAttribute("size", &m_TextSettings.fontSize);

                        XMLElement subtitlesElement = xmlElement.GetFirstChildElement("Subtitles");
                        if (xmlElement.IsGood())
                        {
                            subtitlesElement.GetBoolAttribute("enabled", &m_TextSettings.bUseSubtitles);

                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    const GraphicalPreferences::WindowSettings& GraphicalPreferences::GetWindowSettings() const
    {
        return m_WindowSettings;
    }

    const GraphicalPreferences::RendererSettings& GraphicalPreferences::GetRendererSettings() const
    {
        return m_RendererSettings;
    }

    const GraphicalPreferences::TextSettings& GraphicalPreferences::GetTextSettings() const
    {
        return m_TextSettings;
    }

    GraphicalPreferences::WindowSettings& GraphicalPreferences::GetWindowSettings()
    {
        return m_WindowSettings;
    }

}
