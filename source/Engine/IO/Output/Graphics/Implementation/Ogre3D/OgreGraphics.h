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

#include <OGRE/Ogre.h>

#include <Core/PlayerProfile/OutputSettings/OutputSettings.h>

#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
    class OgreGraphics;
    typedef std::shared_ptr<OgreGraphics> OgreGraphicsSharedPointer;

    class OgreGraphics : public IGraphics, public Ogre::FrameListener, public Ogre::WindowEventListener
    {
    public:
        OgreGraphics(const std::wstring& windowName, const OutputSettings& outputSettings);
        virtual ~OgreGraphics();

        virtual bool vInit() override;
        virtual bool vPostInit() override;
        virtual bool vDestroy() override;

        virtual bool vUpdate(const unsigned long timeElapsed) override;

        virtual bool vPreRender() override;
        virtual bool vRender() override;
        virtual bool vPostRender() override;

        virtual void vSetBackgroundColor(const char r, const char g, const char b, const char a) override;

        virtual void vSetWorldTransform(const Matrix4& worldTransform) override;
        virtual void vSetViewTransform(const Matrix4& viewTransform) override;
        virtual void vSetProjectionTransform(const Matrix4& projectionTransform) override;

        virtual float vGetAspectRatio() const override
        {
            return Ogre::Real(m_pViewport->getActualWidth() /
                              Ogre::Real(m_pViewport->getActualHeight()));
        }

        virtual size_t vGetWindowHandle() const override
        {
            size_t windowHandle;
            m_pWindow->getCustomAttribute("WINDOW", &windowHandle);

            return windowHandle;
        }

        virtual OutputType vGetOutputType() const override
        {
            return OutputType::Graphical;
        }

    protected:
        // Ogre3D members.
        virtual bool frameStarted(const Ogre::FrameEvent& frameEvent) override;
        virtual bool frameEnded(const Ogre::FrameEvent& frameEvent) override;

        virtual bool frameRenderingQueued(const Ogre::FrameEvent& frameEvent) override;

        virtual void windowResized(Ogre::RenderWindow* pRenderWindow) override;
        virtual void windowClosed(Ogre::RenderWindow* pRenderWindow) override;

    public:
        // Internal use.
        Ogre::Root* GetOgreRoot();
        void AddViewport(Ogre::Camera* pOgreCamera);

    private:
        OutputSettings m_OutputSettings;
        std::wstring m_WindowName;

        // Ogre
        Ogre::Root* m_pRoot;

        Ogre::RenderWindow* m_pWindow;
        Ogre::Viewport* m_pViewport;
    };
}
