/*
 * (c) Copyright 2013 - 2014 Franco Eus�bio Garcia
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

#include "Window.h"

namespace uge
{

    namespace ui
    {
        //Window::Window()
        //{

        //}

        //Window::~Window()
        //{
        //    CleanUp();
        //}

        //bool Window::Init(const std::string& title,
        //                  const int width,
        //                  const int height,
        //                  const int red,
        //                  const int green,
        //                  const int blue,
        //                  const int alpha,
        //                  const int bitDepth,
        //                  const int stencilBits,
        //                  const bool bIsFullScreen,
        //                  const bool bIsResizable,
        //                  const int antiAliasingSamples)
        //{
        //    m_WindowParameters.title = title;
        //    m_WindowParameters.width = width;
        //    m_WindowParameters.height = height;
        //    m_WindowParameters.red = red;
        //    m_WindowParameters.green = green;
        //    m_WindowParameters.blue = blue;
        //    m_WindowParameters.alpha = alpha;
        //    m_WindowParameters.bitDepth = bitDepth;
        //    m_WindowParameters.stencilBits = stencilBits;
        //    m_WindowParameters.bIsFullScreen = bIsFullScreen;
        //    m_WindowParameters.bIsResizable = bIsResizable;
        //    m_WindowParameters.antiAliasingSamples = antiAliasingSamples;

        //    return (glfwInit() == GL_TRUE);
        //}

        //bool Window::Init(const WindowParameters& windowParameters)
        //{
        //    return Init(windowParameters.title,
        //                windowParameters.width,
        //                windowParameters.height,
        //                windowParameters.red,
        //                windowParameters.green,
        //                windowParameters.blue,
        //                windowParameters.alpha,
        //                windowParameters.bitDepth,
        //                windowParameters.stencilBits,
        //                windowParameters.bIsFullScreen,
        //                windowParameters.bIsResizable,
        //                windowParameters.antiAliasingSamples);
        //}

        //bool Window::Create()
        //{
        //    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,
        //                       (m_WindowParameters.bIsResizable) ? GL_FALSE : GL_TRUE);
        //    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, m_WindowParameters.antiAliasingSamples);

        //    int windowMode = (m_WindowParameters.bIsFullScreen) ? GLFW_FULLSCREEN : GLFW_WINDOW;
        //    if (glfwOpenWindow(m_WindowParameters.width,
        //                       m_WindowParameters.height,
        //                       m_WindowParameters.red,
        //                       m_WindowParameters.green,
        //                       m_WindowParameters.blue,
        //                       m_WindowParameters.alpha,
        //                       m_WindowParameters.bitDepth,
        //                       m_WindowParameters.stencilBits,
        //                       windowMode) == GL_TRUE)
        //    {
        //        if (glewInit() == GLEW_OK)
        //        {
        //            glfwSetWindowTitle(m_WindowParameters.title.c_str());

        //            return true;
        //        }
        //    }

        //    return false;
        //}

        //bool Window::Close()
        //{
        //    glfwCloseWindow();

        //    return true;
        //}

        //bool Window::CleanUp()
        //{
        //    glfwTerminate();

        //    return true;
        //}
    }

}
