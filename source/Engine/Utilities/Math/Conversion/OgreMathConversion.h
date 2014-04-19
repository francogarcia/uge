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

#include <Utilities/Math/MathStd.h>

namespace uge
{
    inline Ogre::Vector3 ToOgreMath(const Vector3& vector)
    {
        return Ogre::Vector3(vector.x, vector.y, vector.z);
    }

    inline Ogre::Vector4 ToOgreMath(const Vector4& vector)
    {
        return Ogre::Vector4(vector.x, vector.y, vector.z, vector.w);
    }

    inline Ogre::Matrix3 ToOgreMath(const Matrix3& matrix)
    {
        // XXX: could be done with a single for -> [column][line] = [line][column]
        return Ogre::Matrix3(matrix[0][0], matrix[1][0], matrix[2][0],
                             matrix[0][1], matrix[1][1], matrix[2][1],
                             matrix[0][2], matrix[1][2], matrix[2][2]);
    }

    inline Ogre::Matrix4 ToOgreMath(const Matrix4& matrix)
    {
        // XXX: could be done with a single for -> [column][line] = [line][column]
        return Ogre::Matrix4(matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
                             matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
                             matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
                             matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
    }

    inline Ogre::Quaternion ToOgreMath(const Quaternion& quaternion)
    {
        return Ogre::Quaternion(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    }

    inline Vector3 ToMath(const Ogre::Vector3& vector)
    {
        return Vector3(vector.x, vector.y, vector.z);
    }

    inline Vector4 ToMath(const Ogre::Vector4& vector)
    {
        return Vector4(vector.x, vector.y, vector.z, vector.w);
    }

    inline Quaternion ToMath(const Ogre::Quaternion& quaternion)
    {
        return Quaternion(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    }

    inline Matrix3 ToMath(const Ogre::Matrix3& matrix)
    {
        // XXX: could be done with a single for -> [column][line] = [line][column]
        return Matrix3(matrix[0][0], matrix[1][0], matrix[2][0],
                       matrix[0][1], matrix[1][1], matrix[2][1],
                       matrix[0][2], matrix[1][2], matrix[2][2]);
    }

    inline Matrix4 ToMath(const Ogre::Matrix4& matrix)
    {
        // XXX: could be done with a single for -> [column][line] = [line][column]
        return Matrix4(matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
                       matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
                       matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
                       matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
    }
}
