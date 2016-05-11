#pragma once

#include "glPoint.h"
#include "vec.h"
#include "mat.h"
#include <gl/glut.h>
#include <vector>

constexpr double PI = 3.14159265;

class Player
{
private:
    //inner states
    Vec3 _velocity;
    Vec3 _lookat;
    Vec3 _up;
    Vec3 _position;
    double _fov;
    Vec2 _resolution;
    double _near, _far;
    
    //outer states
    bool _wPressed, _aPressed, _sPressed, _dPressed;
    bool _lookChanged;
public:
    Player(Vec3 position, Vec3 lookat, Vec2 resolution, double fov, double near = 0.01, double far = 100);
    Vec3 Position();
    Vec3 ForwardDir(const Vec3& normal);
    void Look();
    void Move();
    static void SlowDown(double& v);
    void SlowDown();
    void SpeedUp(Vec3 normal);
    void LimitSpeed();
    bool NothingPressed();
    void CollisionReduce(const std::vector<Vec3>& walls);
    const Vec3& Speed() const;
    void OnIdle(Vec3 ground = Vec3(0, 0, 1), const std::vector<Vec3>& walls = std::vector<Vec3>());
    void MouseMove(int x, int y);
    void WDown();
    void ADown();
    void SDown();
    void DDown();
    void WUp();
    void AUp();
    void SUp();
    void DUp();
};