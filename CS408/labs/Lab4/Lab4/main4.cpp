//
//  Main4.cpp
//

#include <cassert>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <iostream>

#include "GetGlut.h"
#include <GLUT/GLUT.h>
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/TextureManager.h"
#include "Sleep.h"

using namespace std;
using namespace ObjLibrary;

void init ();
void initDisplay ();
void keyboard (unsigned char key, int x, int y);
void update ();
void reshape (int w, int h);
void display ();

// add your global variables here
ObjModel spiky;
ObjModel bucket;
ObjModel skybox;


int main (int argc, char* argv[])
{
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Loading OBJ Models");
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 1;
}

void init ()
{
    spiky.load("Spiky.obj");
    bucket.load("firebucket.obj");
	initDisplay();
}

void initDisplay ()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void update ()
{
	// update your variables here
	
	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

void reshape (int w, int h)
{
	glViewport (0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void display ()
{
    for (int i = 1; i <= 3; i++)
    {
        glPushMatrix();
        glTranslatef(-i, 0.f, 0.f);
        glScalef(0.005f, 0.005f, 0.005f);
        bucket.draw();
        glPopMatrix();
    }
    glColor3f(1.0f, 0.2f, 0.3f);
    spiky.draw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(2.0, 3.0, 4.0,
	          0.0, 0.0, 0.0,
	          0.0, 1.0, 0.0);

	// display positive X, Y, and Z axes near origin
	glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(2.0, 0.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 2.0, 0.0);
		glColor3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 2.0);
	glEnd();

	// draw a purple wireframe cube
	glColor3d(1.0, 0.0, 1.0);
	glPushMatrix();
		glTranslated(0.0, 0.0, 0.0);
		glRotated(45, 0.0, 1.0, 0.0);
		glScaled(1.0, 1.0, 1.0);
		glutWireCube(1.0);
	glPopMatrix();

	glutSwapBuffers();
}
