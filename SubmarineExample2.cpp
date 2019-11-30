/*
PROBLEMS: Do not fire correctly
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>


#define WINDOW_WIDTH  1500
#define WINDOW_HEIGHT 850

#define TIMER_PERIOD  30 // Period for the timer.
#define TIMER_ON         0 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

/*My Variable Start*/
int submarineMotor;
bool activeTimer=false;
float angle = 0;
float angle2 ;
bool  whichText=false;
float forX, forY;
float A = 100, //amplitude
fq = 1,  //frequency
C = 0,   //horizontal phase shift
B = 0;   //vertical phase shift

int fireCorx,fireCory;
bool activeFire=false;

typedef struct {
	float x, y;
} pos_t;


pos_t p0, 
p1, 
p2;  

int mx=0;

/*My Variable End*/

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
	for (i = 0; i<len; i++)
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
	for (i = 0; i<len; i++)
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
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

/*Submarine*/
void DrawingSubmarine() {
	/*Body*/
	glColor3ub(33, 33, 33);
	glRectf(-765 + submarineMotor, 330, -930 + submarineMotor , 300);
	/*Body End*/

	/*Tail*/
	glRectf(-930 + submarineMotor , 325, -945 + submarineMotor,305);
	/*Tail End*/

	/*Tail*/
	glBegin(GL_TRIANGLES);
	glVertex2f(-945 + submarineMotor, 315);
	glVertex2f(-955 + submarineMotor , 315);
	glVertex2f(-950 + submarineMotor ,335);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-945 + submarineMotor, 315);
	glVertex2f(-955 + submarineMotor ,315);
	glVertex2f(-950 + submarineMotor , 295);
	glEnd();
	/*Tail End*/

	/*Top*/
	glRectf(-900 + submarineMotor, 330, -880 + submarineMotor ,345);
	/*Top End*/

	/*Front*/
	circle(-765 + submarineMotor , 315, 15);
	/*Fron End*/
	glLineWidth(3);

	/*Antena*/
	glBegin(GL_LINES);
	glVertex2f(-927 + submarineMotor , 330);
	glVertex2f(-927 + submarineMotor, 350);
	glEnd();
	/*Antena End*/
	glColor3ub(255, 168, 18);
	/*Insıde*/
	glRectf(-920 + submarineMotor, 320, -890 + submarineMotor, 310);
	/*Inside End*/

	/*Front White*/
	glColor3ub(255, 255, 255);
	circle(-765 + submarineMotor,320, 5);
	/*Front White End*/

}
/*Submarine END*/

/*Drawing Mine*/
void drawMine(float xf,float yf) {
	
	glColor3ub(5, 20, 70);
	circle(-35+ xf, 15-yf, 25);
	
	glColor3ub(0, 0, 70);
	glBegin(GL_TRIANGLES);
	glVertex2f( 75+xf -100, 40-yf);
	glVertex2f( 55 + xf-100, 40 - yf);
	glVertex2f(65 + xf-100, 55 - yf);
	glEnd();

	glColor3ub(0, 0, 70);
	glBegin(GL_TRIANGLES);
	glVertex2f(90 + xf - 100, 25 - yf);
	glVertex2f(90 + xf - 100, 5 - yf);
	glVertex2f(105 + xf - 100, 15 - yf);
	glEnd();

	glColor3ub(0, 0, 70);
	glBegin(GL_TRIANGLES);
	glVertex2f(40 + xf - 100, 25 - yf);
	glVertex2f(40 + xf - 100, 5 - yf);
	glVertex2f(25 + xf - 100, 15 - yf);
	glEnd();

	glColor3ub(0, 0, 70);
	glBegin(GL_TRIANGLES);
	glVertex2f(75 + xf - 100, -10 - yf);
	glVertex2f(55 + xf - 100, -10 - yf);
	glVertex2f(65 + xf - 100, -25 - yf);
	glEnd();
	
}
/*Drawing Mine*/
void centerItem() {

	float r = fabs(A);
	glColor3f(0.3, 0.3, 1.0);
	circle_wire(-35, 15, r); 
	glColor3f(1, 0, 0);

	
	forX = r * cos(angle * D2R);
	forY = r * sin(angle*D2R);
	
	if (!activeTimer) {
	
		angle = 0;
	}
	drawMine(forX,forY);
}

void ball() {
	if (activeFire == true) {
		circle(-74 + 50 * cos(angle2 * D2R)+fireCorx, -376 + 50 * sin(angle2 * D2R)+fireCory, 10);
	}
	
}

void drawLazer(int mx) {
	glColor3ub(210, 105, 30);
	glBegin(GL_TRIANGLES);
	glVertex2f(-70+mx,-350);
	glVertex2f(-95 + mx,-375);
	glVertex2f(-45 + mx,-375);
	glEnd();

	glRectf(-78 + mx,-358,-65 + mx,-340);

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-72+mx, -341);
	glVertex2f(-72+ 50 * cos(angle2 * D2R)+mx, -330 + 50 * sin(angle2 * D2R));
	glEnd();

	circle(-72 + mx,-341,8);

}

void drawBottomMenu() {
	glColor3ub(1, 1, 1);
	glRectf(-750, -375, 750,-425);

	glColor3ub(245, 245, 245);
	if (!whichText)
	{
		vprint(-140, -400, GLUT_BITMAP_9_BY_15, "Press <F1> to Start a new game");	

	}

	else
	{
		
		vprint(-140, -400, GLUT_BITMAP_9_BY_15, "<SpaceBar> Fire, <F1> Pause/Restart");
	}
	

}

//
// To display onto window using OpenGL commands
//
void display() {
	//
	// clear window to black
	//
	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawingSubmarine();
	centerItem();
	drawBottomMenu();
	ball();
	drawLazer(mx);
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

	if (key == ' ') {
		activeFire = true;
	}
	
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

	if (key == GLUT_KEY_F1) {
		whichText = !whichText;
		activeTimer = !activeTimer;
		submarineMotor = 0;
		mx = 0;
		
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

	// Write your codes here.
	int x2 = x - winWidth / 2;
	int y2 = winHeight / 2 - y;

	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
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
float f(float x) {
	return A * sin((fq * x + C) * D2R) + B;
}
//#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (activeTimer) {

		submarineMotor = submarineMotor + 10;
		/*Restar the submarine */
		if (submarineMotor >= WINDOW_WIDTH+300) {
			submarineMotor = 0;
			
		}

		angle += 2;
		if (angle > 360)
			angle -= 360;

	
		p0.x = -350;
		p0.y = f(angle);
		p0.y += 25; 

		
		/*Move the lazer*/
		if (right == true) {
			if (mx < 795) {
				mx = mx + 5;
			}
			
		}
		/*Move the lazer*/
		if (left == true) {
			if (mx > -650) {
				mx = mx - 5;
			}
			
		}
		
		if (up == true) {
			/*Rotate the lase and limit the lazer*/
			if (angle2 >= -54)
			{
				angle2 = angle2 - 3;
				
			}
			
			
		}
		if (down == true) {
			/*Rotate the lase and limit the lazer*/
			if (angle2 < 240) {
				angle2 = angle2 + 3;
			}
			
			
		}

		if (activeFire) {
			fireCorx=fireCorx+10;
			fireCory=fireCory+10;
			printf("%d %d \n", fireCorx,fireCory);
			if (fireCorx > 810 && fireCory > 810) {
				activeFire = false;
				fireCorx = 0;
				fireCory = 0;
			}
		}
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
	glutCreateWindow("HW-3: Hitting The Target by Aykut");

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