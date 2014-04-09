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

namespace uge
{

    struct Vector3;
    struct Vector4;

    typedef std::list<Vector3> Vector3List;
    typedef std::list<Vector4> Vector4List;

    struct Vector3 : public glm::vec3
    {
    public:
        static const Vector3 g_Zero;
        static const Vector3 g_Right;
        static const Vector3 g_Up;
        static const Vector3 g_Forward;

        Vector3();
        Vector3(const float fX, const float fY, const float fZ);
        Vector3(const Vector3& vector);
        Vector3(const Vector4& vector);
        ~Vector3();

        float Length() const;
        /// Faster.
        float LengthSquared() const;

        float Distance(const Vector3 vector) const;
        float DistanceSquared(const Vector3 vector) const;

        float DotProduct(const Vector3 vector) const;
        Vector3 CrossProduct(const Vector3 vector) const;

        void Normalize();
        Vector3 GetNormalized() const;

        // Linear interpolation.
        Vector3 LERP(Vector3& end, float fPercent);
        // TODO: http://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
        //Vector3 SLERP();
        //vector3 NLERP();

        Vector3& operator += (const Vector3& right);
        Vector3& operator -= (const Vector3& right);
        Vector3& operator *= (const float& fRight);
        Vector3& operator /= (const float& fRight);
        Vector3 operator - ();

    //private:
        Vector3(const glm::vec3& glmVector);
    };

    const Vector3 operator + (const Vector3& left, const Vector3& right);
    const Vector3 operator - (const Vector3& left, const Vector3& right);

    const Vector3 operator * (const Vector3& left, const float fRight);
    const Vector3 operator * (const float fLeft, const Vector3& right);

    const Vector3 operator / (const Vector3& left, const float fRight);

    const bool operator == (const Vector3& left, const Vector3& right);
    const bool operator != (const Vector3& left, const Vector3& right);

    struct Vector4 : public glm::vec4
    {
    public:
        static const Vector4 g_Zero;
        static const Vector4 g_Right;
        static const Vector4 g_Up;
        static const Vector4 g_Forward;

        Vector4();
        Vector4(const float fX, const float fY, const float fZ, const float fW);
        Vector4(const Vector3& vector);
        Vector4(const Vector4& vector);
        ~Vector4();

        float Length() const;
        /// Faster.
        float LengthSquared() const;

        float Distance(const Vector4 vector) const;
        float DistanceSquared(const Vector4 vector) const;

        float DotProduct(const Vector4 vector) const;

        void Normalize();
        Vector4 GetNormalized() const;

        // Linear interpolation.
        Vector4 LERP(Vector4& end, float fPercent);
        // TODO: http://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
        //Vector4 SLERP();
        //Vector4 NLERP();

        // X, Y, Z
        Vector3 ToVector3() const;

        Vector4& operator += (const Vector4& right);
        Vector4& operator -= (const Vector4& right);
        Vector4& operator *= (const float& fRight);
        Vector4& operator /= (const float& fRight);
        Vector4 operator - ();

    //private:
        Vector4(const glm::vec4& glmVector);
    };

    const Vector4 operator + (const Vector4& left, const Vector4& right);
    const Vector4 operator - (const Vector4& left, const Vector4& right);

    const Vector4 operator * (const Vector4& left, const float fRight);
    const Vector4 operator * (const float fLeft, const Vector4& right);

    const Vector4 operator / (const Vector4& left, const float fRight);

    const bool operator == (const Vector4& left, const Vector4& right);
    const bool operator != (const Vector4& left, const Vector4& right);

}
