#include <gl/GLUT.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#define WINDOW_HEIGHT   1000
#define WINDOW_WIDTH    1000



using std::vector;
const double pi = 3.14159;

volatile bool forward(false), back(false), left(false), right(false);

double speed = 0.003;
double player_x = 1.5;
double player_y = 1.5;

double player_headXY = 0.0;   /* radian */
double player_headZ = pi / 2;
double lastMouseX = WINDOW_HEIGHT / 2;
double lastMouseY = WINDOW_WIDTH / 2;

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

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)w / (GLfloat)h, 0.1, 20);
}

void drawCube(int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);

    /* bottom */
    glBegin(GL_QUADS);
    glVertex3f(x, y, 0);
    glVertex3f(x, y + 1, 0);
    glVertex3f(x + 1, y + 1, 0);
    glVertex3f(x + 1, y, 0);
    glEnd();

    /* top */
    glBegin(GL_QUADS);
    glVertex3f(x, y, 1);
    glVertex3f(x, y + 1, 1);
    glVertex3f(x + 1, y + 1, 1);
    glVertex3f(x + 1, y, 1);
    glEnd();

    /* surrounding */
    glBegin(GL_QUADS);
    glVertex3f(x, y, 0);
    glVertex3f(x, y + 1, 0);
    glVertex3f(x, y + 1, 1);
    glVertex3f(x, y, 1);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(x, y, 0);
    glVertex3f(x + 1, y, 0);
    glVertex3f(x + 1, y, 1);
    glVertex3f(x, y, 1);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(x + 1, y + 1, 0);
    glVertex3f(x + 1, y, 0);
    glVertex3f(x + 1, y, 1);
    glVertex3f(x + 1, y + 1, 1);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(x + 1, y + 1, 0);
    glVertex3f(x, y + 1, 0);
    glVertex3f(x, y + 1, 1);
    glVertex3f(x + 1, y + 1, 1);
    glEnd();
}

bool is_overlapped(double x, double y, double head, double cube_size)
{
    double x1 = x + std::cos(head + pi * 45. / 180) * cube_size / sqrt(2);
    double y1 = y + std::sin(head + pi * 45. / 180) * cube_size / sqrt(2);
    double x2 = x + std::cos(head + pi * 135. / 180) * cube_size / sqrt(2);
    double y2 = y + std::sin(head + pi * 135. / 180) * cube_size / sqrt(2);
    double x3 = x + std::cos(head + pi * 225. / 180) * cube_size / sqrt(2);
    double y3 = y + std::sin(head + pi * 225. / 180) * cube_size / sqrt(2);
    double x4 = x + std::cos(head + pi * 315. / 180) * cube_size / sqrt(2);
    double y4 = y + std::sin(head + pi * 315. / 180) * cube_size / sqrt(2);

    if (maze_data[int(std::floor(x1))][int(std::floor(y1))] == 'H')
        return true;
    if (maze_data[int(std::floor(x2))][int(std::floor(y2))] == 'H')
        return true;
    if (maze_data[int(std::floor(x3))][int(std::floor(y3))] == 'H')
        return true;
    if (maze_data[int(std::floor(x4))][int(std::floor(y4))] == 'H')
        return true;

    return false;
}

void move(double angle)
{
    double x_next = player_x + std::cos(player_headXY + angle) * speed;
    double y_next = player_y + std::sin(player_headXY + angle) * speed;
    if (!is_overlapped(x_next, y_next, player_headXY, 0.1))
    {
        player_x = x_next;
        player_y = y_next;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case (unsigned char)119:    /* w */
        forward = true;
        break;
    case (unsigned char)115:    /* s */
        back = true;
        break;
    case (unsigned char)97:     /* a */
        left = true;
        break;
    case (unsigned char)100:    /* d */
        right = true;
        break;

    default: break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case (unsigned char)119:    /* w */
        forward = false;
        break;
    case (unsigned char)115:    /* s */
        back = false;
        break;
    case (unsigned char)97:     /* a */
        left = false;
        break;
    case (unsigned char)100:    /* d */
        right = false;
        break;

    default: break;
    }
}

void drawWalls()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    std::size_t mazeHeight = maze_data.size();
    std::size_t mazeWidth = maze_data[0].size();

    for (auto i = 0; i < mazeHeight; ++i)
    {
        for (auto j = 0; j < mazeWidth; ++j)
        {
            if (maze_data[i][j] == 'H')
                drawCube(i, j);
        }
    }
    glFlush();
}

void viewChange(int x, int y)
{
    if (x > WINDOW_WIDTH / 2 + 100)
        player_headXY -= 0.1 / 180 * pi;
    else if (x < WINDOW_WIDTH / 2 - 100)
        player_headXY += 0.1 / 180 * pi;

    double changeZ = y - lastMouseY;

    if (changeZ > 10)
        player_headZ += 0.1 / 180 * pi;
    else if (changeZ < -10)
        player_headZ -= 0.1 / 180 * pi;

    lastMouseX = x;
    lastMouseY = y;
}

void idle()
{
    if (lastMouseX > WINDOW_WIDTH / 2 + 100)
    {
        player_headXY -= 0.1 / 180 * pi;
    }
    else if (lastMouseX < WINDOW_WIDTH / 2 - 100)
    {
        player_headXY += 0.1 / 180 * pi;
    }
    if (forward)
        move(0);
    if (back)
        move(pi);
    if (left)
        move(pi / 2.);
    if (right)
        move(-pi / 2.);
    glutPostRedisplay();
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(player_x, player_y, 0.5,
              player_x + std::cos(player_headXY), player_y + std::sin(player_headXY), 0.5 + std::cos(player_headZ),
              0, 0, 1);
    drawWalls();
}
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("maze");
    glClearColor(0.4, 0.4, 0.4, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyUp);
    glutPassiveMotionFunc(viewChange);
    glutIdleFunc(idle);
    glutMainLoop();
}




