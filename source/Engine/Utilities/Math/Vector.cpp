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

#include "GameEngineSTD.h"

#include "Vector.h"
#include "MathUtil.h"

namespace uge
{

    const Vector3 Vector3::g_Zero(0.0f, 0.0f, 0.0f);
    const Vector3 Vector3::g_Right(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::g_Up(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::g_Forward(0.0f, 0.0f, 1.0f);

    const Vector4 Vector4::g_Zero(0.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::g_Up(Vector3::g_Up.x, Vector3::g_Up.y, Vector3::g_Up.z, 0.0f);
    const Vector4 Vector4::g_Right(Vector3::g_Right.x, Vector3::g_Right.y, Vector3::g_Right.z, 0.0f);
    const Vector4 Vector4::g_Forward(Vector3::g_Forward.x, Vector3::g_Forward.y, Vector3::g_Forward.z, 0.0f);

    // Vector 3

    Vector3::Vector3() : glm::vec3(0.0f, 0.0f, 0.0f)
    {

    }

    Vector3::Vector3(const float fX, const float fY, const float fZ)
        : glm::vec3(fX, fY, fZ)
    {

    }

    Vector3::Vector3(const Vector3& vector)
        : glm::vec3(vector.x, vector.y, vector.z)
    {

    }

    Vector3::Vector3(const Vector4& vector)
        : glm::vec3(vector.x, vector.y, vector.z)
    {

    }

    Vector3::Vector3(const glm::vec3& glmVector)
        : glm::vec3(glmVector.x, glmVector.y, glmVector.z)
    {

    }

    Vector3::~Vector3()
    {

    }

    float Vector3::Length() const
    {
        return glm::length(static_cast<const glm::vec3&>(*this));
    }

    float Vector3::LengthSquared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    float Vector3::Distance(const Vector3 vector) const
    {
        return SquareRoot(DistanceSquared(vector));
    }

    float Vector3::DistanceSquared(const Vector3 vector) const
    {
        const float fXDelta = x - vector.x;
        const float fYDelta = y - vector.y;
        const float fZDelta = z - vector.z;

        return (fXDelta * fXDelta) + (fYDelta * fYDelta) + (fZDelta * fZDelta);
    }

    float Vector3::DotProduct(const Vector3 vector) const
    {
        return glm::dot(static_cast<const glm::vec3&>(*this), static_cast<const glm::vec3&>(vector));
    }

    Vector3 Vector3::CrossProduct(const Vector3 vector) const
    {
        return Vector3(glm::cross(static_cast<const glm::vec3&>(*this), static_cast<const glm::vec3&>(vector)));
    }

    void Vector3::Normalize()
    {
        glm::vec3 normalizedVector = glm::normalize(static_cast<const glm::vec3&>(*this));
        this->x = normalizedVector.x;
        this->y = normalizedVector.y;
        this->z = normalizedVector.z;
    }

    Vector3 Vector3::GetNormalized() const
    {
        return Vector3(glm::normalize(static_cast<const glm::vec3&>(*this)));
    }

    Vector3 Vector3::LERP(Vector3& end, float fPercent)
    {
        return Vector3(*this - fPercent * (end - *this));
    }

    Vector3& Vector3::operator += (const Vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;

        return *this;
    }

    Vector3& Vector3::operator -= (const Vector3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;

        return *this;
    }

    Vector3& Vector3::operator *= (const float& right)
    {
        x *= right;
        y *= right;
        z *= right;

        return *this;
    }

    Vector3& Vector3::operator /= (const float& right)
    {
        float fDiv = 1.0f / right;
        x *= fDiv;
        y *= fDiv;
        z *= fDiv;

        return *this;
    }

    Vector3 Vector3::operator - ()
    {
        return Vector3(-x, -y, -z);
    }

    const Vector3 operator + (const Vector3& left, const Vector3& right)
    {
        return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
    }

    const Vector3 operator - (const Vector3& left, const Vector3& right)
    {
        return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
    }

    const Vector3 operator * (const Vector3& left, const float fRight)
    {
        return Vector3(left.x * fRight, left.y * fRight, left.z * fRight);
    }

    const Vector3 operator * (const float fLeft, const Vector3& right)
    {
        return right * fLeft;
    }

    const Vector3 operator / (const Vector3& left, const float fRight)
    {
        float fDiv = 1.0f / fRight;
        return Vector3(left.x * fDiv, left.y * fDiv, left.z * fDiv);
    }

    const bool operator == (const Vector3& left, const Vector3& right)
    {
        return ((FAbs(left.x - right.x) < EPSILON)
                && (FAbs(left.y - right.y) < EPSILON)
                && (FAbs(left.z - right.z) < EPSILON));
    }

    const bool operator != (const Vector3& left, const Vector3& right)
    {
        return !(left == right);
    }

    // Vector 4

    Vector4::Vector4() : glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)
    {

    }

    Vector4::Vector4(const float fX, const float fY, const float fZ, const float fW)
        : glm::vec4(fX, fY, fZ, fW)
    {

    }

    Vector4::Vector4(const Vector3& vector)
        : glm::vec4(vector.x, vector.y, vector.z, 1.0f)
    {

    }

    Vector4::Vector4(const Vector4& vector)
        : glm::vec4(vector.x, vector.y, vector.z, vector.w)
    {

    }

    Vector4::Vector4(const glm::vec4& glmVector)
        : glm::vec4(glmVector.x, glmVector.y, glmVector.z, glmVector.w)
    {

    }

    Vector4::~Vector4()
    {

    }

    float Vector4::Length() const
    {
        return glm::length(static_cast<const glm::vec4&>(*this));
    }

    float Vector4::LengthSquared() const
    {
        return (x * x) + (y * y) + (z * z) + (w * w);
    }

    float Vector4::Distance(const Vector4 vector) const
    {
        return SquareRoot(DistanceSquared(vector));
    }

    float Vector4::DistanceSquared(const Vector4 vector) const
    {
        const float fXDelta = x - vector.x;
        const float fYDelta = y - vector.y;
        const float fZDelta = z - vector.z;
        const float fWDelta = w - vector.w;

        return (fXDelta * fXDelta) + (fYDelta * fYDelta) + (fZDelta * fZDelta) + (fWDelta * fWDelta);
    }

    float Vector4::DotProduct(const Vector4 vector) const
    {
        return glm::dot(static_cast<const glm::vec4&>(*this), static_cast<const glm::vec4&>(vector));
    }

    Vector3 Vector4::ToVector3() const
    {
        return Vector3(x, y, z);
    }

    void Vector4::Normalize()
    {
        glm::vec4 normalizedVector = glm::normalize(static_cast<const glm::vec4&>(*this));
        this->x = normalizedVector.x;
        this->y = normalizedVector.y;
        this->z = normalizedVector.z;
        this->w = normalizedVector.w;
    }

    Vector4 Vector4::GetNormalized() const
    {
        return Vector4(glm::normalize(static_cast<const glm::vec4&>(*this)));
    }

    Vector4 Vector4::LERP(Vector4& end, float fPercent)
    {
        return Vector4(*this - fPercent * (end - *this));
    }

    Vector4& Vector4::operator += (const Vector4& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;

        return *this;
    }

    Vector4& Vector4::operator -= (const Vector4& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;

        return *this;
    }

    Vector4& Vector4::operator *= (const float& right)
    {
        x *= right;
        y *= right;
        z *= right;
        w *= right;

        return *this;
    }

    Vector4& Vector4::operator /= (const float& right)
    {
        float fDiv = 1.0f / right;
        x *= fDiv;
        y *= fDiv;
        z *= fDiv;
        w *= fDiv;

        return *this;
    }

    Vector4 Vector4::operator - ()
    {
        return Vector4(-x, -y, -z, -w);
    }

    const Vector4 operator + (const Vector4& left, const Vector4& right)
    {
        return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
    }

    const Vector4 operator - (const Vector4& left, const Vector4& right)
    {
        return Vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
    }

    const Vector4 operator * (const Vector4& left, const float fRight)
    {
        return Vector4(left.x * fRight, left.y * fRight, left.z * fRight, left.w * left.w);
    }

    const Vector4 operator * (const float fLeft, const Vector4& right)
    {
        return right * fLeft;
    }

    const Vector4 operator / (const Vector4& left, const float fRight)
    {
        float fDiv = 1.0f / fRight;
        return Vector4(left.x * fDiv, left.y * fDiv, left.z * fDiv, left.z * fDiv);
    }

    const bool operator == (const Vector4& left, const Vector4& right)
    {
        return ((FAbs(left.x - right.x) < EPSILON)
                && (FAbs(left.y - right.y) < EPSILON)
                && (FAbs(left.z - right.z) < EPSILON)
                && (FAbs(left.w - right.w) < EPSILON));
    }

    const bool operator != (const Vector4& left, const Vector4& right)
    {
        return !(left == right);
    }
}
