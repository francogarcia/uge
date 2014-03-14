#pragma once

#include <Utilities/Math/MathStd.h>

namespace uge
{
    inline YSE::Vec ToYSEMath(const Vector3& vector)
    {
        return YSE::Vec(vector.x, vector.y, vector.z);
    }

    inline Vector3 ToMath(const YSE::Vec& vector)
    {
        return Vector3(vector.x, vector.y, vector.z);
    }
}
