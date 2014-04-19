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

#include "GameEngineStd.h"

#include "Matrix.h"

#include "MathUtil.h"

namespace uge
{
    const Matrix3 Matrix3::g_Zero(glm::mat3(0.0f));
    const Matrix3 Matrix3::g_Identity(glm::mat3(1.0f));

    const Matrix4 Matrix4::g_Zero(glm::mat4(0.0f));
    const Matrix4 Matrix4::g_Identity(glm::mat4(1.0f));

    // Matrix 3

    Matrix3::Row::Row(Matrix3& matrix, unsigned int row)
        : m_Matrix(matrix), m_Row(row)
    {

    }

    float& Matrix3::Row::operator[](unsigned int column)
    {
        assert(column < 3 && "Invalid column index!");

        return m_Matrix.m_Values[m_Row][column];
    }

    const float& Matrix3::Row::operator[](unsigned int column) const
    {
        assert(column < 3 && "Invalid column index!");

        return m_Matrix.m_Values[m_Row][column];
    }

    Matrix3::ConstRow::ConstRow(const Matrix3& matrix, unsigned int row)
        : m_Matrix(matrix), m_Row(row)
    {

    }

    const float& Matrix3::ConstRow::operator[](unsigned int column) const
    {
        assert(column < 3 && "Invalid column index!");

        return m_Matrix.m_Values[m_Row][column];
    }

    Matrix3::Matrix3() : m_Values(0.0f)
    {

    }

    Matrix3::Matrix3(const float fMatrix[9])
    {
        m_Values = glm::make_mat3(fMatrix);
    }

    Matrix3::Matrix3(const float fMatrix[3][3])
    {
        const float* pMatrix = &fMatrix[0][0];
        m_Values = glm::make_mat3(pMatrix);
    }

    Matrix3::Matrix3(const float fMatrix00, const float fMatrix01, const float fMatrix02,
                     const float fMatrix10, const float fMatrix11, const float fMatrix12,
                     const float fMatrix20, const float fMatrix21, const float fMatrix22)
    {
        m_Values[0][0] = fMatrix00;
        m_Values[0][1] = fMatrix01;
        m_Values[0][2] = fMatrix02;

        m_Values[1][0] = fMatrix10;
        m_Values[1][1] = fMatrix11;
        m_Values[1][2] = fMatrix12;

        m_Values[2][0] = fMatrix20;
        m_Values[2][1] = fMatrix21;
        m_Values[2][2] = fMatrix22;
    }

    Matrix3::Matrix3(const Matrix3& matrix)
        : m_Values(matrix.m_Values)
    {

    }

    Matrix3::Matrix3(const glm::mat3& glmMatrix)
        : m_Values(glmMatrix)
    {

    }

    Matrix3::~Matrix3()
    {

    }

    void Matrix3::Multiply(Matrix3 matrix)
    {
        m_Values = m_Values * matrix.m_Values;
    }

    Matrix3 Matrix3::GetTransposed() const
    {
        return Matrix3(glm::transpose(m_Values));
    }

    Matrix3 Matrix3::GetInversed() const
    {
        return Matrix3(glm::inverse(m_Values));
    }

    float Matrix3::Determinant() const
    {
        return glm::determinant(m_Values);
    }

    Matrix3::Row Matrix3::GetRow(const unsigned int row)
    {
        assert(row < 3 && "Invalid row index!");

        return Row(*this, row);
    }

    const Matrix3::ConstRow Matrix3::GetRow(const unsigned int row) const
    {
        assert(row < 3 && "Invalid row index!");

        return ConstRow(*this, row);
    }

    Vector3 Matrix3::GetRowVector(const unsigned int row) const
    {
        assert(row < 3 && "Invalid row index!");

        return Vector3(m_Values[row]);
    }

    void Matrix3::SetPositionFromVector(const Vector3& vector)
    {
        m_Values[3][0] = vector[0];
        m_Values[3][1] = vector[1];
        m_Values[3][2] = vector[2];
        m_Values[3][3] = 1.0f;
    }

    Vector3 Matrix3::GetPositionVector() const
    {
        return Vector3(m_Values[3][0], m_Values[3][1], m_Values[3][2]);
    }

    void Matrix3::SetRotationFromVector(const Vector3& rotationAxis, float fRotationAngle)
    {
        // TODO: implement this.
        assert(0 && "To be implemented");
    }

    Vector3 Matrix3::GetRotationVector() const
    {
        Quaternion rotationQuaternion;
        rotationQuaternion.MakeQuaternion(*this);

        return rotationQuaternion.GetEulerAngles();
    }

    void Matrix3::SetScaleFromVector(const Vector3& vector)
    {
        m_Values[0][0] = vector.x;
        m_Values[1][1] = vector.y;
        m_Values[2][2] = vector.z;
    }

    Vector3 Matrix3::GetScaleVector() const
    {
        return Vector3(m_Values[0][0], m_Values[1][1], m_Values[2][2]);
    }

    Vector3 Matrix3::GetDirectionVector() const
    {
        // XXX: Or 2. Change Right() if wrong.
        return Vector3(m_Values[0][0], m_Values[0][1], m_Values[0][2]);
    }

    Vector3 Matrix3::GetRightVector() const
    {
        // XXX: Or 2. Change Direction() if wrong.
        return Vector3(m_Values[2][0], m_Values[2][1], m_Values[2][2]);
    }

    Vector3 Matrix3::GetUpVector() const
    {
        return Vector3(m_Values[1][0], m_Values[1][1], m_Values[1][2]);
    }

    Matrix3::Row Matrix3::operator [](unsigned int row)
    {
        return GetRow(row);
    }

    const Matrix3::ConstRow Matrix3::operator [](unsigned int row) const
    {
        return GetRow(row);
    }

    Matrix3& Matrix3::operator = (const Matrix3& right)
    {
        m_Values = right.m_Values;

        return *this;
    }

    Matrix3& Matrix3::operator += (const Matrix3& right)
    {
        m_Values += right.m_Values;

        return *this;
    }

    Matrix3& Matrix3::operator -= (const Matrix3& right)
    {
        m_Values -= right.m_Values;

        return *this;
    }

    Matrix3& Matrix3::operator *= (const Matrix3& right)
    {
        m_Values *= right.m_Values;

        return *this;
    }

    Matrix3& Matrix3::operator *= (const float& right)
    {
        m_Values *= right;

        return *this;
    }

    Matrix3& Matrix3::operator /= (const float& right)
    {
        float fInvertedValue = 1.0 / right;
        m_Values *= fInvertedValue;

        return *this;
    }

    Matrix3 Matrix3::operator - ()
    {
        m_Values *= -1;

        return *this;
    }

    const Matrix3 operator + (const Matrix3& left, const Matrix3& right)
    {
        Matrix3 result(left);
        result += right;

        return result;
    }

    const Matrix3 operator - (const Matrix3& left, const Matrix3& right)
    {
        Matrix3 result(left);
        result -= right;

        return result;
    }

    const Matrix3 operator * (const Matrix3& left, const Matrix3& right)
    {
        Matrix3 result(left);
        result.Multiply(right);

        return result;
    }

    const Matrix3 operator * (const Matrix3& left, const float fRight)
    {
        Matrix3 result(left);
        result *= fRight;

        return result;
    }

    const Matrix3 operator * (const float fLeft, const Matrix3& right)
    {
        Matrix3 result(right);
        result *= fLeft;

        return result;
    }

    const Matrix3 operator / (const Matrix3& left, const float fRight)
    {
        Matrix3 result(left);
        result *= fRight;

        return result;
    }

    const bool operator == (const Matrix3& left, const Matrix3& right)
    {
        return (left.m_Values == right.m_Values);
    }

    const bool operator != (const Matrix3& left, const Matrix3& right)
    {
        return (left.m_Values != right.m_Values);
    }

    const Vector3 operator * (const Vector3& left, const Matrix3& right)
    {
        assert(0 && "GLM uses row vectors!");
        return right.GetTransposed() * left;
    }

    const Vector3 operator * (const Matrix3& left, const Vector3& right)
    {
        return Vector3(left.m_Values * static_cast<const glm::vec3&>(right));
    }

    // Matrix 4

    Matrix4::Row::Row(Matrix4& matrix, unsigned int row)
        : m_Matrix(matrix), m_Row(row)
    {

    }

    float& Matrix4::Row::operator[](unsigned int column)
    {
        assert(column < 4 && "Invalid column index!");

        return m_Matrix.m_Values[m_Row][column];
    }

    const float& Matrix4::Row::operator[](unsigned int column) const
    {
        assert(column < 4 && "Invalid column index!");

        return m_Matrix.m_Values[m_Row][column];
    }

    Matrix4::ConstRow::ConstRow(const Matrix4& matrix, unsigned int row)
        : m_Matrix(matrix), m_Row(row)
    {

    }

    const float& Matrix4::ConstRow::operator[](unsigned int column) const
    {
        assert(column < 4 && "Invalid column index!");

        return m_Matrix.m_Values[m_Row][column];
    }

    Matrix4::Matrix4() : m_Values(0.0f)
    {

    }

    Matrix4::Matrix4(const float fMatrix[16])
    {
        m_Values = glm::make_mat4(fMatrix);
    }

    Matrix4::Matrix4(const float fMatrix[4][4])
    {
        const float* pMatrix = &fMatrix[0][0];
        m_Values = glm::make_mat4(pMatrix);
    }

    Matrix4::Matrix4(const float fMatrix00, const float fMatrix01, const float fMatrix02, const float fMatrix03,
                     const float fMatrix10, const float fMatrix11, const float fMatrix12, const float fMatrix13,
                     const float fMatrix20, const float fMatrix21, const float fMatrix22, const float fMatrix23,
                     const float fMatrix30, const float fMatrix31, const float fMatrix32, const float fMatrix33)
    {
        m_Values[0][0] = fMatrix00;
        m_Values[0][1] = fMatrix01;
        m_Values[0][2] = fMatrix02;
        m_Values[0][3] = fMatrix03;

        m_Values[1][0] = fMatrix10;
        m_Values[1][1] = fMatrix11;
        m_Values[1][2] = fMatrix12;
        m_Values[1][3] = fMatrix13;

        m_Values[2][0] = fMatrix20;
        m_Values[2][1] = fMatrix21;
        m_Values[2][2] = fMatrix22;
        m_Values[2][3] = fMatrix23;

        m_Values[3][0] = fMatrix30;
        m_Values[3][1] = fMatrix31;
        m_Values[3][2] = fMatrix32;
        m_Values[3][3] = fMatrix33;
    }

    Matrix4::Matrix4(const float fYaw, const float fPitch, const float fRoll)
    {
        MakeRotationMatrix(fYaw, fPitch, fRoll);
    }

    Matrix4::Matrix4(const Matrix4& matrix)
        : m_Values(matrix.m_Values)
    {

    }

    Matrix4::Matrix4(const glm::mat4& glmMatrix)
        : m_Values(glmMatrix)
    {

    }

    Matrix4::~Matrix4()
    {

    }

    void Matrix4::Multiply(Matrix4 matrix)
    {
        m_Values *= matrix.m_Values;
    }

    Matrix4 Matrix4::GetTransposed() const
    {
        return Matrix4(glm::transpose(m_Values));
    }

    Matrix4 Matrix4::GetInversed() const
    {
        return Matrix4(glm::inverse(m_Values));
    }

    float Matrix4::Determinant() const
    {
        return glm::determinant(m_Values);
    }

    Matrix4::Row Matrix4::GetRow(const unsigned int row)
    {
        assert(row < 4 && "Invalid row index!");

        return Row(*this, row);
    }

    const Matrix4::ConstRow Matrix4::GetRow(const unsigned int row) const
    {
        assert(row < 4 && "Invalid row index!");

        return ConstRow(*this, row);
    }

    Vector4 Matrix4::GetRowVector(const unsigned int row) const
    {
        assert(row < 4 && "Invalid row index!");

        return Vector4(m_Values[row]);
    }

    void Matrix4::MakeTransform(const Vector3& position, const Vector3& scale, const Quaternion& rotation)
    {
        Matrix4 translationMatrix;
        translationMatrix.MakeTranslationMatrix(position);

        Matrix4 rotationMatrix = rotation.ToMatrix4();

        Matrix4 scaleMatrix;
        scaleMatrix.MakeScaleMatrix(scale);

        m_Values = translationMatrix.m_Values * rotationMatrix.m_Values * scaleMatrix.m_Values;
    }

    void Matrix4::MakeTransform(const Vector3& position, const Vector3& scale, const Vector3& rotation)
    {
       Quaternion rotationQuaternion;
       rotationQuaternion.MakeQuaternion(rotation);

       MakeTransform(position, scale, rotationQuaternion);
    }

    void Matrix4::DecomposeTransform(Vector3& position, Vector3& scale, Quaternion& rotation) const
    {
        position = GetPositionVector();
        scale = GetScaleVector();
        rotation = GetRotationQuaternion();
    }

    void Matrix4::Transform(const Matrix4& translationMatrix, const Matrix4& scaleMatrix, const Matrix4& rotationMatrix)
    {
        m_Values = translationMatrix.m_Values * rotationMatrix.m_Values * scaleMatrix.m_Values;
    }

    void Matrix4::Translate(const Vector3& offset)
    {
        m_Values = glm::translate(m_Values, static_cast<const glm::vec3&>(offset));
    }

    void Matrix4::Rotate(const Vector3& rotationAxis, float fRotationAngleRadians)
    {
        m_Values = glm::rotate(m_Values, fRotationAngleRadians, static_cast<const glm::vec3&>(rotationAxis));
    }

    void Matrix4::Rotate(const Quaternion& rotationQuaternion)
    {
        Matrix4 rotationMatrix = rotationQuaternion.ToMatrix4();
        m_Values *= rotationMatrix.m_Values;
    }

    void Matrix4::Scale(const Vector3& scale)
    {
        m_Values = glm::scale(m_Values, static_cast<const glm::vec3&>(scale));
    }

    void Matrix4::MakeTranslationMatrix(const Vector3& position)
    {
        m_Values = glm::translate(static_cast<const glm::vec3&>(position));
    }

    void Matrix4::SetPositionFromVector(const Vector3& vector)
    {
        m_Values[3][0] = vector.x;
        m_Values[3][1] = vector.y;
        m_Values[3][2] = vector.z;
        m_Values[3][3] = 1.0f;
    }

    void Matrix4::SetPositionFromVector(const Vector4& vector)
    {
        m_Values[3][0] = vector.x;
        m_Values[3][1] = vector.y;
        m_Values[3][2] = vector.z;
        m_Values[3][3] = vector.w;
    }

    Vector3 Matrix4::GetPositionVector() const
    {
        return Vector3(m_Values[3][0], m_Values[3][1], m_Values[3][2]);
    }

    void Matrix4::MakeRotationMatrix(const Vector3& rotationAxis, float fRotationAngleRadians)
    {
        m_Values = glm::rotate(fRotationAngleRadians, static_cast<const glm::vec3&>(rotationAxis));
    }

    void Matrix4::MakeRotationMatrix(const float fYawRadians, const float fPitchRadians, const float fRollRadians)
    {
        m_Values = glm::yawPitchRoll(fYawRadians, fPitchRadians, fRollRadians);
    }

    void Matrix4::MakeRotationMatrix(const Quaternion& rotation)
    {
        *this = rotation.ToMatrix4();
    }

    Vector3 Matrix4::GetRotationVector() const
    {
        Quaternion rotationQuaternion = GetRotationQuaternion();

        return rotationQuaternion.GetEulerAngles();
    }

    Matrix3 Matrix4::GetRotationMatrix() const
    {
        Vector3 row1(GetRowVector(0));
        Vector3 row2(GetRowVector(1));
        Vector3 row3(GetRowVector(2));

        Vector3 scale(row1.Length(), row2.Length(), row3.Length());
        if (scale.x != 0)
        {
            row1 /= scale.x;
        }

        if (scale.y != 0)
        {
            row2 /= scale.y;
        }

        if (scale.x != 0)
        {
            row3 /= scale.z;
        }

        return Matrix3(row1.x, row1.y, row1.z,
                       row2.x, row2.y, row2.z,
                       row3.x, row3.y, row3.z);
    }

    Quaternion Matrix4::GetRotationQuaternion() const
    {
        Matrix3 rotationMatrix = GetRotationMatrix();

        return Quaternion(glm::quat_cast(rotationMatrix.m_Values));
    }

    void Matrix4::MakeScaleMatrix(const Vector3& scale)
    {
        m_Values = glm::scale(static_cast<const glm::vec3&>(scale));
    }

    void Matrix4::SetScaleFromVector(const Vector3& vector)
    {
        m_Values[0][0] = vector.x;
        m_Values[1][1] = vector.y;
        m_Values[2][2] = vector.z;
        m_Values[3][3] = 1.0f;
    }

    Vector3 Matrix4::GetScaleVector() const
    {
        Vector3 row1(GetRowVector(0));
        Vector3 row2(GetRowVector(1));
        Vector3 row3(GetRowVector(2));

        Vector3 scale(row1.Length(), row2.Length(), row3.Length());
        if (Determinant() < 0)
        {
            scale.x = -scale.x;
            scale.y = -scale.y;
            scale.z = -scale.z;
        }

        return scale;
    }

    Matrix3 Matrix4::ExtractPositionRotation() const
    {
        // TODO: implement this.
        assert(0 && "To be implemented");
        return Matrix3();
    }

    Vector3 Matrix4::GetDirectionVector() const
    {
        // XXX: Or 0. Change Right() if wrong.
        return Vector3(m_Values[2][0], m_Values[2][1], m_Values[2][2]);
    }

    Vector3 Matrix4::GetRightVector() const
    {
        // XXX: Or 2. Change Direction() if wrong.
        return Vector3(m_Values[0][0], m_Values[0][1], m_Values[0][2]);
    }

    Vector3 Matrix4::GetUpVector() const
    {
        return Vector3(m_Values[1][0], m_Values[1][1], m_Values[1][2]);
    }

    Vector3 Matrix4::XForm(const Vector3& vector) const
    {
        Vector4 vector4(vector);

        return XForm(vector4);
    }

    Vector3 Matrix4::XForm(const Vector4& vector) const
    {
        Vector4 result(*this * vector);

        return Vector3(result.x, result.y, result.z);
    }


    Matrix4::Row Matrix4::operator [](unsigned int row)
    {
        return GetRow(row);
    }

    const Matrix4::ConstRow Matrix4::operator [](unsigned int row) const
    {
        return GetRow(row);
    }

    Matrix4& Matrix4::operator = (const Matrix4& right)
    {
        m_Values = right.m_Values;

        return *this;
    }

    Matrix4& Matrix4::operator += (const Matrix4& right)
    {
        m_Values += right.m_Values;

        return *this;
    }

    Matrix4& Matrix4::operator -= (const Matrix4& right)
    {
        m_Values -= right.m_Values;

        return *this;
    }

    Matrix4& Matrix4::operator *= (const Matrix4& right)
    {
        m_Values *= right.m_Values;

        return *this;
    }

    Matrix4& Matrix4::operator *= (const float& right)
    {
        m_Values *= right;

        return *this;
    }

    Matrix4& Matrix4::operator /= (const float& right)
    {
        float fInvertedValue = 1.0 / right;
        m_Values *= fInvertedValue;

        return *this;
    }

    Matrix4 Matrix4::operator - ()
    {
        m_Values *= -1;

        return *this;
    }

    const Matrix4 operator + (const Matrix4& left, const Matrix4& right)
    {
        Matrix4 result(left);
        result += right;

        return result;
    }

    const Matrix4 operator - (const Matrix4& left, const Matrix4& right)
    {
        Matrix4 result(left);
        result -= right;

        return result;
    }

    const Matrix4 operator * (const Matrix4& left, const Matrix4& right)
    {
        Matrix4 result(left);
        result.Multiply(right);

        return result;
    }

    const Matrix4 operator * (const Matrix4& left, const float fRight)
    {
        Matrix4 result(left);
        result *= fRight;

        return result;
    }

    const Matrix4 operator * (const float fLeft, const Matrix4& right)
    {
        Matrix4 result(right);
        result *= fLeft;

        return result;
    }

    const Matrix4 operator / (const Matrix4& left, const float fRight)
    {
        Matrix4 result(left);
        result *= fRight;

        return result;
    }

    const bool operator == (const Matrix4& left, const Matrix4& right)
    {
        return (left.m_Values == right.m_Values);
    }

    const bool operator != (const Matrix4& left, const Matrix4& right)
    {
        return (left.m_Values != right.m_Values);
    }

    const Vector4 operator * (const Vector4& left, const Matrix4& right)
    {
        assert(0 && "GLM uses row vectors!");
        return right.GetTransposed() * left;
    }

    const Vector4 operator * (const Matrix4& left, const Vector4& right)
    {
        return Vector4(left.m_Values * static_cast<const glm::vec4&>(right));
    }

    // MatrixStack

    MatrixStack::MatrixStack()
        : m_TopMatrix(Matrix4::g_Identity)
    {
        m_MatrixStack.push(m_TopMatrix);
    }

    MatrixStack::MatrixStack(Matrix4 topMatrix)
        : m_TopMatrix(topMatrix)
    {

    }

    MatrixStack::~MatrixStack()
    {

    }

    void MatrixStack::Push()
    {
        m_MatrixStack.push(m_TopMatrix);
    }

    void MatrixStack::Pop()
    {
        assert(!m_MatrixStack.empty() && "The stack is empty!");

        m_TopMatrix = m_MatrixStack.top();
        m_MatrixStack.pop();
    }

    void MatrixStack::ApplyLocal(const Matrix4& matrix)
    {
        m_TopMatrix *= matrix;
    }

    const Matrix4& MatrixStack::Top() const
    {
        return m_TopMatrix;
    }

}
