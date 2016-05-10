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

void prepareCube(double x, double y)
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
    
    glEnable(GL_LIGHT_MODEL_AMBIENT);

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat lightAmbient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSpecular[] = {0.5, 0.5, 0.5, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat lightPosition[] = {8, 8, 4, 1.0};   // w²»Îª0
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor3f(0.5, 0.5, 0.5);
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
