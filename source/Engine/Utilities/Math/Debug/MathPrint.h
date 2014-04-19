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
 *//

#include "GameEngineStd.h"

#include <Utilities/Math/MathStd.h>

namespace uge
{
    namespace test
    {

        void PrintMatrix(const uge::Matrix4& mat)
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    std::cout << mat[i][j] << " ";
                }

                std::cout << std::endl;
            }
        }

        void PrintVector(const uge::Vector3& vec)
        {
            std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
        }

        void PrintQuaternion(const uge::Quaternion& quat)
        {
            std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
        }

        // OGRE

        void PrintMatrix(const Ogre::Matrix4& mat)
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    std::cout << mat[i][j] << " ";
                }

                std::cout << std::endl;
            }
        }

        void PrintVector(const Ogre::Vector3& vec)
        {
            std::cout << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
        }

        void PrintQuaternion(const Ogre::Quaternion& quat)
        {
            std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
        }

    }
}
