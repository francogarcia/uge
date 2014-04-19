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

#include "MathUtil.h"

#include "Quaternion.h"
#include "Vector.h"

namespace uge
{
    struct Matrix3;
    struct Matrix4;
    class MatrixStack;

    struct Quaternion;

    struct Matrix3
    {
    public:
        // Proxy class.
        struct Row;
        struct ConstRow;

        static const Matrix3 g_Zero;
        static const Matrix3 g_Identity;

        glm::mat3 m_Values;

        Matrix3();
        Matrix3(const float fMatrix[9]);
        Matrix3(const float fMatrix[3][3]);
        Matrix3(const float fMatrix00, const float fMatrix01, const float fMatrix02,
                const float fMatrix10, const float fMatrix11, const float fMatrix12,
                const float fMatrix20, const float fMatrix21, const float fMatrix22);
        Matrix3(const Matrix3& matrix);
        ~Matrix3();

        void Multiply(Matrix3 matrix);

        Matrix3 GetTransposed() const;

        Matrix3 GetInversed() const;

        float Determinant() const;

        Matrix3::Row GetRow(const unsigned int row);
        const Matrix3::ConstRow GetRow(const unsigned int row) const;
        Vector3 GetRowVector(const unsigned int row) const;

        // Translation.
        void SetPositionFromVector(const Vector3& vector);
        Vector3 GetPositionVector() const;

        void SetRotationFromVector(const Vector3& rotationAxis, float fRotationAngle);
        Vector3 GetRotationVector() const;

        void SetScaleFromVector(const Vector3& vector);
        Vector3 GetScaleVector() const;

        // http://gamedev.stackexchange.com/questions/54103/glulookat-strange-behavior-implementing-camera
        Vector3 GetDirectionVector() const;
        Vector3 GetRightVector() const;
        Vector3 GetUpVector() const;

        Matrix3::Row operator [](const unsigned int row);
        const Matrix3::ConstRow operator [](const unsigned int row) const;

        Matrix3& operator = (const Matrix3& right);
        Matrix3& operator += (const Matrix3& right);
        Matrix3& operator -= (const Matrix3& right);
        Matrix3& operator *= (const Matrix3& right);
        Matrix3& operator *= (const float& right);
        Matrix3& operator /= (const float& right);
        Matrix3 operator - ();

        struct Row
        {
            friend struct Matrix3;

        public:
            float& operator[](const unsigned int column);
            const float& operator[](const unsigned int column) const;

        private:
            Row(Matrix3& matrix, const unsigned int row);

            Matrix3& m_Matrix;
            unsigned int m_Row;
        };

        struct ConstRow
        {
            friend struct Matrix3;

        public:
            const float& operator[](const unsigned int column) const;

        private:
            ConstRow(const Matrix3& matrix, const unsigned int row);

            const Matrix3& m_Matrix;
            unsigned int m_Row;
        };

        //private:
        // Internal use.
        Matrix3(const glm::mat3& glmMatrix);
    };

    const Matrix3 operator + (const Matrix3& left, const Matrix3& right);
    const Matrix3 operator - (const Matrix3& left, const Matrix3& right);

    const Matrix3 operator * (const Matrix3& left, const Matrix3& right);
    const Matrix3 operator * (const Matrix3& left, const float fRight);
    const Matrix3 operator * (const float fLeft, const Matrix3& right);

    const Matrix3 operator / (const Matrix3& left, const float fRight);

    const bool operator == (const Matrix3& left, const Matrix3& right);
    const bool operator != (const Matrix3& left, const Matrix3& right);

    const Vector3 operator * (const Vector3& left, const Matrix3& right);
    const Vector3 operator * (const Matrix3& left, const Vector3& right);

    struct Matrix4
    {
    public:
        // Proxy class.
        struct Row;
        struct ConstRow;

        static const Matrix4 g_Zero;
        static const Matrix4 g_Identity;

        glm::mat4 m_Values;

        Matrix4();
        Matrix4(const float fMatrix[16]);
        Matrix4(const float fMatrix[4][4]);
        Matrix4(const float fMatrix00, const float fMatrix01, const float fMatrix02, const float fMatrix03,
                const float fMatrix10, const float fMatrix11, const float fMatrix12, const float fMatrix13,
                const float fMatrix20, const float fMatrix21, const float fMatrix22, const float fMatrix23,
                const float fMatrix30, const float fMatrix31, const float fMatrix32, const float fMatrix33);
        Matrix4(const float fYaw, const float fPitch, const float fRoll);
        Matrix4(const Matrix4& matrix);
        ~Matrix4();

        void Multiply(Matrix4 matrix);

        Matrix4 GetTransposed() const;

        Matrix4 GetInversed() const;

        float Determinant() const;

        Matrix4::Row GetRow(const unsigned int row);
        const Matrix4::ConstRow GetRow(const unsigned int row) const;
        Vector4 GetRowVector(const unsigned int row) const;

        void MakeTransform(const Vector3& position, const Vector3& scale, const Quaternion& rotation);
        // Rotation vector: yaw, pitch, roll order.
        void MakeTransform(const Vector3& position, const Vector3& scale, const Vector3& rotation);
        void DecomposeTransform(Vector3& position, Vector3& scale, Quaternion& rotation) const;

        void Transform(const Matrix4& translationMatrix, const Matrix4& scaleMatrix, const Matrix4& rotationMatrix);

        void Translate(const Vector3& offset);

        // Angle in radians.
        void Rotate(const Vector3& rotationAxis, float fRotationAngleRadians);
        void Rotate(const Quaternion& rotationQuaternion);

        void Scale(const Vector3& scale);

        // Translation.
        void MakeTranslationMatrix(const Vector3& position);
        void SetPositionFromVector(const Vector3& vector);
        void SetPositionFromVector(const Vector4& vector);
        Vector3 GetPositionVector() const;

        // Angle in radians.
        void MakeRotationMatrix(const Vector3& rotationAxis, float fRotationAngleRadians);
        void MakeRotationMatrix(const Quaternion& rotation);
        void MakeRotationMatrix(const float fYawRadians, const float fPitchRadians, const float fRollRadians);
        Vector3 GetRotationVector() const;
        Matrix3 GetRotationMatrix() const;
        Quaternion GetRotationQuaternion() const;

        void MakeScaleMatrix(const Vector3& scale);
        void SetScaleFromVector(const Vector3& vector);
        Vector3 GetScaleVector() const;

        // 3 x 3 matrix with the translation and rotation of the matrix.
        Matrix3 ExtractPositionRotation() const;

        // http://gamedev.stackexchange.com/questions/54103/glulookat-strange-behavior-implementing-camera
        Vector3 GetDirectionVector() const;
        Vector3 GetRightVector() const;
        Vector3 GetUpVector() const;

        Vector3 XForm(const Vector3& vector) const;
        Vector3 XForm(const Vector4& vector) const;

        Matrix4::Row operator [](const unsigned int row);
        const Matrix4::ConstRow operator [](const unsigned int row) const;

        Matrix4& operator = (const Matrix4& right);
        Matrix4& operator += (const Matrix4& right);
        Matrix4& operator -= (const Matrix4& right);
        Matrix4& operator *= (const Matrix4& right);
        Matrix4& operator *= (const float& right);
        Matrix4& operator /= (const float& right);
        Matrix4 operator - ();

        struct Row
        {
            friend struct Matrix4;

        public:
            float& operator[](const unsigned int column);
            const float& operator[](const unsigned int column) const;

        private:
            Row(Matrix4& matrix, const unsigned int row);

            Matrix4& m_Matrix;
            unsigned int m_Row;
        };

        struct ConstRow
        {
            friend struct Matrix4;

        public:
            const float& operator[](const unsigned int column) const;

        private:
            ConstRow(const Matrix4& matrix, const unsigned int row);

            const Matrix4& m_Matrix;
            unsigned int m_Row;
        };

        //private:
        // Internal use.
        Matrix4(const glm::mat4& glmMatrix);
    };

    const Matrix4 operator + (const Matrix4& left, const Matrix4& right);
    const Matrix4 operator - (const Matrix4& left, const Matrix4& right);

    const Matrix4 operator * (const Matrix4& left, const Matrix4& right);
    const Matrix4 operator * (const Matrix4& left, const float fRight);
    const Matrix4 operator * (const float fLeft, const Matrix4& right);

    const Matrix4 operator / (const Matrix4& left, const float fRight);

    const bool operator == (const Matrix4& left, const Matrix4& right);
    const bool operator != (const Matrix4& left, const Matrix4& right);

    const Vector4 operator * (const Vector4& left, const Matrix4& right);
    const Vector4 operator * (const Matrix4& left, const Vector4& right);

    class MatrixStack
    {
    public:
        MatrixStack();
        MatrixStack(Matrix4 topMatrix);
        ~MatrixStack();

        // Duplicate top.
        void Push();
        void Pop();

        void ApplyLocal(const Matrix4& matrix);

        const Matrix4& Top() const;

    private:
        std::stack<Matrix4, std::vector<Matrix4>> m_MatrixStack;
        Matrix4 m_TopMatrix;
    };

}
