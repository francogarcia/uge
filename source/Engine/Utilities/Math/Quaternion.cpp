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

#include "GameEngineStd.h"

#include "Quaternion.h"

#include "MathUtil.h"

namespace uge
{
    Quaternion::Quaternion()
        : glm::quat()
    {

    }

    Quaternion::Quaternion(const float fW, const float fX, const float fY, const float fZ)
        : glm::quat(fW, fX, fY, fZ)
    {

    }

    Quaternion::Quaternion(const Vector3& angles)
        : glm::quat(static_cast<const glm::vec3&>(angles))
    {

    }

    Quaternion::Quaternion(const Matrix3& rotationMatrix)
        : glm::quat(rotationMatrix.m_Values)
    {

    }

    Quaternion::Quaternion(const Quaternion& quaternion)
        : glm::quat(static_cast<const glm::quat&>(quaternion))
    {

    }

    Quaternion::Quaternion(const glm::quat& glmQuaternion)
        : glm::quat(glmQuaternion)
    {

    }

    Quaternion::~Quaternion()
    {

    }

    void Quaternion::MakeQuaternion(const Vector3& pitchYawRoll)
    {
        glm::quat quaternion(static_cast<const glm::vec3&>(pitchYawRoll));
        this->x = quaternion.x;
        this->y = quaternion.y;
        this->z = quaternion.z;
        this->w = quaternion.w;
    }

    void Quaternion::MakeQuaternion(const Matrix3& rotation)
    {
        glm::quat quaternion = glm::quat_cast(rotation.m_Values);
        this->x = quaternion.x;
        this->y = quaternion.y;
        this->z = quaternion.z;
        this->w = quaternion.w;
    }

    void Quaternion::MakeQuaternion(const Matrix4& transform)
    {
        // XXX: GLM results seems wrong. Check Matrix4 for a correct implementation if needed.

        glm::quat quaternion = glm::quat_cast(transform.m_Values);
        this->x = quaternion.x;
        this->y = quaternion.y;
        this->z = quaternion.z;
        this->w = quaternion.w;
    }

    Matrix3 Quaternion::ToMatrix3() const
    {
        return Matrix3(glm::mat3_cast(static_cast<const glm::quat&>(*this)));
    }

    Matrix4 Quaternion::ToMatrix4() const
    {
        return Matrix4(glm::mat4_cast(static_cast<const glm::quat&>(*this)));
    }

    Vector3 Quaternion::GetEulerAngles() const
    {
        Vector3 degrees = GetEulerAnglesDegrees();

        return degrees * uge::PI / 180.0f;
    }

    Vector3 Quaternion::GetEulerAnglesDegrees() const
    {
        return Vector3(glm::eulerAngles(static_cast<const glm::quat&>(*this)));
    }

    float Quaternion::GetYaw() const
    {
        glm::vec3 angles = glm::eulerAngles(static_cast<const glm::quat&>(*this));

        return angles.y;
    }

    float Quaternion::GetPitch() const
    {
        glm::vec3 angles = glm::eulerAngles(static_cast<const glm::quat&>(*this));

        return angles.x;
    }

    float Quaternion::GetRoll() const
    {
        glm::vec3 angles = glm::eulerAngles(static_cast<const glm::quat&>(*this));

        return angles.z;
    }

    float Quaternion::DotProduct(const Quaternion& quaternion) const
    {
        return glm::dot(static_cast<const glm::quat&>(*this),
                        static_cast<const glm::quat&>(quaternion));
    }

    Quaternion Quaternion::CrossProduct(const Quaternion& quaternion) const
    {
        return Quaternion(glm::cross(static_cast<const glm::quat&>(*this),
                                     static_cast<const glm::quat&>(quaternion)));
    }

    float Quaternion::Length() const
    {
        return glm::length(static_cast<const glm::quat&>(*this));
    }

    void Quaternion::Normalize()
    {
        Quaternion normalizedQuaternion = GetNormalized();
        this->x = normalizedQuaternion.x;
        this->y = normalizedQuaternion.y;
        this->z = normalizedQuaternion.z;
        this->w = normalizedQuaternion.w;
    }

    Quaternion Quaternion::GetNormalized() const
    {
        return glm::normalize(static_cast<const glm::quat&>(*this));
    }

    Quaternion& Quaternion::operator += (const Quaternion& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;

        return *this;
    }

    Quaternion& Quaternion::operator -= (const Quaternion& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;

        return *this;
    }

    Quaternion& Quaternion::operator *= (const float& fRight)
    {
        x *= fRight;
        y *= fRight;
        z *= fRight;
        w *= fRight;

        return *this;
    }

    Quaternion& Quaternion::operator /= (const float& fRight)
    {
        const float fInvRight = 1.0f / fRight;

        x *= fInvRight;
        y *= fInvRight;
        z *= fInvRight;
        w *= fInvRight;

        return *this;
    }

    Quaternion Quaternion::operator - ()
    {
        return Quaternion(-x, -y, -z, -w);
    }

    const Quaternion operator + (const Quaternion& left, const Quaternion& right)
    {
        return Quaternion(left.x + right.x,
                          left.y + right.y,
                          left.z + right.z,
                          left.w + right.w);
    }

    const Quaternion operator - (const Quaternion& left, const Quaternion& right)
    {
        return Quaternion(left.x - right.x,
                          left.y - right.y,
                          left.z - right.z,
                          left.w - right.w);
    }

    const Quaternion operator * (const Quaternion& left, const float fRight)
    {
        return Quaternion(left.x * fRight,
                          left.y * fRight,
                          left.z * fRight,
                          left.w * fRight);
    }

    const Quaternion operator * (const float fLeft, const Quaternion& right)
    {
        return right * fLeft;
    }

    const Quaternion operator / (const Quaternion& left, const float fRight)
    {
        const float fInvRight = 1.0f / fRight;

        return Quaternion(left.x * fInvRight,
                          left.y * fInvRight,
                          left.z * fInvRight,
                          left.w * fInvRight);
    }

    const bool operator == (const Quaternion& left, const Quaternion& right)
    {
        return ((FAbs(left.x - right.x) < EPSILON)
                && (FAbs(left.y - right.y) < EPSILON)
                && (FAbs(left.z - right.z) < EPSILON))
               && (FAbs(left.w - right.w) < EPSILON);
    }

    const bool operator != (const Quaternion& left, const Quaternion& right)
    {
        return !(left == right);
    }
}
