#pragma once

#include "glPoint.h"
#include "vec.h"
#include <gl/glut.h>

constexpr double PI = 3.14159265;

class Player
{
private:
    Vec3 _velocity;
    Vec3 _lookat;
    Vec3 _up;
    Vec3 _position;
    double _fov;
    Vec2 _resolution;
    double _near, _far;

    bool _wPressed, _aPressed, _sPressed, _dPressed;
    Vec2 _mousePos;
public:
    Player(Vec2 resolution, double fov, double near = 1, double far = 100)
        : _velocity(0, 0, 0)
        , _lookat(1, 1, 0)
        , _up(0, 0, 1)
        , _position(0, 0, 0)
        , _fov(fov)
        , _resolution(resolution)
        , _near(near)
        , _far(far)
        , _wPressed(false), _aPressed(false), _sPressed(false), _dPressed(false)
        , _mousePos(resolution / 2)
    {
    }

    Vec3 Position()
    {
        return _position;
    }

    Vec3 ForwardDir(Vec3 normal)
    {
        return _lookat - normal * (normal.dot(_lookat));
    }

    void Look()
    {
        gluLookAt(_position.x, _position.y, _position.z,
                  _lookat.x, _lookat.y, _lookat.z,
                  _up.x, _up.y, _up.z);
        gluPerspective(_fov, _resolution.x / _resolution.y, _near, _far);
    }

    void Move()
    {
        _position += _velocity * 0.01;
    }

    static void SlowDown(double& v)
    {
        if (v >= 0.02)
        {
            v -= 0.02;
        }
        else
        {
            v = 0;
        }
    }

    void SlowDown()
    {
        SlowDown(_velocity.x);
        SlowDown(_velocity.y);
        SlowDown(_velocity.z);
    }

    void SpeedUp(Vec3 normal)
    {
        Vec3 fwd = ForwardDir(normal);
        Vec3 lft = normal.cross(fwd);
        Vec3 deltaSpeed;
        if (_wPressed)
        {
            deltaSpeed += fwd;
        }
        if (_sPressed)
        {
            deltaSpeed -= fwd;
        }
        if (_aPressed)
        {
            deltaSpeed += lft;
        }
        if (_dPressed)
        {
            deltaSpeed -= lft;
        }
        deltaSpeed.normalize;
        deltaSpeed *= 0.01;
        _velocity += Vec3(deltaSpeed.x, deltaSpeed.y, 0);
        Limit(_velocity.x);
        Limit(_velocity.y);
        Limit(_velocity.z);
    }

    static void Limit(double& v)
    {
        if (v > 1)
        {
            v = 1;
        }
    }

    void OnIdle(Vec3 normal = Vec3(0, 0, 1))
    {
        SpeedUp(normal);
        SlowDown();
        Move();
        Look();
    }

    void MouseMove(int x, int y)
    {
        double deltaX = (x - _mousePos.x) / _resolution.x * PI;
        double deltaY = (y - _mousePos.y) / _resolution.y * PI;
        
        // TODO : 
    }

    void WDown()
    {
        _wPressed = true;
    }
    void ADown()
    {
        _aPressed = true;
    }
    void SDown()
    {
        _sPressed = true;
    }
    void DDown()
    {
        _dPressed = true;
    }
    void WUp()
    {
        _wPressed = false;
    }
    void AUp()
    {
        _aPressed = false;
    }
    void SUp()
    {
        _sPressed = false;
    }
    void DUp()
    {
        _dPressed = false;
    }
};