//
//  Particles.h
//  A1
//
//  Created by Mandeep Singh on 2017-01-19.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#ifndef Particles_h
#define Particles_h

#include <stdio.h>

#include "ObjLibrary/Vector2.h"
using namespace ObjLibrary;
#endif /* Particles_h */
class Particle
{
private:
//    const float redColorIncrement = 0.05f;
//    const float greenColorIncrement = 0.05f;
//    const float blueColorIncrement = 0.05f;
    const float opIncrement = 0.0;
    const float xPosIncrement = 10;
    const float yPosIncrement = 10;
    const float xVelocityIncrement = 10;
    const float yVelocityIncrement = 10;
protected:
    float red;
    float blue;
    float green;
    float op;
    float xScale;
    float yScale;
    float xVelocity;
    float yVelocity;
    
    float xPosition;
    float yPosition;

    Vector2 particlePos;
    Vector2 particleVel;
    float particleAge;
    float opacity;
    

  

    
public:
    Particle();
    Particle(Particle const &particle);
    ~Particle();
    float random0to60();
    
    void setRedColor(float red);
    void setGreenColor(float green);
    void setBlueColor(float blue);
    float getRedColor() const;
    float getGreenColor() const;
    float getBlueColor() const;
    
    void setParticleAge(float age);
    float getParticleAge() const;

    void setOpacity(float newOpacity);
    float getOpacity() const;
    
    float getParticleAge();

    void moveLeft(float x);
    void moveRight(float x);
    void moveUp(float y);
    void moveDown(float y);
    
    void addVelocity();
    void removeVelocity();
    void setColor(float r, float g, float b, float o);
    void setScale(float x, float y);
    void setPosition(float x, float y);
    
    void init();
    void update();
    virtual void draw() = 0;
    void updateParticle();
    bool isAlive();
    void setVelocity(float vel);
};

class Square: public Particle
{
public:
    void draw();
    Square();
    Square(Particle const& particle);
};
class LStar:public Particle
{
public:
    void draw();
    LStar();
    LStar(Particle const& particle);
};
class Octagon:public Particle
{
public:
    void draw();
    Octagon();
    Octagon(Particle const& particle);
};
class Kite:public Particle
{
public:
    void draw();
    Kite();
    Kite(Particle const& particle);
};
class SStar:public Particle
{
public:
    void draw();
    SStar();
    SStar(Particle const& particle);
};

