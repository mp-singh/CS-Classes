//
//  main.cpp
//  A2
//
//  Created by Mandeep Singh on 2017-02-01.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#include <cassert>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "GetGlut.h"
#include <GLUT/GLUT.h>
#include "ObjLibrary/ObjModel.h"
#include "ObjLibrary/TextureManager.h"
#include "Sleep.h"
#include "myFunctions.h"


using namespace std;
using namespace ObjLibrary;

void init ();
void initDisplay ();
void keyboard (unsigned char key, int x, int y);
void update ();
void reshape (int w, int h);
void display ();

// add your global variables here
int startTime = 0;





int main (int argc, char* argv[])
{
        glutInitWindowSize(1024, 768);
        glutInitWindowPosition(0, 0);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("");
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
    initDisplay();
    buildTable();
    startTime = glutGet(GLUT_ELAPSED_TIME);


}

void initDisplay ()
{
//    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 1, 1);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glutPostRedisplay();
    
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'c':
            sine = true;
            parabolic = false;
            break;
        case 'b':
            sine = false;
            parabolic = false;
            break;
        case 'd':
            sine = false;
            parabolic = true;
            break;
        case 27: // on [ESC]
            exit(0); // normal exit
            break;
    }
}

void update ()
{
    // update your variables here
    
    sleep(1.0 / 60.0); // 60fps
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(20.0, 10.0, 50.0,
              20.0, 10.0, -50.0,
              0.0, 1.0, 0.0);
    drawCntrlPoints();
    drawCurve();
    drawSphereY(startTime);
    glutSwapBuffers();

}

