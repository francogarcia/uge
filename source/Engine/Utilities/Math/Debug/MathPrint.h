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
