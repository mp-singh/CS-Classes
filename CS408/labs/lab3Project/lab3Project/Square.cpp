//
//  Square.cpp
//  lab3Project
//
//  Created by Mandeep Singh on 2017-01-18.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//
#include "GetGlut.h"
#include <GLUT/GLUT.h>
#include <stdio.h>
#include "Square.h"

//Vector2 square_pos(0.0, 0.0);
//Vector2 square_vel(5.0, 1.0);
//double square_age = 0.0;

float Square::random0to1()
{
    return (float)(rand()) / ((float)RAND_MAX + 1.0f);
}
Square::Square()
{
    init();
    age = 999999;
}
void Square::init()
{
    red   = random0to1();
    green = random0to1();
    blue  = random0to1();
    pos.set(0.0, 0.0);
    vel = Vector2::getRandomUnitVector() * 5.0;
    age = 0;
}

void Square::update()
{
    pos += vel;
    age++;
    
}
void Square::draw()
{
    if(isAlive())
    {
        glPushMatrix();
        glTranslated(pos.x, pos.y, 0.0f);
        glBegin(GL_POLYGON);
        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(red, green, blue, 0.4f);
        glVertex2f(-50.0, -50.0);
        glVertex2f(-50.0,  50.0);
        glVertex2f( 50.0,  50.0);
        glVertex2f( 50.0, -50.0);
        glEnd();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPopMatrix();
    }
}

bool Square::isAlive()
{
    return (age <= 60);
}
Square::~Square(){}
