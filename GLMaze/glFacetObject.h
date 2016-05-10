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
};

class VertexArray
{
private:
    std::vector<double> _points;
    std::vector<unsigned int> _sequence;
    std::map<Point3, size_t> _indexmap;
public:
    VertexArray()
        : _points()
        , _sequence()
    {
    }

    void AddTriangle(Point3(&&points)[3])
    {
        decltype(_indexmap)::iterator place;

        size_t sequence[3];
        for (int i = 0; i < 3; i++)
        {
            if ((place = _indexmap.find(points[i])) == _indexmap.end())
            {
                _points.push_back(points[i].x);
                _points.push_back(points[i].y);
                _points.push_back(points[i].z);
                _indexmap.insert({ points[i], _points.size() / 3 - 1 });
                sequence[i] = _points.size() / 3 - 1;
            }
            else
            {
                sequence[i] = place->second;
            }
        }

        _sequence.insert(_sequence.end(), sequence, sequence + 3);
    }

    void AddRectangle(Point3(&&points)[4])
    {
        AddTriangle({ points[0], points[1], points[2] });
        AddTriangle({ points[0], points[2], points[3] });
    }

    void Ready()
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, &_points[0]);
    }

    void Draw()
    {
        glDrawElements(GL_TRIANGLES, _sequence.size(), GL_UNSIGNED_INT, &_sequence[0]);
    }

    void AddObject(VertexArrayObject& vao)
    {
        vao.AddToVertexArray(*this);
    }
};


class VertexArrayCube : public VertexArrayObject
{
private:
    virtual void AddToVertexArray(VertexArray& array) override
    {
        array.AddRectangle({ _points[6],_points[2],_points[3],_points[7] });
        array.AddRectangle({ _points[5],_points[1],_points[0],_points[4] });
        array.AddRectangle({ _points[7],_points[3],_points[1],_points[5] });
        array.AddRectangle({ _points[4],_points[0],_points[2],_points[6] });
        array.AddRectangle({ _points[2],_points[0],_points[1],_points[3] });
        array.AddRectangle({ _points[7],_points[5],_points[4],_points[6] });
    }

    Point3 _points[8];

public:
    VertexArrayCube(Point3(&&points)[8])
        : _points()
    {
        std::copy(points, points + 8, _points);
    }
};