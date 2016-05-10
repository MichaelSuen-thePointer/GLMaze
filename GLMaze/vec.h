#pragma once

#include <cmath>

class Vec3
{
public:
    double x, y, z;

    Vec3();
    Vec3(double x, double y, double z);
    void normalize();
    double length() const;
    double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    Vec3 vertical_component(const Vec3& other) const;
    Vec3 operator+(const Vec3& other) const;
    Vec3& operator+=(const Vec3& other);
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator-() const;
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(double scale);
    Vec3& operator/=(double scale);
    friend Vec3 operator*(double scale, const Vec3& rhs);
    friend Vec3 operator*(const Vec3& rhs, double scale);
    friend Vec3 operator/(const Vec3& rhs, double scale);
};

class Vec2
{
public:
    double x, y;

    Vec2();
    Vec2(double x, double y);
    void normalize();
    double length();
    double dot(const Vec2& other);
    Vec2 operator+(const Vec2& other);
    Vec2& operator+=(const Vec2& other);
    Vec2 operator-(const Vec2& other);
    Vec2 operator-();
    Vec2& operator-=(const Vec2& other);
    Vec2& operator*=(double scale);
    Vec2& operator/=(double scale);
    friend Vec2 operator*(double scale, const Vec2& rhs);
    friend Vec2 operator*(const Vec2& rhs, double scale);
    friend Vec2 operator/(const Vec2& rhs, double scale);
};