#pragma once

#include <OGRE/Ogre.h>

#include <Core/PlayerProfile/GraphicalPreferences.h>

#include <IO/Output/Graphics/Graphics.h>

namespace uge
{
    class OgreGraphics;
    typedef std::shared_ptr<OgreGraphics> OgreGraphicsSharedPointer;

    class OgreGraphics : public IGraphics, public Ogre::FrameListener, public Ogre::WindowEventListener
    {
    public:
        OgreGraphics(const std::wstring& windowName, const GraphicalPreferences& graphicalPreferences);
        virtual ~OgreGraphics();

        virtual bool vInit() override;
        virtual bool vDestroy() override;

        virtual void vSetBackgroundColor(const char r, const char g, const char b, const char a) override;

        virtual bool vPreRender() override;
        virtual bool vPostRender() override;

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
        GraphicalPreferences m_GraphicalPreferences;
        std::wstring m_WindowName;

        // Ogre
        Ogre::Root* m_pRoot;

        Ogre::RenderWindow* m_pWindow;
        Ogre::Viewport* m_pViewport;
    };
}
