//
//  Particles.cpp
//  A1
//
//  Created by Mandeep Singh on 2017-01-19.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#include <stdlib.h>
#include "Particles.h"
#include "GetGlut.h"
#include <GLUT/GLUT.h>
#include <cmath>

Particle::~Particle(){}

void Particle::init()
{
    xPosition = 0;
    yPosition = 0;
    xVelocity = 1.0f;
    yVelocity = 0.0f;
    particlePos.set(xPosition, yPosition);
    particleVel = Vector2(xVelocity, yVelocity) * 5;
    particleVel.rotate(M_PI*(random0to60() - 30)/180);
    
    particleAge = 2;
    red = 0.25;
    blue = 0.25;
    green = 0.25;
    op = 0.3;
    xScale = 100;
    yScale = 100;
}

float Particle::random0to60 ()
{
    return rand()%(61);
}
void Particle::update()
{
    particlePos += particleVel;
    particleAge++;
    
}

bool Particle::isAlive()
{
    return (particleAge <= 60);
}

Particle::Particle()
{
    init();
}
Particle::Particle(Particle const &p)
{


    particleAge = p.particleAge;
    particlePos = p.particlePos;
    particleVel = p.particleVel;
    xScale = p.xScale;
    yScale = p.yScale;
}



float Particle::getParticleAge() const
{
    return particleAge;
}

void Particle::setParticleAge(float age)
{
    particleAge = age;
}

void Particle::setColor(float r, float g, float b, float o)
{
    red = r;
    green = g;
    blue = b;
    op = o;
}

void Particle::setPosition(float x, float y)
{
    xPosition = x;
    yPosition = y;
}
void Particle::setScale(float x, float y)
{
    xScale = x;
    yScale = y;
}


void Particle::moveRight(float x)
{
    xPosition += xPosIncrement;
    particlePos.set(xPosition, yPosition);
}

void Particle::moveLeft(float x)
{
    xPosition -= xPosIncrement;
    particlePos.set(xPosition, yPosition);
}

void Particle::moveUp(float y)
{
    yPosition += yPosIncrement;
    particlePos.set(xPosition, yPosition);
}

void Particle::moveDown(float y)
{
    yPosition -=yPosIncrement;
    particlePos.set(xPosition, yPosition);
}

//void Particle::addVelocity()
//{
//    xVelocity += xVelocityIncrement;
//    yVelocity += yVelocityIncrement;
//}
//
//void Particle::removeVelocity()
//{
//    xVelocity -= xVelocityIncrement;
//    yVelocity -= yVelocityIncrement;
//}

void Particle::setVelocity(float vel)
{
    xVelocity = vel;
}

SStar::SStar(){}
Square::Square(){}
Octagon::Octagon(){}
Kite::Kite(){}
LStar::LStar(){};


SStar::SStar(Particle const& particle) : Particle(particle){}
Square::Square(Particle const& particle) : Particle(particle){}
LStar::LStar(Particle const& particle) : Particle(particle){}
Octagon::Octagon(Particle const& particle) : Particle(particle){}
Kite::Kite(Particle const& particle) : Particle(particle){}


void SStar::draw()
{
    glPushMatrix();
    glTranslated(particlePos.x, particlePos.y, 0.0);
    glScalef(xScale, yScale, 500); //Scaling object
    
    
    glBegin(GL_TRIANGLE_FAN);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, op);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -0.25f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f( 0.5f, 0.5f);
    glVertex2f(0.0f, 0.25f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    
    glEnd();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPopMatrix();
}
void Square::draw()
{
    glPushMatrix();
    glTranslated(particlePos.x, particlePos.y, 0.0);
    glScalef(xScale, yScale, 500); //Scaling object//
    //    glScalef(100,100, 500); //Scaling object
    
    glBegin(GL_TRIANGLE_FAN);
    glEnable(GL_BLEND);
    //            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, op);
    
    
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -0.05f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f,  0.5f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPopMatrix();
}

void Octagon::draw()
{
    //octagon
    
    glPushMatrix();
    glTranslated(particlePos.x, particlePos.y, 0.0);
    glScalef(xScale, yScale, 500); //Scaling object
    
    glBegin(GL_TRIANGLE_FAN);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, op);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -0.75f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f(0.75f, 0.0f);
    glVertex2f( 0.5f, 0.5f);
    glVertex2f(0.0f, 0.75f);
    glVertex2f(-0.5f,  0.5f);
    glVertex2f(-0.75f, 0.0f);
    glEnd();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPopMatrix();
}

void Kite::draw()
{
    //kite
    glPushMatrix();
    glTranslated(particlePos.x, particlePos.y, 0.0);
    //    glScalef(xScale, yScale, 0); //Scaling object
    glScalef(xScale, yScale, 500); //Scaling object
    
    glBegin(GL_TRIANGLE_FAN);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, op);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-0.5f,  0.5f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPopMatrix();
    
}

void LStar::draw()
{
    //big star
    glPushMatrix();
    glTranslated(particlePos.x, particlePos.y, 0.0);
    //    glScalef(xScale, yScale, 0); //Scaling object
    
    glScalef(xScale, yScale, 500); //Scaling object
    
    glBegin(GL_TRIANGLE_FAN);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, op);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, -1.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f(1.5f, 0.0f);
    glVertex2f( 0.5f, 0.5f);
    glVertex2f(0.0f, 1.5f);
    glVertex2f(-0.5f,  0.5f);
    glVertex2f(-1.5f, 0.0f);
    glEnd();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPopMatrix();
}


//
//void Particle::addRedColor()
//{
//    if(redColor >= 0.0f && redColor <= 1.0f)
//    {
//        redColor += redColorIncrement;
//    }
//    else
//        redColor = 1.0f;
//}
//void Particle::addGreenColor()
//{
//    if(greenColor >= 0.0f && greenColor <= 1.0f)
//    {
//        greenColor += greenColorIncrement;
//    }
//    else
//        redColor = 1.0f;
//}
//void Particle::addBlueColor()
//{
//    if(blueColor >= 0.0f && blueColor <= 1.0f)
//    {
//        blueColor += blueColorIncrement;
//    }
//    else
//        blueColor = 1.0f;
//}
//void Particle::removeRedColor()
//{
//    if(redColor >= 0.0f && redColor <= 1.0f)
//        redColor -= redColorIncrement;
//    else
//        redColor = 0.0f;
//}
//void Particle::removeGreenColor()
//{
//    if(greenColor >= 0.0f && greenColor <= 1.0f)
//        greenColor -= greenColorIncrement;
//    else
//        greenColor = 0.0f;
//}
//
//void Particle::removeBlueColor()
//{
//    if(blueColor >= 0.0f && blueColor <= 1.0f)
//        blueColor -= blueColorIncrement;
//    else
//        blueColor = 0.0f;
//}
//
//void Particle::addOpacity()
//{
//    if(opacity >= 0.0 && opacity <= 1.0)
//        opacity += opIncrement;
//    else
//    {
//        opacity = 1.0;
//    }
//}
//
//void Particle::removeOpacity()
//{
//    if(opacity >= 0.0 && opacity <= 1.0)
//        opacity -= opIncrement;
//    else
//    {
//        opacity = 0.05;
//    }
//}

//void Particle::setOpacity(float newOpacity)
//{
//    opacity = newOpacity;
//}
//float Particle::getOpacity() const
//{
//    return opacity;
//}

//void Particle::addScale()
//{
//    if(xScale >= 1 && xScale <= 200)
//    {
//        xScale += xScaleIncrement;
//        yScale += yScaleIncrement;
//    }
//    else
//    {
//        //        cout << "'+' max size"<<endl;
//        xScale = 100;
//        yScale = 100;
//    }
//}
//void Particle::removeScale()
//{
//    if(xScale >= 1 && xScale <= 200)
//    {
//        xScale -= xScaleIncrement;
//        yScale -= yScaleIncrement;
//    }
//    else
//    {
//        //        cout << "'-' min size"<<endl;
//        xScale = 100;
//        yScale = 100;
//    }
//}
