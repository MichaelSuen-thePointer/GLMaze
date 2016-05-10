#pragma once

#include "glPoint.h"
#include "vec.h"
#include "mat.h"
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

    bool _lookChanged;
public:
    Player(Vec3 position, Vec3 lookat, Vec2 resolution, double fov, double near = 0.01, double far = 100)
        : _velocity(0, 0, 0)
        , _lookat(lookat)
        , _up(0, 0, 1)
        , _position(position)
        , _fov(fov)
        , _resolution(resolution)
        , _near(near)
        , _far(far)
        , _wPressed(false), _aPressed(false), _sPressed(false), _dPressed(false)
    {
        _lookat.normalize();
    }

    Vec3 Position()
    {
        return _position;
    }

    Vec3 ForwardDir(const Vec3& normal)
    {
        return _lookat - normal * (normal.dot(_lookat));
    }

    void Look()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(_fov, _resolution.x / _resolution.y, _near, _far);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        Vec3 lookPoint = _position + _lookat;
        gluLookAt(_position.x, _position.y, _position.z,
                  lookPoint.x, lookPoint.y, lookPoint.z,
                  _up.x, _up.y, _up.z);
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
        fwd.normalize();
        Vec3 lft = normal.cross(fwd);
        Vec3 deltaSpeed = -_velocity;
        deltaSpeed.normalize();
        deltaSpeed /= 2;
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
        deltaSpeed.normalize();
        deltaSpeed *= 0.01;
        _velocity += deltaSpeed;

        LimitSpeed();

        printf("%9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f\n", _velocity.x, _velocity.y, _velocity.z, _position.x, _position.y, _position.z,
               _lookat.x, _lookat.y, _lookat.z);
    }

    void LimitSpeed()
    {
        auto len = _velocity.length();
        if (len > 1)
        {
            _velocity /= len;
        }
        if (NothingPressed() && len < 0.1)
        {
            _velocity = Vec3(0, 0, 0);
        }
    }

    bool NothingPressed()
    {
        return !_wPressed && !_dPressed && !_aPressed && !_sPressed;
    }

    void CollisionReduce(const std::vector<Vec3>& walls)
    {
        for (auto& wall : walls)
        {
            if (_velocity.dot(wall) < 0)
            {
                _velocity = _velocity.vertical_component(wall);
            }
        }
    }

    void OnIdle(Vec3 ground = Vec3(0, 0, 1), const std::vector<Vec3>& walls = std::vector<Vec3>())
    {
        SpeedUp(ground);
        //SlowDown();
        CollisionReduce(walls);
        if (_velocity.length() > 0.001)
        {
            Move();
            Look();
            glutPostRedisplay();
        }
        else if (_lookChanged)
        {
            Look();
            _lookChanged = false;
            glutPostRedisplay();
        }
        
    }

    void MouseMove(int x, int y)
    {
        double deltaX = -(x - _resolution.x/2) / _resolution.x * PI * 4;
        double deltaY = -(y - _resolution.y/2) / _resolution.y * PI;

        Mat3 xRotation(cos(deltaX), -sin(deltaX), 0,
                       sin(deltaX), cos(deltaX), 0,
                       0, 0, 1);
        _lookat = xRotation * Vec3(-1,-1,0);

        _lookat.normalize();

        Vec3 rn = Vec3(0, 0, 1).cross(_lookat); //rotate axis

        Mat3 yRotation(rn.x*rn.x*(1 - cos(deltaY)) + cos(deltaY), rn.x*rn.y*(1 - cos(deltaY)) + rn.z*sin(deltaY), rn.x*rn.z*(1 - cos(deltaY)) - rn.y*sin(deltaY),
                       rn.x*rn.y*(1 - cos(deltaY)) - rn.z*sin(deltaY), rn.y*rn.y*(1 - cos(deltaY)) + cos(deltaY), rn.y*rn.z*(1 - cos(deltaY)) + rn.x*sin(deltaY),
                       rn.x*rn.z*(1 - cos(deltaY)) + rn.y*sin(deltaY), rn.y*rn.z*(1 - cos(deltaY)) - rn.x*sin(deltaY), rn.z*rn.z*(1 - cos(deltaY)) + cos(deltaY));

        _lookat = yRotation * _lookat;

        _lookat.normalize();

        _lookChanged = true;
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