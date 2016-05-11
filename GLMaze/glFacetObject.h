#pragma once

#include <gl/glut.h>
#include <vector>
#include <map>
#include <tuple>
#include "glPoint.h"

class VertexArray;
class VertexArrayObject
{
public:
    virtual void AddToVertexArray(VertexArray&) = 0;
    virtual ~VertexArrayObject()
    {
    }
};

class VertexArray
{
private:
    std::vector<double> _points;
    std::vector<unsigned int> _sequence;
    std::map<Point3, size_t> _indexmap;

    bool _ready = false;
public:
    VertexArray();
    ~VertexArray();
    void AddTriangle(Point3(&&points)[3]);
    void AddRectangle(Point3(&&points)[4]);
    void Ready();
    void Draw();
    void AddObject(VertexArrayObject& vao);
};


class VertexArrayCube : public VertexArrayObject
{
private:
    Point3 _points[8];

    virtual void AddToVertexArray(VertexArray& array) override;
public:
    VertexArrayCube(Point3(&&points)[8]);
};