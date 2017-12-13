//
//  Main.cpp
//
// This program displays an animated human-like figure made
// out of cylinders and spheres.  A right-handed coordinate
// system is used.  The figure is displayed upright along 
// the Y axis, facing forward towards the positive
// Z-axis, with left side of boding facing towards the positive
// X-axis.

// This example was adapted from: 
// E. Angel, OpenGL: A Primer, 3rd edition, Addison-Wesley, 2007, ISBN 0-321-39811-4.

// For assignment 4, add the right arm and right leg. Also add the nose
// and two ears. For the nose, you can use a sphere half exposed and for
// the ears, you can use a sphere elongated to be twice as tall as in
// other dimensions (egg shaped) and half exposed as well. Finally, 
// add two feet on the end of the legs. 

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>

#include "GetGlut.h"
#include "Sleep.h"
#include "Main.h"

using namespace std;

namespace
{
	const unsigned int TARGET_FPS = 40;
	double g_fps = TARGET_FPS;
	int g_next_frame_time;
	const bool SHOW_FPS = true;

	const double NEAR_CLIP = 0.01;
	const double FAR_CLIP = 1000;

	const float TORSO_RADIUS = 3.0f;
	const float TORSO_HEIGHT = 8.0f;
	const float NECK_RADIUS = 0.5f;
	const float NECK_HEIGHT = 1.0f;
	const float HEAD_RADIUS = 1.5f;

	const float UPPER_ARM_RADIUS = 1.0f;
	const float UPPER_ARM_LENGTH = 5.0f;
	const float LOWER_ARM_RADIUS = 1.0f;
	const float LOWER_ARM_LENGTH = 4.0;

	const float UPPER_LEG_RADIUS = 1.5f;
	const float UPPER_LEG_LENGTH = 7.0f;
	const float LOWER_LEG_RADIUS = 1.5f;
	const float LOWER_LEG_LENGTH = 6.0f;

	const float FOOT_RADIUS = 1.5f;
	const float FOOT_LENGTH = 0.5f;

	const float NOSE_RADIUS = 0.3f;
	const float EAR_RADIUS = 0.35f;

	const float HAND_RADIUS = 1.2f;

	// bone identifiers (bone ids)
	const int LIMB_TORSO = 0;
	const int LIMB_NECK = 1;
	const int LIMB_HEAD = 2;
	const int LIMB_UPPER_LEFT_ARM = 3;
	const int LIMB_UPPER_LEFT_LEG = 4;
	const int LIMB_LOWER_LEFT_ARM = 5;
	const int LIMB_LOWER_LEFT_LEG = 6;
	const int LIMB_UPPER_RIGHT_ARM = 7;
	const int LIMB_UPPER_RIGHT_LEG = 8;
	const int LIMB_LOWER_RIGHT_ARM = 9;
	const int LIMB_LOWER_RIGHT_LEG = 10;
	const int LIMB_LEFT_FOOT = 11;
	const int LIMB_RIGHT_FOOT = 12;
	const int LIMB_RIGHT_HAND = 13;
	const int LIMB_LEFT_HAND = 14;
	const int LIMB_NOSE = 15;
	const int LIMB_LEFT_EAR = 16;
	const int LIMB_RIGHT_EAR = 17;
	const int LIMB_HAND = 18;

	char pose;
	const int LIMBCOUNT = 19;

	// initial angle for all bones (in degrees)
	float theta[LIMBCOUNT] 
	{
		0.0, 10.0, 15.0, 20.0,
		30.0, 21.0, 11.0, 20.0,
		30.0, 21.0, 11.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
	};

	// amount by which each bone rotates per frame (in degrees)
	float delta[LIMBCOUNT] =
	{
		0.2f, 0.4f, 0.6f, 0.8f,
		1.2f, 1.6f, 2.0f, 0.8f,
		1.2f, 1.6f, 2.0f, 0.8f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 0.8f
	};

	float minLimb[LIMBCOUNT] =
	{
		0.0, -10.0, -10.0, -90.0, -70.0, 0.0, 0.0, -90.0, -70.0, 0.0, -90.0, -15.0, -15.0, -90.0, -90.0, 
		0.0, 0.0, 0.0, -90.0
	};


	float maxLimb[LIMBCOUNT] =
	{
		0.0, 25.0, 35.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 0.0, 0.0, 0.0, 25.0
	};


	float pose0[LIMBCOUNT] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	};


	float pose1[LIMBCOUNT] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 45, 90, -20, 0, 15, 0, 0, 0, 0, 0, 0
	};


	float pose2[LIMBCOUNT] =
	{
		0, 0, 0, 0, 0, 90, 0, 0, -45, 0, -20, 0, 15, 0, 0, 0, 0, 0, 0

	};

	float pose3[LIMBCOUNT] =
	{
		0, 0, 15, 30, 40, 90, -30, -50, -40, 90, -30, 10, 0, 0, 0, 0, 0, 0
	};

	float pose4[LIMBCOUNT] = 
	{
		0, 0, 15, -50, -40, 90, -30, 30, 40, 90, -30, 10, 10, 0, 0, 0, 0, 0, 0
	};

	

	/*
	const int LIMB_TORSO = 0;
	const int LIMB_NECK = 1;
	const int LIMB_HEAD = 2;
	const int LIMB_UPPER_LEFT_ARM = 3;
	const int LIMB_UPPER_LEFT_LEG = 4;
	const int LIMB_LOWER_LEFT_ARM = 5;
	const int LIMB_LOWER_LEFT_LEG = 6; 
	const int LIMB_UPPER_RIGHT_ARM = 7; 
	const int LIMB_UPPER_RIGHT_LEG = 8; 
	const int LIMB_LOWER_RIGHT_ARM = 9; 
	const int LIMB_LOWER_RIGHT_LEG = 10; 
	const int LIMB_LEFT_FOOT = 11; 
	const int LIMB_RIGHT_FOOT = 12;
	const int LIMB_RIGHT_HAND = 13; 
	const int LIMB_LEFT_HAND = 14;
	const int LIMB_NOSE = 15;-
	const int LIMB_LEFT_EAR = 16;
	const int LIMB_RIGHT_EAR = 17;
	const int LIMB_HAND = 18;
	*/

	// Display the cylinder (by default) along the 
	// positive Z-axis with the origin at the bottom center
	// of the cylinder 
	void display_cylinder(
		GLdouble radius, GLdouble height,
		GLint slices, GLint stacks)
	{
		// Quadrics are used by the GLU library for many
		// 3D shapes
		GLUquadricObj *p = gluNewQuadric();

		// Use a disk to make the bottom of the cylinder.
		// The default disk is vertical facing positive Z-axis,
		// so rotate it around the Y-axis to make it face
		// the other way
		glPushMatrix();
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		gluDisk(p, 0.0, radius, slices, stacks);
		glPopMatrix();

		// main part of cylinder
		gluCylinder(p, radius, radius, height, slices, stacks);

		// Use another disk to make the top of cylinder; 
		// put it out along the positive Z-axis
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, height);
		gluDisk(p, 0.0, radius, slices, stacks);
		glPopMatrix();

		gluDeleteQuadric(p);
	}

	// Display the torso as a cylinder turned upright by rotating 
	// around the X-axis (from its default position along the positive
	// Z-axis).  The resulting torso is along the positive Y-axis
	void display_torso()
	{
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		display_cylinder(TORSO_RADIUS, TORSO_HEIGHT, 60, 15);
		glPopMatrix();
	}


	// Display the neck in the same manner as the torso
	void display_neck()
	{
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		display_cylinder(NECK_RADIUS, NECK_HEIGHT, 60, 15);
		glPopMatrix();
	}

	// Display the head as a sphere elongated along the Y-axis
	void display_head()
	{
		glPushMatrix();
		glScalef(1.0, 1.3, 1.0);
		glutSolidSphere(HEAD_RADIUS, 40, 40);
		glPopMatrix();
	}



	void display_nose()
	{
		glPushMatrix();
		glScalef(1.0, 1.0, 1.0);
		glutSolidSphere(NOSE_RADIUS, 40, 40);
		glPopMatrix();
	}

	void display_ear()
	{
		glPushMatrix();
		glScalef(1.0, 1.0, 1.0);
		glutSolidSphere(EAR_RADIUS, 40, 40);
		glPopMatrix();
	}

	// Display the upper arm as a cylinder turned to face along 
	// the positive X-axis (the figure's left arm) by rotating
	// around the Y axis.
	void display_upper_arm()
	{
		glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		display_cylinder(UPPER_ARM_RADIUS, UPPER_ARM_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_upper_right_arm()
	{
		glPushMatrix();
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		display_cylinder(UPPER_ARM_RADIUS, UPPER_ARM_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_hand()
	{
		glPushMatrix();
		glutSolidSphere(HAND_RADIUS, 40, 40);
		glPopMatrix();
	}

	void display_lower_arm()
	{
		glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		display_cylinder(LOWER_ARM_RADIUS, LOWER_ARM_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_lower_right_arm()
	{
		glPushMatrix();
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		display_cylinder(LOWER_ARM_RADIUS, LOWER_ARM_LENGTH, 15, 15);
		glPopMatrix();
	}


	// Display the upper leg as a cylinder turned to face along 
	// the negative Y-axis (projecting downward) by rotating
	// around the X-axis.
	void display_upper_leg()
	{
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		display_cylinder(UPPER_LEG_RADIUS, UPPER_LEG_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_lower_leg()
	{
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		display_cylinder(LOWER_LEG_RADIUS, LOWER_LEG_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_foot()
	{
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidSphere(FOOT_RADIUS, 15, 15);
		glPopMatrix();

	}

	// To display a human-like figure, one performs a translation, possibly a 
	// rotation, and a display on each component and then repeats for each of
	// its children (connected components further from the root).  To deal 
	// with one of the connected component, such as the neck connected to the 
	// torso and then the head connected to the neck, we push (save) the current 
	// matrix at each step.  We pop the matrix when we are finished with a 
	// component and all its subcomponents. If a particular model does not
	// have its origin at the point where it should be connected, it requires
	// an additional transformation (called a node transformation in the notes).
	void display_person()
	{
		// origin is in the middle of torso
		glTranslatef(0.0, -TORSO_HEIGHT / 2.0, 0.0);
		display_torso();

		// neck, head, nose, and ears
		// base of neck is determined relative to the bottom of the
		// torso.
		glPushMatrix();
		glTranslatef(0.0, TORSO_HEIGHT, 0.0);
		glRotatef(theta[LIMB_NECK], 1.0, 0.0, 0.0);
		display_neck();

		glPushMatrix();
		glTranslatef(0.0, NECK_HEIGHT, 0.0);
		glRotatef(theta[LIMB_HEAD], 0.0, 1.0, 0.0); //head

		glPushMatrix();
		glTranslatef(0.0, HEAD_RADIUS, 0.0); // node transform to compensate for model
		display_head();

		glPushMatrix();
		glTranslatef(0.0, .5*HEAD_RADIUS, HEAD_RADIUS); //nose
		display_nose();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-.75*HEAD_RADIUS, .5*HEAD_RADIUS, 0.0); //right ear
		display_ear();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(.75*HEAD_RADIUS, .5*HEAD_RADIUS, 0.0); //left ear
		display_ear();
		

		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		// left arm
		glPushMatrix();
		glTranslatef(TORSO_RADIUS, TORSO_HEIGHT - UPPER_ARM_RADIUS, 0.0);
		glRotatef(theta[LIMB_UPPER_LEFT_ARM], 0.0, 0.0, 1.0);
		display_upper_arm();

		glPushMatrix();
		glTranslatef(UPPER_ARM_LENGTH, 0.0, 0.0);
		glRotatef(theta[LIMB_LOWER_LEFT_ARM], 0.0, 0.0, 1.0);
		display_lower_arm();

		glPushMatrix();
		glTranslatef(LOWER_ARM_LENGTH, 0.0, 0.0);
		glRotatef(theta[LIMB_HAND], 0.0, 0.0, 1.0);
		display_hand();

		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//right arm
		glPushMatrix();
		glTranslatef(-1*TORSO_RADIUS, TORSO_HEIGHT - UPPER_ARM_RADIUS, 0.0);
		glRotatef(-theta[LIMB_UPPER_RIGHT_ARM], 0.0, 0.0, 1.0);
		display_upper_right_arm();

		glPushMatrix();
		glTranslatef(-UPPER_ARM_LENGTH, 0.0, 0.0);
		glRotatef(-theta[LIMB_LOWER_RIGHT_ARM], 0.0, 0.0, 1.0);
		display_lower_right_arm();

		glPushMatrix();
		glTranslatef(-LOWER_ARM_LENGTH, 0.0, 0.0);
		glRotatef(-theta[LIMB_HAND], 0.0, 0.0, 1.0);
		display_hand();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		// left leg
		glPushMatrix();
		glTranslatef(TORSO_RADIUS - UPPER_LEG_RADIUS, 0.0, 0.0);
		glRotatef(-theta[LIMB_UPPER_LEFT_LEG], 1.0, 0.0, 0.0);
		display_upper_leg();

		glPushMatrix();
		glTranslatef(0.0, -UPPER_LEG_LENGTH, 0.0);
		glRotatef(theta[LIMB_LOWER_LEFT_LEG], 1.0, 0.0, 0.0);
		display_lower_leg();

		glPushMatrix();
		glTranslatef(0.0, (-LOWER_LEG_LENGTH - 0.5f), 0.0);
		glRotatef(theta[LIMB_RIGHT_FOOT], 1.0, 0.0, 0.0);
		glScalef(1.0f, 0.5f, 1.5f);
		display_foot();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		//right leg
		glPushMatrix();
		glTranslatef(-TORSO_RADIUS + UPPER_LEG_RADIUS, 0.0, 0.0);
		glRotatef(-theta[LIMB_UPPER_LEFT_LEG], 1.0, 0.0, 0.0);
		display_upper_leg();

		glPushMatrix();
		glTranslatef(0.0, -UPPER_LEG_LENGTH, 0.0);
		glRotatef(theta[LIMB_LOWER_LEFT_LEG], 1.0, 0.0, 0.0);
		display_lower_leg();

		glPushMatrix();
		glTranslatef(0.0, (-LOWER_LEG_LENGTH - 0.5f), 0.0);
		glRotatef(theta[LIMB_LEFT_FOOT], 1.0, 0.0, 0.0);
		glScalef(1.0f, 0.5f, 1.5f);
		display_foot();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();


	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CS408: Person");
	glutKeyboardFunc(keyboardDown);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init();

	glutMainLoop();

	return 1;
}

void init()
{
	GLfloat mat_ambient[] = { 0.2, 0.4, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.4, 0.4, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0.5, 1.0, 1.0 };
	GLfloat lm_ambient[] = { 0.25, 0.25, 0.25, 1.0 };

	ofstream output("logfile.txt");

	//  select clearing (background) color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//  initialize viewing values
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPointSize(1.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

	glutPostRedisplay();
}



void keyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f': 
		pose = 'f'; //pose 0 and 1
		break;
	case 'b':
		pose = 'b'; //pose 1 and 2
		break;
	case 'g':
		pose = 'g'; //alternate between 3 and 4
		break;

	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}


void idle()
{
	double waste_time; // in seconds

	if (pose == 'f')
	{

		for (int i = 0; i < LIMBCOUNT; i++)
		{
			if (pose1[i] != 0)
				theta[i] += delta[i];

			if ((theta[i] > pose1[i]) || (theta[i] < pose0[i]))
				delta[i] = -delta[i];
		}
	}

	else if (pose == 'b')
	{

		for (int i = 0; i < LIMBCOUNT; i++)
		{

			if (pose2[i] != 0)
			pose1[i] += delta[i];
			if ((theta[i] > pose2[i]) || (theta[i] < pose1[i]))
				delta[i] = -delta[i];
		}
	}

	else if (pose == 'g')
	{

		for (int i = 0; i < LIMBCOUNT; i++)
		{

			if (pose4[i] != 0)
			pose3[i] += delta[i];
			if ((theta[i] > pose4[i]) || (theta[i] < pose3[i]))
				delta[i] = -delta[i];
		}

	}
	else
	{
		for (int i = 0; i < LIMBCOUNT; i++)
		{
			if(theta[i] != 0)
				theta[i] += delta[i];
			if ((theta[i] > maxLimb[i]) || (theta[i] < minLimb[i]))
				delta[i] = -delta[i];
		}
	}
	// wait until time for next frame
	waste_time = (g_next_frame_time - glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	if (SHOW_FPS)
		std::cout << "Waste time in frame =  " << waste_time << " seconds " << std::endl;
	if (waste_time > 0.0)
		sleep(waste_time);

	// calculate real frame rate
	g_fps = 1000.0 / (float(glutGet(GLUT_ELAPSED_TIME) - g_next_frame_time) + 1000.0 / TARGET_FPS);

	// update time to draw next frame
	g_next_frame_time = glutGet(GLUT_ELAPSED_TIME) + 1000.0 / TARGET_FPS;

	// draw next frame
	glutPostRedisplay();
}



void reshape(int w, int h)
{
	// void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far);
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, NEAR_CLIP, FAR_CLIP);
}

void display_axes()
{
	// show X, Y, and Z axis in red, green, and blue
	const double AXIS_LENGTH = 60.0;
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(AXIS_LENGTH, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, AXIS_LENGTH, 0.0);
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, AXIS_LENGTH);
	glEnd();
	glEnable(GL_LIGHTING);
}

void display()
{
	GLfloat light_direction[] = { 1.0, 1.0, 1.0, 0.0 };

	static double s_angle_around = 0.0;
	static double s_height = 0.0;
	static double s_height_delta = 12.0;

	unsigned int error = glGetError();

	if (error != 0)
	{
		cout << "OpenGL Error: " << error << endl;
		assert(error == 0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set up the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);

	// moving camera
	gluLookAt(
		// looking from:
		cos(s_angle_around) * 40, s_height, sin(s_angle_around) * 40,
		// looking at:
		0.0, 0.0, 0.0,
		// vector pointing up from camera 
		// (to orient it right-side up):
		0.0, 1.0, 0.0);

	// still camera for screenshots
	//gluLookAt(5.0, 20.0, 40.0,
	//	0.0, -5.0, 0.0,
	//	0.0, 1.0, 0.0);

	display_axes();

	display_person();

	s_angle_around += 0.5 / g_fps;
	s_height += s_height_delta / g_fps;
	if (s_height <= -25.0 || s_height >= 30.0)
		s_height_delta = -s_height_delta;

	glutSwapBuffers();
}

