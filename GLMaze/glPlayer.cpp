#include "glPlayer.h"

Player::Player(Vec3 position, Vec3 lookat, Vec2 resolution, double fov, double near, double far)
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

Vec3 Player::Position()
{
    return _position;
}

Vec3 Player::ForwardDir(const Vec3 & normal)
{
    return _lookat - normal * (normal.dot(_lookat));
}

void Player::Look()
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

void Player::Move()
{
    _position += _velocity * (1.0 / 60);
}

void Player::SlowDown(double & v)
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

void Player::SlowDown()
{
    SlowDown(_velocity.x);
    SlowDown(_velocity.y);
    SlowDown(_velocity.z);
}

void Player::SpeedUp(Vec3 normal)
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
    deltaSpeed *= 0.1;
    _velocity += deltaSpeed;

    LimitSpeed();
    /*
    printf("%9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f\n", _velocity.x, _velocity.y, _velocity.z, _position.x, _position.y, _position.z,
    _lookat.x, _lookat.y, _lookat.z);
    */
}

void Player::LimitSpeed()
{
    auto len = _velocity.length();
    if (len > 2)
    {
        _velocity.normalize();
        _velocity *= 2;
    }
    if (NothingPressed() && len < 0.1)
    {
        _velocity = Vec3(0, 0, 0);
    }
}

bool Player::NothingPressed()
{
    return !_wPressed && !_dPressed && !_aPressed && !_sPressed;
}

void Player::CollisionReduce(const std::vector<Vec3>& walls)
{
    for (auto& wall : walls)
    {
        if (_velocity.dot(wall) < 0)
        {
            _velocity = _velocity.vertical_component(wall);
        }
    }
}

const Vec3 & Player::Speed() const { return _velocity; }

void Player::OnIdle(Vec3 ground, const std::vector<Vec3>& walls)
{
    SpeedUp(ground);
    //SlowDown();
    CollisionReduce(walls);
    if (_velocity.length() > 0.001)
    {
        Move();
        Look();
    }
    else if (_lookChanged)
    {
        Look();
        _lookChanged = false;
    }

}

void Player::MouseMove(int x, int y)
{
    double deltaX = -(x - _resolution.x / 2) / _resolution.x * PI * 4;
    double deltaY = -(y - _resolution.y / 2) / _resolution.y * PI;

    Mat3 xRotation(cos(deltaX), -sin(deltaX), 0,
                   sin(deltaX), cos(deltaX), 0,
                   0, 0, 1);
    _lookat = xRotation * Vec3(-1, -1, 0);

    _lookat.normalize();

    Vec3 rn = Vec3(0, 0, 1).cross(_lookat); //rotate axis

    Mat3 yRotation(rn.x*rn.x*(1 - cos(deltaY)) + cos(deltaY), rn.x*rn.y*(1 - cos(deltaY)) + rn.z*sin(deltaY), rn.x*rn.z*(1 - cos(deltaY)) - rn.y*sin(deltaY),
                   rn.x*rn.y*(1 - cos(deltaY)) - rn.z*sin(deltaY), rn.y*rn.y*(1 - cos(deltaY)) + cos(deltaY), rn.y*rn.z*(1 - cos(deltaY)) + rn.x*sin(deltaY),
                   rn.x*rn.z*(1 - cos(deltaY)) + rn.y*sin(deltaY), rn.y*rn.z*(1 - cos(deltaY)) - rn.x*sin(deltaY), rn.z*rn.z*(1 - cos(deltaY)) + cos(deltaY));

    _lookat = yRotation * _lookat;

    _lookat.normalize();

    _lookChanged = true;
}

void Player::WDown()
{
    _wPressed = true;
}

void Player::ADown()
{
    _aPressed = true;
}

void Player::SDown()
{
    _sPressed = true;
}

void Player::DDown()
{
    _dPressed = true;
}

void Player::WUp()
{
    _wPressed = false;
}

void Player::AUp()
{
    _aPressed = false;
}

void Player::SUp()
{
    _sPressed = false;
}

void Player::DUp()
{
    _dPressed = false;
}
