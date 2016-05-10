#include "vec.h"

Vec3 operator*(double scale, const Vec3 & rhs)
{
    return Vec3(scale * rhs.x, scale * rhs.y, scale * rhs.z);
}

Vec3 operator*(const Vec3 & rhs, double scale)
{
    return scale * rhs;
}

Vec3 operator/(const Vec3 & rhs, double scale)
{
    return Vec3(rhs.x / scale, rhs.y / scale, rhs.z / scale);
}

Vec2 operator*(double scale, const Vec2 & rhs)
{
    return Vec2();
}

Vec2 operator*(const Vec2 & rhs, double scale)
{
    return Vec2();
}

Vec2 operator/(const Vec2 & rhs, double scale)
{
    return Vec2();
}

Vec3::Vec3()
    : Vec3(0, 0, 0)
{
}

Vec3::Vec3(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

void Vec3::normalize()
{
    double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    if (length > 0.00001)
    {
        x /= length;
        y /= length;
        z /= length;
    }
}

double Vec3::length() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double Vec3::dot(const Vec3 & other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3 & other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vec3 Vec3::vertical_component(const Vec3 & other) const
{
    Vec3 copy = other;
    copy.normalize();
    return *this - (copy * this->dot(copy));
}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3& Vec3::operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator-() const
{
    return Vec3(-x, -y, -z);
}

Vec3& Vec3::operator-=(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3& Vec3::operator*=(double scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Vec3& Vec3::operator/=(double scale)
{
    x /= scale;
    y /= scale;
    z /= scale;
    return *this;
}

Vec2::Vec2()
    : Vec2(0, 0)
{
}

Vec2::Vec2(double x, double y)
    : x(x), y(y)
{
}

void Vec2::normalize()
{
    double len = sqrt(pow(x, 2) + pow(y, 2));
    x /= len;
    y /= len;
}

double Vec2::length()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

double Vec2::dot(const Vec2 & other)
{
    return x * other.x + y*other.y;
}

Vec2 Vec2::operator+(const Vec2 & other)
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 & Vec2::operator+=(const Vec2 & other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vec2 Vec2::operator-(const Vec2 & other)
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator-()
{
    return Vec2(-x, -y);
}

Vec2 & Vec2::operator-=(const Vec2 & other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2 & Vec2::operator*=(double scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Vec2 & Vec2::operator/=(double scale)
{
    x /= scale;
    y /= scale;
    return *this;
}
