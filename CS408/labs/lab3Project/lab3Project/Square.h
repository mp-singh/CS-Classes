//
//  Square.h
//  lab3Project
//
//  Created by Mandeep Singh on 2017-01-18.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#ifndef Square_h
#define Square_h


#endif /* Square_h */
#include "ObjLibrary/Vector2.h"

using namespace ObjLibrary;

class Square
{
private:
    Vector2 pos;
    Vector2 vel;
    double age;
    float random0to1();
    float red;
    float green;
    float blue;
public:
    Square();
    ~Square();
    void update();
    void draw();
    void init();
    bool isAlive();
};
