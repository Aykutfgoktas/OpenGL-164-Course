/*********
----------
PROBLEMS: No lighting
----------
ADDITIONAL FEATURES:
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  40 // Period for the timer.
#define TIMER_ON         0 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height


/*My variable start*/
bool randomAngle=false;
bool activeTimer=false;
float angle = 0,angle2=0,angle3=0;
float forX, forY;
bool off1=false, off2=false, off3=false;
float A = 100, //amplitude
fq = 1,  //frequency
C = 0,   //horizontal phase shift
B = 0;   //vertical phase shift

/*Random radius*/
int rforRandom1=rand()%10+3, rforRandom2 = rand() % 10 + 3, rforRandom3 = rand() % 10 + 3;
/*My variable end*/

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
		angle = 2 * PI*i / 100;
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
		angle = 2 * PI*i / 100;
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
void vprint2(int x, int y, float size, const char *string, ...) {
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

void centerBalls() {

	float r = fabs(A);
	float r2 = fabs(A) + 25;
	float r3 = fabs(A) + 50;


	glColor3f(0.3, 0.3, 1.0);
	circle_wire(-35, 15, r);
	circle_wire(-35, 15, r2);
	circle_wire(-35, 15, r3);
	glColor3f(0,0,0);
	/*Black Ball start*/
	circle(-35,15,15);
	/*Blak Ball end*/
	forX = r * cos(angle * D2R);
	forY = r * sin(angle*D2R);

	if (off1) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(1, 0, 0);
	}
	circle(r*cos(angle * D2R) -35, r*sin(angle*D2R) + 15, rforRandom1);
	if (off2) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(0, 1, 0);
	}
	circle(r2*cos(angle2 * D2R) - 35, r2*sin(angle2*D2R) + 15, rforRandom2);
	
	if (off3) {
		glColor3f(0, 0, 0);
	}
	else {
		glColor3f(0, 0, 1);
	}
	circle(r3*cos(angle3 * D2R) - 35, r3*sin(angle3*D2R) + 15, rforRandom3);


}

void drawingBottom() {

	glColor3ub(33, 33, 33);
	glRectd(-400,-350,400,-400);
	glColor3f(1, 1, 1);

	/*Deciding which text will be used*/
		if (off1) {
			vprint(-350, -380, GLUT_BITMAP_9_BY_15, "F1(Red):OFF");
		}
		else {
			vprint(-350, -380, GLUT_BITMAP_9_BY_15, "F1(Red):ON");
		}

		if (off2) {
			vprint(-200, -380, GLUT_BITMAP_9_BY_15, "F2(Green):OFF");
		}
		else {
			vprint(-200, -380, GLUT_BITMAP_9_BY_15, "F2(Green):ON");
		}

		if (off3) {
			vprint(-70, -380, GLUT_BITMAP_9_BY_15, "F3(Blue):OFF");
		}
		else {
			vprint(-70, -380, GLUT_BITMAP_9_BY_15, "F3(Blue):ON");
		}
	

	
	if (!activeTimer) {
		vprint(70, -380, GLUT_BITMAP_9_BY_15, "F4(Animation):OFF");
	}
	else
	{
			vprint(70, -380, GLUT_BITMAP_9_BY_15, "F4(Animation):ON");	
	}
	
	vprint(250, -380, GLUT_BITMAP_9_BY_15, "F5: Restart");
	
}

//
// To display onto window using OpenGL commands
//
void display() {
	//
	// clear window to black
	//
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	centerBalls();
	drawingBottom();

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
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	if (key == GLUT_KEY_F4) {
		activeTimer = !activeTimer;
	}

	/*Different restart point*/
	if (key == GLUT_KEY_F5) {
		activeTimer = false;
		randomAngle = !randomAngle;
		if (randomAngle == true) {
			/*Random Radiues for balls*/
			angle = rand() % 360;
			angle2 = rand() % 360;
			angle3 = rand() % 360;
			randomAngle = !randomAngle;

		}
		rforRandom1 = rand() % 10+3;
		rforRandom2 = rand() % 10+3;
		rforRandom3 = rand() % 10+3;
	}
	/*Text and color on off part*/
	if (key == GLUT_KEY_F1) {
		off1 = !off1;
	}
	if (key == GLUT_KEY_F2) {
		off2 = !off2;
	}
	if (key == GLUT_KEY_F3) {
		off3 = !off3;
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
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}
	/*if (key == GLUT_KEY_F5) {
		randomAngle = !randomAngle;
	}*/
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

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (activeTimer) {
/*Random value assign to speed*/
		angle +=rand()%15;
		if (angle > 360)
			angle -= 360;

		angle2 += rand() % 10;
		if (angle2 > 360)
			angle2 -= 360;

		angle3 += rand() % 10;
		if (angle3 > 360)
			angle3 -= 360;

		
	}

	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
//#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework-4 (800x800)");

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

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}