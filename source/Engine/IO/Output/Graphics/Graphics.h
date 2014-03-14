#pragma once

#include <IO/Output/IOutput.h>
#include <Utilities/Math/Matrix.h>

namespace uge
{

    enum class RenderPass : unsigned char
    {
        RenderPass0,
        Static = RenderPass0,
        Actor,
        Sky,
        NotRendered,

        RenderPassCount, // For loops.
        Root, // Root node is only used for the scene root node.
        Camera // Same as above.
    };

    class IGraphics;
    typedef std::shared_ptr<IGraphics> IGraphicsSharedPointer;
    typedef std::weak_ptr<IGraphics> IGraphicsWeakPointer;

    class IGraphics : public IOutput
    {
    public:
        IGraphics();
        virtual ~IGraphics();

        virtual bool vInit() = 0;
        virtual bool vDestroy() = 0;

        virtual void vSetBackgroundColor(const char r, const char g, const char b, const char a) = 0;

        virtual bool vPreRender() = 0;
        virtual bool vPostRender() = 0;

        virtual void vSetWorldTransform(const Matrix4& worldTransform) = 0;
        virtual void vSetViewTransform(const Matrix4& viewTransform) = 0;
        virtual void vSetProjectionTransform(const Matrix4& projectionTransform) = 0;

        virtual float vGetAspectRatio() const = 0;
        virtual size_t vGetWindowHandle() const = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

}
