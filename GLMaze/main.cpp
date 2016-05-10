#include <gl/glut.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "glFacetObject.h"

#define WINDOW_HEIGHT   1000
#define WINDOW_WIDTH    1000

using std::vector;

vector<vector<char>> maze_data{
    { 'H','H','H','H','H','H','H','H','H','H','H','H','H','H','H','H' },
    { 'H',' ',' ',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ','H' },
    { 'H',' ','H',' ','H','H','H',' ','H',' ','H',' ',' ',' ',' ','H' },
    { 'H',' ','H','H',' ',' ','H',' ','H','H',' ','H',' ','H',' ','H' },
    { 'H',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ','H',' ','H' },
    { 'H',' ','H','H','H','H','H','H','H','H',' ','H','H','H',' ','H' },
    { 'H',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H',' ',' ','H' },
    { 'H',' ','H','H','H','H','H',' ','H','H','H',' ','H','H','H','H' },
    { 'H',' ','H',' ',' ',' ','H',' ',' ',' ','H',' ',' ',' ',' ','H' },
    { 'H',' ',' ',' ','H','H','H','H','H','H','H',' ',' ',' ',' ','H' },
    { 'H',' ','H',' ',' ',' ','H',' ',' ',' ','H',' ',' ','H',' ','H' },
    { 'H',' ','H','H','H','H','H',' ','H','H','H','H',' ','H',' ','H' },
    { 'H',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ','H',' ','H' },
    { 'H',' ',' ','H','H',' ','H','H','H','H',' ','H','H','H',' ','H' },
    { 'H',' ',' ',' ','H',' ','H',' ',' ',' ',' ','H',' ',' ',' ','H' },
    { 'H','H','H','H','H','H','H','H','H','H','H','H','H',' ','H','H' },
};  /* reference from internet */

VertexArray maze;

void prepareCube(int x, int y)
{
    VertexArrayCube cube({
        { x,y,0 },{ x, y + 1, 0 },{ x + 1, y, 0 },{ x + 1, y + 1, 0 },
        { x,y,1 },{ x, y + 1, 1 },{ x + 1, y, 1 },{ x + 1, y + 1, 1 }
    });

    maze.AddObject(cube);
}

void prepareWalls()
{

    std::size_t mazeHeight = maze_data.size();
    std::size_t mazeWidth = maze_data[0].size();

    for (size_t i = 0; i != mazeHeight; ++i)
    {
        for (size_t j = 0; j != mazeWidth; ++j)
        {
            if (maze_data[i][j] == 'H')
            {
                prepareCube(i, j);
            }
        }
    }
    maze.Ready();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0, 1, 1);
    
    maze.Draw();

    glutSwapBuffers();
}

void init()
{
    prepareWalls();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpengGL Demo");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, 1.0f, 1.0f, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20, 20, 20, 5, 5, 0, 0, 0, 1);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
