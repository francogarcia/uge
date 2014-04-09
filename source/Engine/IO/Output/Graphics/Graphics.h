/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
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
  */

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
