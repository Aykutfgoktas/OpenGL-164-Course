#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD 30 // Period for the timer.
#define TIMER_ON 0      // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;

bool activeTimer = false;
int fishSpeed, submarineSpeed;
int winWidth, winHeight; // current Window width and height

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char *string, void *font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

/*WALL*/
void DrawingWall()
{
    glColor3ub(69, 139, 116);
    glRectf(-500, 400, 500, -400);

    for (int i = 0; i <= 800; i = i + 50)
    {
        glColor3ub(102, 205, 170);
        glBegin(GL_LINES);
        glVertex2f(-500, 400 - i);
        glVertex2f(500, 400 - i);
        glEnd();
    }
}
/*WALL END*/

/*SIGN*/
void DrawingSign()
{
    glColor3ub(0, 0, 0);
    glRectf(-210, 360, 210, 290);
    circle(-200, 325, 35);
    circle(200, 325, 35);

    glColor3ub(102, 205, 170);
    glRectf(-200, 350, 200, 300);
    circle(-200, 325, 25);
    circle(200, 325, 25);

    glColor3ub(0, 0, 0);
    circle(-212, 325, 10);
    circle(212, 325, 10);

    glColor3ub(40, 73, 66);
    glRectf(-180, 345, 180, 305);

    glColor3ub(245, 245, 245);
    vprint(-140, 320, GLUT_BITMAP_9_BY_15, "Aykut Submarine");
}
/*SIGN END*/

/*Submarine*/
void DrawingSubmarine()
{
    /*Body*/
    glColor3ub(33, 33, 33);
    glRectf(-80 + submarineSpeed, -170, -245 + submarineSpeed, -200);
    /*Body End*/

    /*Tail*/
    glRectf(-245 + submarineSpeed, -175, -260 + submarineSpeed, -195);
    /*Tail End*/

    /*Tail*/
    glBegin(GL_TRIANGLES);
    glVertex2f(-260 + submarineSpeed, -185);
    glVertex2f(-270 + submarineSpeed, -185);
    glVertex2f(-265 + submarineSpeed, -165);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-260 + submarineSpeed, -185);
    glVertex2f(-270 + submarineSpeed, -185);
    glVertex2f(-265 + submarineSpeed, -205);
    glEnd();
    /*Tail End*/

    /*Top*/
    glRectf(-215 + submarineSpeed, -170, -195 + submarineSpeed, -155);
    /*Top End*/

    /*Front*/
    circle(-80 + submarineSpeed, -185, 15);
    /*Fron End*/
    glLineWidth(3);

    /*Antena*/
    glBegin(GL_LINES);
    glVertex2f(-242 + submarineSpeed, -170);
    glVertex2f(-242 + submarineSpeed, -150);
    glEnd();
    /*Antena End*/
    glColor3ub(255, 168, 18);
    /*Insıde*/
    glRectf(-235 + submarineSpeed, -180, -205 + submarineSpeed, -190);
    /*Inside End*/

    /*Front White*/
    glColor3ub(255, 255, 255);
    circle(-80 + submarineSpeed, -180, 5);
    /*Front White End*/
}
/*Submarine END*/

/*Fish Start*/
void DrawingFish()
{

    glBegin(GL_TRIANGLES);
    glVertex2f(80 - fishSpeed, 90);
    glVertex2f(115 - fishSpeed, 105);
    glVertex2f(115 - fishSpeed, 75);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(145 - fishSpeed, 90);
    glVertex2f(115 - fishSpeed, 105);
    glVertex2f(115 - fishSpeed, 75);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(145 - fishSpeed, 90);
    glVertex2f(155 - fishSpeed, 100);
    glVertex2f(155 - fishSpeed, 80);
    glEnd();

    glColor3ub(100 - fishSpeed, 0, 0);
    circle(104 - fishSpeed, 94, 3);

    /**********************************************************/

    glColor3ub(0, 0, 100);
    glBegin(GL_TRIANGLES);
    glVertex2f(120 - fishSpeed, 130);
    glVertex2f(155 - fishSpeed, 145);
    glVertex2f(155 - fishSpeed, 115);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(185 - fishSpeed, 130);
    glVertex2f(155 - fishSpeed, 145);
    glVertex2f(155 - fishSpeed, 115);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(185 - fishSpeed, 130);
    glVertex2f(195 - fishSpeed, 140);
    glVertex2f(195 - fishSpeed, 120);
    glEnd();

    glColor3ub(100, 0, 0);
    circle(144 - fishSpeed, 134, 3);

    /**********************************************************************/
    glColor3ub(0, 100, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(20 - fishSpeed, 30);
    glVertex2f(55 - fishSpeed, 105 - 60);
    glVertex2f(55 - fishSpeed, 15);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(85 - fishSpeed, 30);
    glVertex2f(55 - fishSpeed, 45);
    glVertex2f(55 - fishSpeed, 15);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(85 - fishSpeed, 30);
    glVertex2f(95 - fishSpeed, 40);
    glVertex2f(95 - fishSpeed, 20);
    glEnd();

    glColor3ub(100, 0, 0);
    circle(45 - fishSpeed, 34, 3);
}

/*Fish End*/

/*WINDOW*/
void DrawingWindow()
{

    /*Sea*/
    glColor3ub(0, 154, 205);
    circle(0, -50, 323);
    /*Sea*/

    DrawingSubmarine();
    DrawingFish();
    /*Black Window*/
    glLineWidth(5);
    glColor3ub(0, 0, 0);
    circle_wire(0, -50, 325);
    /*Black Window end*/

    glColor3ub(0, 0, 0);
    glLineWidth(7);

    glBegin(GL_LINES);
    glVertex2f(0, 275);
    glVertex2f(0, -375);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(325, -50);
    glVertex2f(-325, -50);
    glEnd();
}
/*WINDOW END*/

//
// To display onto window using OpenGL commands
//
void display()
{
    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    //Drawings
    //

    DrawingWall();
    DrawingSign();
    DrawingWindow();

    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == ' ')
        activeTimer = !activeTimer;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key)
    {
    case GLUT_KEY_UP:
        up = true;
        break;
    case GLUT_KEY_DOWN:
        down = true;
        break;
    case GLUT_KEY_LEFT:
        left = true;
        break;
    case GLUT_KEY_RIGHT:
        right = true;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key)
    {
    case GLUT_KEY_UP:
        up = false;
        break;
    case GLUT_KEY_DOWN:
        down = false;
        break;
    case GLUT_KEY_LEFT:
        left = false;
        break;
    case GLUT_KEY_RIGHT:
        right = false;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    int x2 = x - winWidth / 2;
    int y2 = winHeight / 2 - y;

    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN)
    {
        printf("x= %d, y=%d\n", x2, y2);
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y)
{
    // Write your codes here.

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y)
{
    // Write your codes here.

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//#if TIMER_ON == 1
void onTimer(int v)
{

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.

    if (activeTimer)
    {

        submarineSpeed = submarineSpeed + 18;
        fishSpeed++;
        //fishSpeed = fishSpeed /5;
        printf("%d\n", fishSpeed);

        /*When they hit the frame I rest their coordination*/
        if (submarineSpeed == 356)
        {
            submarineSpeed = 0;
        }
        if (fishSpeed == 336)
        {
            fishSpeed = 0;
        }
    }

    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()
}
//#endif

void Init()
{

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Submarine");
    glutDisplayFunc(display);
    glutReshapeFunc(onResize);
    glutTimerFunc(1000, onTimer, 0);
    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}