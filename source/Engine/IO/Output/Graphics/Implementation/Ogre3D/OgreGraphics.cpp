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

#include "GameEngineStd.h"

#include "OgreGraphics.h"

#include <OGRE/OgreUTFString.h>

#include <Utilities/Debug/Logger.h>
#include <Utilities/String/StringUtil.h>

namespace uge
{
    OgreGraphics::OgreGraphics(const std::wstring& windowName, const OutputSettings& outputSettings)
        : m_WindowName(windowName),
          m_OutputSettings(outputSettings),
          m_pRoot(nullptr),
          m_pWindow(nullptr),
          m_pViewport(nullptr)
    {

    }

    OgreGraphics::~OgreGraphics()
    {

    }

    bool OgreGraphics::vInit()
    {
        Ogre::String m_UserConfiguration;
        Ogre::String m_PluginsConfiguration;
        Ogre::String m_DebugLogFile;

#ifdef _DEBUG
        m_UserConfiguration = "ogre/debug/user_config_d.cfg";
        m_PluginsConfiguration = "ogre/debug/plugins_d.cfg";
        m_DebugLogFile = "ogre/debug/log_d.txt";
#else
        m_UserConfiguration = "ogre/release/user_config.cfg";
        m_PluginsConfiguration = "ogre/release/plugins.cfg";
        m_DebugLogFile = "ogre/release/log.txt";
#endif

        m_pRoot = new Ogre::Root(m_PluginsConfiguration, m_UserConfiguration, m_DebugLogFile);
        //if (!m_pRoot->showConfigDialog())
        //{
        //    // User cancelled the dialog box.
        //    return false;
        //}

        // A list of supported render systems is avaiable at: http://www.ogre3d.org/tikiwiki/Ogre+Wiki+Tutorial+Framework#Setup
        // FIXME: DirectX 10 and 11 are not working. Check http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Basic+Tutorial+6
        // later.
        const OutputSubsystemSettings::OutputSubsystemSettingsData& rendererSettings
            = m_OutputSettings.GetOutputSettingsData().subsystems["ogre"].GetOutputSubsystemSettingsData();

        auto& findIt = rendererSettings.settings.find("renderer");
        std::string rendererName = findIt->second;
        Ogre::RenderSystem* pRenderSystem = m_pRoot->getRenderSystemByName(rendererName.c_str());
        if (pRenderSystem->getName() != rendererName)
        {
            LOG_ERROR("Graphical renderer not found!");

            return false;
        }

        const WindowSettings::WindowSettingsData& windowSettings = m_OutputSettings.GetOutputSettingsData().window.GetWindowSettingsData();
        pRenderSystem->setConfigOption("Full Screen", windowSettings.bFullScreen ? "Yes" : "No");
        pRenderSystem->setConfigOption("VSync", windowSettings.bVSync ? "Yes" : "No");
        std::string videoMode;
        videoMode = IntToString(windowSettings.width) + " x " + IntToString(windowSettings.height) + " @ " + IntToString(windowSettings.pixelDepth) + "-bit colour";
        pRenderSystem->setConfigOption("Video Mode", videoMode);

        m_pRoot->setRenderSystem(pRenderSystem);

        m_pWindow = m_pRoot->initialise(true, Ogre::UTFString(m_WindowName));
        windowResized(m_pWindow);
        Ogre::WindowEventUtilities::addWindowEventListener(m_pWindow, this);
        m_pRoot->addFrameListener(this);

        // Allow the window to be drawn when it lose focus.
        m_pWindow->setDeactivateOnFocusChange(false);

        return true;
    }

    bool OgreGraphics::vPostInit()
    {
        return true;
    }

    bool OgreGraphics::vDestroy()
    {
        Ogre::WindowEventUtilities::removeWindowEventListener(m_pWindow, this);
        //windowClosed(m_pWindow);
        SAFE_DELETE(m_pRoot);

        m_pRoot = nullptr;
        m_pWindow = nullptr;
        m_pViewport = nullptr;

        return true;
    }

    bool OgreGraphics::vUpdate(const unsigned long timeElapsed)
    {
        return true;
    }

    bool OgreGraphics::vPreRender()
    {
        Ogre::WindowEventUtilities::messagePump();

        if (m_pWindow->isClosed())
        {
            return false;
        }

        return true;
    }

    bool OgreGraphics::vRender()
    {
        return true;
    }

    bool OgreGraphics::vPostRender()
    {
        return true;
    }

    void OgreGraphics::vSetBackgroundColor(const char r, const char g, const char b, const char a)
    {
        m_pViewport->setBackgroundColour(Ogre::ColourValue(r / 255.0f,
                                                           g / 255.0f,
                                                           b / 255.0f,
                                                           a / 255.0f));
    }

    void OgreGraphics::vSetWorldTransform(const Matrix4& worldTransform)
    {

    }

    void OgreGraphics::vSetViewTransform(const Matrix4& viewTransform)
    {

    }

    void OgreGraphics::vSetProjectionTransform(const Matrix4& projectionTransform)
    {

    }

    // Ogre3D overloads.

    bool OgreGraphics::frameStarted(const Ogre::FrameEvent& frameEvent)
    {
        return true;
    }

    bool OgreGraphics::frameEnded(const Ogre::FrameEvent& frameEvent)
    {
        return true;
    }

    bool OgreGraphics::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
    {
        if (m_pWindow->isClosed())
        {
            return false;
        }

        return true;
    }

    void OgreGraphics::windowResized(Ogre::RenderWindow* pRenderWindow)
    {
        unsigned int windowWidth, windowHeight, windowDepth;
        int windowTopPosition, windowLeftPosition;
        m_pWindow->getMetrics(windowWidth, windowHeight, windowDepth, windowLeftPosition, windowTopPosition);

        WindowSettings::WindowSettingsData& windowSettings = m_OutputSettings.GetOutputSettingsData().window.GetWindowSettingsData();
        windowSettings.width = windowWidth;
        windowSettings.height = windowHeight;
    }

    void OgreGraphics::windowClosed(Ogre::RenderWindow* pRenderWindow)
    {
        if (pRenderWindow == m_pWindow)
        {
            // Do additional clean up.
        }
    }

    Ogre::Root* OgreGraphics::GetOgreRoot()
    {
        return m_pRoot;
    }

    void OgreGraphics::AddViewport(Ogre::Camera* pOgreCamera)
    {
        m_pViewport = m_pWindow->addViewport(pOgreCamera);
        m_pViewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
    }
}
