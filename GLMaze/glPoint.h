#pragma once

#include <type_traits>

struct Point3
{
    double x, y, z;
};

template<>
struct std::less<Point3>
{
    bool operator()(const Point3& a, const Point3& b) const
    {
        if (a.x < b.x)
        {
            return true;
        }
        if (a.x > b.x)
        {
            return false;
        }
        if (a.y < b.y)
        {
            return true;
        }
        if (a.y > b.y)
        {
            return false;
        }
        if (a.z < b.z)
        {
            return true;
        }
        if (a.z > b.z)
        {
            return false;
        }
        return false;
    }
};