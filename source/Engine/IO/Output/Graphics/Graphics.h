/*
 * (c) Copyright 2012 Michael L. McShaffry and David Graham
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

/*
 *  This file's implementation is based on the text and source code of
 * the book Game Coding Complete, 4th edition, by Michael L. McShaffry (Mr. Mike)
 * and David Graham (Rez).
 *  The original source code of the book is licensed under the GNU Lesser General
 * Public License, version 3.0 <http://www.gnu.org/licenses/lgpl-3.0.txt>.
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
        virtual bool vPostInit() = 0;
        virtual bool vDestroy() = 0;

        virtual bool vUpdate(const unsigned long timeElapsed) = 0;

        virtual bool vPreRender() = 0;
        virtual bool vRender() = 0;
        virtual bool vPostRender() = 0;

        virtual void vSetBackgroundColor(const char r, const char g, const char b, const char a) = 0;

        virtual void vSetWorldTransform(const Matrix4& worldTransform) = 0;
        virtual void vSetViewTransform(const Matrix4& viewTransform) = 0;
        virtual void vSetProjectionTransform(const Matrix4& projectionTransform) = 0;

        virtual float vGetAspectRatio() const = 0;
        virtual size_t vGetWindowHandle() const = 0;

        virtual OutputType vGetOutputType() const = 0;
    };

}
