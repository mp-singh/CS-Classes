//
//  Main3.cpp
//

#include <string>
#include <stdlib.h>

#include "GetGlut.h"
#include <GLUT/GLUT.h>
#include "Sleep.h"

#include "Square.h"

//#include <GL/glut.h>

using namespace std;
using namespace ObjLibrary;

// prototypes
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void update();
void reshape(int w, int h);
void display();

// declare global variables here

const unsigned int SQUARE_COUNT = 100;
Square squares[SQUARE_COUNT];
unsigned int next_square = 0;
bool emitter_on = true;


int main (int argc, char** argv)
{
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Particles");
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	initDisplay();

	glutMainLoop();

	return 1;
}

void initDisplay()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
        case ' ':
        {
            emitter_on = !emitter_on;
            break;
        }
        case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}



void update()
{
   
    next_square = (next_square + 1) % SQUARE_COUNT;
    if(emitter_on)
    {
        squares[next_square].init();
    }
	// update your variables here
    for(int i = 0; i < SQUARE_COUNT; i++)
    {
        squares[i].update();
    }
	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport (0, 0, w, h);

	int x_center = w / 2;
	int y_center = h / 2;

	// set up a 2D view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-x_center, w - x_center, -y_center, h - y_center);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the screen - any drawing before here will not display
    for(int i = 0; i < SQUARE_COUNT; i++)
    {
        squares[i].draw();
    }
    
 

	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
}


