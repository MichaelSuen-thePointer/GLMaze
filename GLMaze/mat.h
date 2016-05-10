#pragma once

#include <cassert>
#include <algorithm>

class Vec3;

class Mat3
{
private:
    double _mat[3][3];

    using MatLine = double(&)[3];
    using ConstMatLine = const double(&)[3];
public:
    ConstMatLine operator[](size_t idx) const;
    MatLine operator[](size_t idx);

    Mat3(double a00, double a01, double a02,
         double a10, double a11, double a12,
         double a20, double a21, double a22);

    Mat3(double* mat);

    friend Vec3 operator*(const Mat3& lhs, const Vec3& rhs);
};

