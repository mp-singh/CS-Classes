//
//  functions.hpp
//  A2
//
//  Created by Mandeep Singh on 2017-02-03.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//



#include <stdio.h>
#include "ObjLibrary/ObjModel.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>      // std::istringstream

using namespace ObjLibrary;
using namespace std;


struct KeyFrame
{
    int keyFrameNo = 0;
    double attributes[10] = {0} ;
    void init();
    
};

struct OBJ
{
    ObjModel modelNo;
    int objId = 9999;
    string objFileName = "";
    KeyFrame keyFrameTable[100];
    int keyFrameCount = 0;
    void init();
};

void readInputFile(OBJ tempObject[], string filename);
void printFile(OBJ tempObject[]);
void linearInterpolate(OBJ tempObject[]);
void interpolatedResults(OBJ tempObject[], string filename);






