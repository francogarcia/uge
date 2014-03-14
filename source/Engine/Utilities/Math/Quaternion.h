#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace uge
{
    struct Matrix3;
    struct Matrix4;

    struct Quaternion : glm::quat
    {
    public:
        Quaternion();
        Quaternion(const float fW, const float fX, const float fY, const float fZ);
        Quaternion(const Vector3& angles);
        Quaternion(const Matrix3& rotationMatrix);
        Quaternion(const Quaternion& quaternion);
        ~Quaternion();

        // x, y, z
        void MakeQuaternion(const Vector3& pitchYawRoll);
        void MakeQuaternion(const Matrix3& rotation);
        void MakeQuaternion(const Matrix4& transform);

        Matrix3 ToMatrix3() const;
        Matrix4 ToMatrix4() const;

        Vector3 GetEulerAngles() const;
        Vector3 GetEulerAnglesDegrees() const;
        float GetYaw() const;
        float GetPitch() const;
        float GetRoll() const;

        float DotProduct(const Quaternion& quaternion) const;
        Quaternion CrossProduct(const Quaternion& quaternion) const;

        float Length() const;
        
        void Normalize();
        Quaternion GetNormalized() const;

        Quaternion& operator += (const Quaternion& right);
        Quaternion& operator -= (const Quaternion& right);
        Quaternion& operator *= (const float& fRight);
        Quaternion& operator /= (const float& fRight);
        Quaternion operator - ();

    //private:
        Quaternion(const glm::quat& glmQuaternion);
    };

    const Quaternion operator + (const Quaternion& left, const Quaternion& right);
    const Quaternion operator - (const Quaternion& left, const Quaternion& right);

    const Quaternion operator * (const Quaternion& left, const float fRight);
    const Quaternion operator * (const float fLeft, const Quaternion& right);

    const Quaternion operator / (const Quaternion& left, const float fRight);

    const bool operator == (const Quaternion& left, const Quaternion& right);
    const bool operator != (const Quaternion& left, const Quaternion& right);
}
