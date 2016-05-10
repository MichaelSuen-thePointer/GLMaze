#include "mat.h"
#include "vec.h"

Mat3::ConstMatLine Mat3::operator[](size_t idx) const
{
    assert(idx >= 0 && idx < 3);

    return _mat[idx];
}

Mat3::MatLine Mat3::operator[](size_t idx)
{
    assert(idx >= 0 && idx < 3);

    return _mat[idx];
}

Mat3::Mat3(double a00, double a01, double a02,
     double a10, double a11, double a12,
     double a20, double a21, double a22)
    : _mat{ a00, a01, a02, a10, a11, a12, a20, a21, a22 }
{
}
Mat3::Mat3(double* mat)
    : _mat()
{
    for (int i = 0; i < 9; i += 3)
    {
        std::copy(mat + i, mat + i + 3, _mat[i]);
    }
}

Vec3 operator*(const Mat3 & lhs, const Vec3 & rhs)
{
    return Vec3(lhs[0][0] * rhs.x + lhs[0][1] * rhs.y + lhs[0][2] * rhs.z,
                lhs[1][0] * rhs.x + lhs[1][1] * rhs.y + lhs[1][2] * rhs.z,
                lhs[2][0] * rhs.x + lhs[2][1] * rhs.y + lhs[2][2] * rhs.z);
}
