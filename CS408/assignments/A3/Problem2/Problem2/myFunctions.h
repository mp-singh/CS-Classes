//
//  myFunctions.h
//  Problem2
//
//  Created by Mandeep Singh on 2017-02-16.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#ifndef myFunctions_h
#define myFunctions_h
#include "GetGlut.h"
#include <GLUT/GLUT.h>


extern bool sine;
extern bool parabolic;
float B0(float u);
float B1(float u);
float B2(float u);
float B3(float u);

void drawCurve();
void drawPoint(float Qx, float Qy, float Qz);
void drawCntrlPoints();
void drawSphereY(int &startTime);
void drawCurve();
void buildTable();
#endif /* myFunctions_h */
