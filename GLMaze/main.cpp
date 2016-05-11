#include <gl/glut.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "glFacetObject.h"
#include "glPlayer.h"

using std::vector;

vector<vector<char>> maze_data{
    { 'H',' ','H','H','H','H','H','H','H','H','H','H','H','H','H','H' },
    { 'H',' ','H',' ',' ',' ',' ',' ','H',' ',' ',' ',' ',' ',' ','H' },
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
Player player{ {16.5,16.5,0.5 }, {1,1,0}, { 900,900 }, 75 };

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

void keydown(unsigned char ch, int x, int y)
{
    if (ch == 'w')
    {
        player.WDown();
    }
    else if (ch == 's')
    {
        player.SDown();
    }
    else if (ch == 'a')
    {
        player.ADown();
    }
    else if (ch == 'd')
    {
        player.DDown();
    }
}

void keyup(unsigned char ch, int x, int y)
{
    if (ch == 'w')
    {
        player.WUp();
    }
    else if (ch == 's')
    {
        player.SUp();
    }
    else if (ch == 'a')
    {
        player.AUp();
    }
    else if (ch == 'd')
    {
        player.DUp();
    }
}

bool hasWall(int x, int y)
{
    assert(maze_data.size() < (size_t)INT_MAX);
    if (x >= 0 && x < (int)maze_data.size() && y >= 0 && y < (int)maze_data.size())
    {
        return maze_data[x][y] == 'H';
    }
    return false;
}

void check_conor(int x, int y, int offx, int offy, vector<Vec3>& walls)
{
    Vec3 wallVec;
    if (hasWall(x + offx, y))
    {
        wallVec += Vec3(-offx, offy, 0);
    }
    if (hasWall(x + offx, y + offy))
    {
        wallVec += Vec3(-offx, -offy, 0);
    }
    if (hasWall(x, y + offy))
    {
        wallVec += Vec3(offx, -offy, 0);
    }
    walls.emplace_back(wallVec.x, 0, 0);
    walls.emplace_back(0, wallVec.y, 0);
}

std::vector<Vec3> getWalls()
{
    vector<Vec3> walls;
    auto pos = player.Position();

    int x = pos.x >= 0 ? pos.x : pos.x - 1;
    int y = pos.y >= 0 ? pos.y : pos.y - 1;

    double toN =  pos.x - x;
    double toS =  x + 1 - pos.x;
    double toE =  y + 1 - pos.y;
    double toW =  pos.y - y;

    if (toN < 0.1)
    {
        if (toE < 0.1)
        {
            check_conor(x, y, -1, 1, walls);
        }
        if (toW < 0.1)
        {
            check_conor(x, y, -1, -1, walls);
        }
        if (hasWall(x - 1, y))
        {
            walls.emplace_back(1, 0, 0);
        }
    }

    if (toS < 0.1)
    {
        if (toE < 0.1)
        {
            check_conor(x, y, 1, 1, walls);
        }
        if (toW < 0.1)
        {
            check_conor(x, y, 1, -1, walls);
        }
        if (hasWall(x + 1, y))
        {
            walls.emplace_back(-1, 0, 0);
        }
    }

    if (toW < 0.1)
    {
        if (hasWall(x, y - 1))
        {
            walls.emplace_back(0, 1, 0);
        }
    }

    if (toE < 0.1)
    {
        if (hasWall(x, y + 1))
        {
            walls.emplace_back(0, -1, 0);
        }
    }

    return walls;
}

void idle()
{
    player.OnIdle(Vec3(0, 0, 1), getWalls());
    //player.OnIdle();
}

void mouse(int x, int y)
{
    player.MouseMove(x, y);
}

void redisplay(int value)
{
    glutTimerFunc(16, redisplay, 1);
    idle();
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpengGL Demo");


    glEnable(GL_LIGHT_MODEL_AMBIENT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat lightAmbient[] = { 0.1F, 0.1F, 0.1F, 1.0F };
    GLfloat lightDiffuse[] = { 1.0F, 1.0F, 1.0F, 1.0F };
    GLfloat lightSpecular[] = { 0.5F, 0.5F, 0.5F, 1.0F };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat lightPosition[] = { 8, 8, 4, 1.0 };   // w²»Îª0
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor3f(0.5, 0.5, 0.5);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keydown);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(mouse);
    glutTimerFunc(16, redisplay, 0);
    //glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
