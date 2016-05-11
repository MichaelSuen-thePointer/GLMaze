#include "glFacetObject.h"

VertexArray::VertexArray()
    : _points()
    , _sequence()
{
}

VertexArray::~VertexArray()
{
    if (_ready == true)
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void VertexArray::AddTriangle(Point3(&& points)[3])
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
            _indexmap.insert({points[i], _points.size() / 3 - 1});
            sequence[i] = _points.size() / 3 - 1;
        }
        else
        {
            sequence[i] = place->second;
        }
    }

    _sequence.insert(_sequence.end(), sequence, sequence + 3);
}

void VertexArray::AddRectangle(Point3(&& points)[4])
{
    AddTriangle({points[0], points[1], points[2]});
    AddTriangle({points[0], points[2], points[3]});
}

void VertexArray::Ready()
{
    if (_ready = true)
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, &_points[0]);
}

void VertexArray::Draw()
{
    glDrawElements(GL_TRIANGLES, _sequence.size(), GL_UNSIGNED_INT, &_sequence[0]);
}

void VertexArray::AddObject(VertexArrayObject & vao)
{
    vao.AddToVertexArray(*this);
}

void VertexArrayCube::AddToVertexArray(VertexArray & array)
{
    array.AddRectangle({_points[6],_points[2],_points[3],_points[7]});
    array.AddRectangle({_points[5],_points[1],_points[0],_points[4]});
    array.AddRectangle({_points[7],_points[3],_points[1],_points[5]});
    array.AddRectangle({_points[4],_points[0],_points[2],_points[6]});
    array.AddRectangle({_points[2],_points[0],_points[1],_points[3]});
    array.AddRectangle({_points[7],_points[5],_points[4],_points[6]});
}

VertexArrayCube::VertexArrayCube(Point3(&& points)[8])
    : _points()
{
    std::copy(points, points + 8, _points);
}
