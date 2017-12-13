//
//  main1.cpp
//
#include <iostream>
#include <stdlib.h>

#include "Sleep.h"
#include <GLUT/glut.h>
#include "ObjLibrary/Vector2.h"
#include "Particles.h"

using namespace std;
using namespace ObjLibrary;

//********** function prototypes **********//
//*****************************************//
void display();
void idle();
void changeShape(int shape);
void keyboard (unsigned char key, int x, int y);
void special (int special_key, int x, int y);
void reshape(int w, int h);
void initDisplay();

//*****************************************//
//*****************************************//


//****** declare global variables here *****//
//*****************************************//
const float xScaleIncrement = 10;
const float yScaleIncrement = 10;
const float redColorIncrement = 0.05f;
const float greenColorIncrement = 0.05f;
const float blueColorIncrement = 0.05f;
const float opIncrement = 0.0;
const float xPosIncrement = 10;
const float yPosIncrement = 10;
const float xVelocityIncrement = 10;
const float yVelocityIncrement = 10;
const unsigned int PARTICLE_COUNT = 100;
Particle *particle[PARTICLE_COUNT];

unsigned int nextParticle = 0;
bool emmitter_on = true;
int shape = 0;
int shIncrement = 1;
float redColor = 0.25f;
float greenColor = 0.25f;
float blueColor = 0.25f;
float opacity = 1.0f;
float xScale = 100;
float yScale = 100;
float xPos = 0;
float yPos = 0;
float xVel = 1.0f;
float yVel = 0.0f;


//*****************************************//
//*****************************************//



//*************** Main Driver *************//
//*****************************************//
int main (int argc, char** argv)
{
    // initialize OpenGL; pass it the command line arguments
    glutInit(&argc, argv);
    glutInitWindowSize (500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Assignment1");
    glutKeyboardFunc(keyboard);
    //    glutSpecialFunc(special);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    initDisplay();
    glutMainLoop();
    return 1;
}
//*****************************************//
//*****************************************//
void initDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    for(int i = 0; i < PARTICLE_COUNT; i++)
    {
        particle[i] = new SStar();
    }
    
    
    glutPostRedisplay();
}


//******** Function for arrow keys ********//
void special (int special_key, int x, int y)
{
    switch(special_key)
    {
        case GLUT_KEY_UP:
        {
            for(int i = 0; i < PARTICLE_COUNT; i++)
            {
                xVel += xVelocityIncrement;
                particle[i]->setVelocity(xVel);
            }
            
        }
            break;
        case GLUT_KEY_DOWN:
        {
            for(int i = 0; i < PARTICLE_COUNT; i++)
            {
                xVel -= xVelocityIncrement;
                particle[i]->setVelocity(xVel);
            }
        }
            
            break;
    }
}
//*****************************************//
//*****************************************//


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


//********** Idle function ***************//
//*****************************************//
void idle()
{
    nextParticle = (nextParticle + 1) % PARTICLE_COUNT;
    if(emmitter_on)
    {
        particle[nextParticle] = new SStar();
    }
    for(int i = 0; i < PARTICLE_COUNT; i++)
    {
        particle[i]->update();
    }
    sleep(1.0 / 60.0); // 60 fps
    // tell OpenGL to redisplay as often as possible
    glutPostRedisplay();
}
//*****************************************//
//*****************************************//




//********** Keyboard Function ************//
//*****************************************//
void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'R':
        {
            if(redColor >= 0.0f && redColor <= 1.0f)
            {
                redColor += redColorIncrement;
            }
            else
                redColor = 1.0f;
            break;
        }
        case 'r':
        {
            if(redColor >= 0.0f && redColor <= 1.0f)
                redColor -= redColorIncrement;
            else
                redColor = 0.0f;
            
            break;
        }
        case 'G':
        {
            if(greenColor >= 0.0f && greenColor <= 1.0f)
            {
                greenColor += greenColorIncrement;
            }
            else
                redColor = 1.0f;
            break;
        }
        case 'g':
        {
            if(blueColor >= 0.0f && blueColor <= 1.0f)
                blueColor -= blueColorIncrement;
            else
                blueColor = 0.0f;
            break;
        }
        case 'B':
        {
            if(blueColor >= 0.0f && blueColor <= 1.0f)
            {
                blueColor += blueColorIncrement;
            }
            else
                blueColor = 1.0f;
            break;
        }
        case 'b':
        {
            if(blueColor >= 0.0f && blueColor <= 1.0f)
                blueColor -= blueColorIncrement;
            else
                blueColor = 0.0f;
            break;
        }
        case 'T':
        {
            if(opacity >= 0.0 && opacity <= 1.0)
                opacity += opIncrement;
            else
            {
                opacity = 1.0;
            }
            
            break;
        }
        case 't':
        {
            if(opacity > 0.0 && opacity <= 1.0)
                opacity -= opIncrement;
            else
            {
                opacity = 0.05;
            }
            
            break;
        }
        case ' ':
        {
            emmitter_on = !emmitter_on;
            break;
        }
        case '+':
        {
            if(xScale >= 1 && xScale <= 200)
            {
                xScale += xScaleIncrement;
                yScale += yScaleIncrement;
            }
            else
            {
                //        cout << "'+' max size"<<endl;
                xScale = 100;
                yScale = 100;
            }
            break;
        }
        case '-':
        {
            if(xScale >= 1 && xScale <= 200)
            {
                xScale -= xScaleIncrement;
                yScale -= yScaleIncrement;
            }
            else
            {
                //        cout << "'-' min size"<<endl;
                xScale = 100;
                yScale = 100;
            }
            break;
        }
        case 'H':
        {
            if(shape >= 0 && shape < 4)
                shape += shIncrement;
            else
            {
                shape = 4;
            }
            changeShape(shape);
            
            break;
        }
        case 'h':
        {
            if(shape > 0 && shape <= 4)
                shape -= shIncrement;
            else
            {
                shape = 0;
            }
            changeShape(shape);
            
            break;
        }
        case 'd':
        {
            xPos += xPosIncrement;
            break;
        }
        case 'a':
        {
            xPos -=xPosIncrement;
            break;
        }
        case 'w':
        {
            yPos += yPosIncrement;
            break;
        }
        case 's':
        {
            yPos -= yPosIncrement;
            break;
        }
        case 27: // on [ESC]
            exit(0); // normal exit
            break;
    }
}
//*****************************************//
//*****************************************//


//*****************************************//
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        particle[i]->setColor(redColor, greenColor,blueColor ,opacity);
        particle[i]->setScale(xScale, yScale);
        //        particle[i]->moveRight(xPos);
        //        particle[i]->moveLeft(xPos);
        //        particle[i]->moveUp(yPos);
        //        particle[i]->moveDown(yPos);
        //        particle[i]->setPosition(xPos, yPos);
        
        particle[i]->draw();
    }
    
    // ensure that all buffered OpenGL commands get done
    glFlush();
    glutSwapBuffers();
}
//*****************************************//
//*****************************************//

void changeShape(int shape)
{
    for(int i = 0; i < PARTICLE_COUNT; i++)
    {
        if(shape == 0)
        {
            particle[i] = new SStar(*particle[i]);
        }
        if(shape == 1)
        {
            particle[i] = new Square(*particle[i]);
        }
        if(shape == 2)
        {
            particle[i] = new Octagon(*particle[i]);
        }
        if(shape == 3)
        {
            particle[i] = new Kite(*particle[i]);
        }
        if(shape == 4)
        {
            particle[i] = new LStar(*particle[i]);
        }
    }
}
