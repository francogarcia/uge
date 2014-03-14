#pragma once

#include <Utilities/Math/MathStd.h>

namespace uge
{
    inline btVector3 ToBulletMath(const Vector3& vector)
    {
        return btVector3(vector.x, vector.y, vector.z);
    }

    inline btVector4 ToBulletMath(const Vector4& vector)
    {
        return btVector4(vector.x, vector.y, vector.z, vector.w);
    }

    inline btMatrix3x3 ToBulletMath(const Matrix3& matrix)
    {
        btMatrix3x3 bulletMatrix;
        bulletMatrix.setFromOpenGLSubMatrix((const btScalar*)&matrix.m_Values);

        return bulletMatrix;
    }

    inline btTransform ToBulletMath(const Matrix4& matrix)
    {
        btTransform bulletMatrix;
        bulletMatrix.setFromOpenGLMatrix((const btScalar*)&matrix.m_Values);        

        return bulletMatrix;
    }

    inline btQuaternion ToBulletMath(const Quaternion& quaternion)
    {
        return btQuaternion(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
    }

    inline Vector3 ToMath(const btVector3& vector)
    {
        return Vector3(vector.x(), vector.y(), vector.z());
    }

    inline Vector4 ToMath(const btVector4& vector)
    {
        return Vector4(vector.x(), vector.y(), vector.z(), vector.w());
    }

    inline Quaternion ToMath(const btQuaternion& quaternion)
    {
        return Quaternion(quaternion.w(), quaternion.x(), quaternion.y(), quaternion.z());
    }

    inline Matrix3 ToMath(const btMatrix3x3& bulletMatrix)
    {
        Matrix3 matrix;
        bulletMatrix.getOpenGLSubMatrix((btScalar*) &matrix.m_Values);       

        return matrix;
    }

    inline Matrix4 ToMath(const btTransform& bulletMatrix)
    {
        Matrix4 matrix;
        bulletMatrix.getOpenGLMatrix((btScalar*) &matrix.m_Values); 

        return matrix;
    }
}