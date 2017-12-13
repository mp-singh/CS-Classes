//
//  functions.cpp
//  A2
//
//  Created by Mandeep Singh on 2017-02-03.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#include "functions.h"
#include <stdio.h>
#include "GetGlut.h"
#include <GLUT/GLUT.h>
#include "ObjLibrary/ObjModel.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>      // std::istringstream
#include <iomanip>

using namespace ObjLibrary;
using namespace std;



void readInputFile(OBJ tempOBJ[], string filename)
{
    
    //    KeyFrame tempKeyFrame;
    ifstream inFile;
    //    string filename = "test";
    inFile.open(filename);
    if(!inFile)
    {
        cout << "cannot open" << endl;
    }
    
    
    string tempLine = "";
    string tempKeyword;
    istringstream tempReader;
    
    
    //   tempReader.str("");
    //    cout << tempLine << endl;
    //    tempLine.clear();
    
    while (getline(inFile, tempLine))
    {
        //        tempReader.str("");
        istringstream tempReader(tempLine);
        //        cout << tempLine << endl;
        tempReader >> tempKeyword;
        if (tempKeyword == "OBJECT")
        {
            tempReader >> tempKeyword;
            int index = atoi(tempKeyword.c_str());
            tempReader >> tempKeyword;
            tempOBJ[index].objId = index;
            tempReader >> tempKeyword;
            tempOBJ[index].objFileName = tempKeyword;
            //            cout << index << endl;
            //            cout << "objId:" << tempOBJ[index].objId << " tempObject:" << tempOBJ[index].objFileName << endl;
            
            
        }
        else if(tempKeyword == "KEYFRAME")
        {
            tempReader >> tempKeyword;
            
            int index = atoi(tempKeyword.c_str());
            
            for(int j = 0; j < 10; j++)
            {
                tempReader >> tempKeyword;
                float value = atof(tempKeyword.c_str());
                //                    cout << value << endl;
                //                    tempObject[index].keyFrameTable[tempObject[index].keyFrameCount]
                tempOBJ[index].keyFrameTable[tempOBJ[index].keyFrameCount].attributes[j] = value;
                //                        cout << tempObject[index].keyFrameTable[tempObject[index].keyFrameCount].attributes[j] << " ";
                
            }
            tempOBJ[index].keyFrameCount++;
            //                        cout << endl;
            //                        cout << tempOBJ[4].keyFrameCount;
            
        }
    }
}

void printFile(OBJ tempObject[])
{
    //    cout <<"hello: " <<tempObject[1].objFileName;
    for(int i = 0; i < 10; i++)
    {
        if(tempObject[i].objId != 9999)
        {
            cout << "OBJECT ID: " << tempObject[i].objId << " File Name: " << tempObject[i].objFileName ;
            cout << endl;
            cout << tempObject[i].keyFrameCount << endl;
            for(int j = 0; j < tempObject[i].keyFrameCount; j++)
            {
                cout << "KEYFRAME ";
                for(int k = 0; k < 10; k++)
                {
                    cout << tempObject[i].keyFrameTable[j].attributes[k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    
}

void linearInterpolate(OBJ tempObject[])
{
    double x,y,z, rx, ry ,rz, sx, sy, sz;
    double u = 0;
    ofstream outfile;
    outfile.open("Output.txt");
    
    if(!outfile)
    {
        cout << "hello cannot read Output" << endl;
    }
    
    for(int i = 0; i <= 10; i++)
    {
        if(tempObject[i].objId != 9999)
        {
            outfile << "OBJECT " << tempObject[i].objId <<" " << tempObject[i].objFileName ;
            outfile << endl;
        }
    }
    outfile << endl;
    //    cout << "tempObj: " << tempObject[1].objFileName;
    for(int j = 0; j < 10; j++)
    {
        int count = -1;
        int m = tempObject[j].keyFrameCount;
        for (int i = 0; i < m - 1; i++)  // m – 1 is correct because of “<”
        {
            //            cout << "tempObj: " << tempObject[4].objFileName << endl;
            double Px[m];
            double Py[m];
            double Pz[m];
            double Prx[m];
            double Pry[m];
            double Prz[m];
            double Psx[m], Psy[m], Psz[m];
            double frameNo[m];
            //            int count = 0;
            frameNo[i] = tempObject[j].keyFrameTable[i].attributes[0];
            frameNo[i+1] = tempObject[j].keyFrameTable[i+1].attributes[0];
            
            if(frameNo[i] > frameNo[i+1])
            {
                frameNo[i+1] = frameNo[i];
            }
            
            
            Px[i] = tempObject[j].keyFrameTable[i].attributes[1];
            Px[i+1] = tempObject[j].keyFrameTable[i+1].attributes[1];
            
            Py[i] = tempObject[j].keyFrameTable[i].attributes[2];
            Py[i+1] = tempObject[j].keyFrameTable[i+1].attributes[2];
            
            Pz[i] = tempObject[j].keyFrameTable[i].attributes[3];
            Pz[i+1] = tempObject[j].keyFrameTable[i+1].attributes[3];
            
            Prx[i] = tempObject[j].keyFrameTable[i].attributes[4];
            Prx[i+1] = tempObject[j].keyFrameTable[i+1].attributes[4];
            
            Pry[i] = tempObject[j].keyFrameTable[i].attributes[5];
            Pry[i+1] = tempObject[j].keyFrameTable[i+1].attributes[5];
            
            Prz[i] = tempObject[j].keyFrameTable[i].attributes[6];
            Prz[i+1] = tempObject[j].keyFrameTable[i+1].attributes[6];
            
            Psx[i] = tempObject[j].keyFrameTable[i].attributes[7];
            Psx[i+1] = tempObject[j].keyFrameTable[i+1].attributes[7];
            
            Psy[i] = tempObject[j].keyFrameTable[i].attributes[8];
            Psy[i+1] = tempObject[j].keyFrameTable[i+1].attributes[8];
            
            Psz[i] = tempObject[j].keyFrameTable[i].attributes[9];
            Psz[i+1] = tempObject[j].keyFrameTable[i+1].attributes[9];
            for (int k = 0; k < frameNo[i+1] - frameNo[i]; k++)
            {
                u = k/(frameNo[i+1] - frameNo[i]);        // u is a fraction between 0 and 1
                
                x = Px[i] + u * (Px[i+1] - Px[i]);
                y = Py[i] + u * (Py[i+1] - Py[i]);
                z = Pz[i] + u * (Pz[i+1] - Pz[i]);
                rx = Prx[i] + u * (Prx[i+1] - Prx[i]);
                ry = Pry[i] + u * (Pry[i+1] - Pry[i]);
                rz = Prz[i] + u * (Prz[i+1] - Prz[i]);
                sx = Psx[i] + u * (Psx[i+1] - Psx[i]);
                sy = Psy[i] + u * (Psy[i+1] - Psy[i]);
                sz = Psz[i] + u * (Psz[i+1] - Psz[i]);
                
                //
                count ++;
                outfile  << "KEYFRAME  " << tempObject[j].objId << "  " << count << "  "  << setprecision(3)<<x << "  " << setprecision(3)<< y << "  " <<  setprecision(3)<< z << "  " << setprecision(3) << rx << "  " << setprecision(3) << ry << "  " << setprecision(3) << rz << "  " << setprecision(3)<< sx << "  " << setprecision(3) << "  " << setprecision(3) << sy << setprecision(3) << "  " << sz << endl;
            }
        }
        outfile << endl;
    }
}

void interpolatedResults(OBJ tempOBJ[], string filename)
{
    readInputFile(tempOBJ, filename);
    //    printFile(tempOBJ);
}

void drawPoint(OBJ tempOBJ[])
{
    for(int i = 0; i < 10; i++)
    {
        if(tempOBJ[i].objId != 9999)
        {
            for(int j = 0; j < tempOBJ[i].keyFrameCount; j++)
            {
                for(int k = 0; k < 10; k++)
                {
                    glPushMatrix();
//                    glTranslated(particlePos.x, particlePos.y, 0.0);
                    glScalef(tempOBJ[i].keyFrameTable[j].attributes[8], tempOBJ[i].keyFrameTable[j].attributes[9], tempOBJ[i].keyFrameTable[j].attributes[10]); //Scaling object
                    glRotatef(0, tempOBJ[i].keyFrameTable[j].attributes[5], tempOBJ[i].keyFrameTable[j].attributes[6], tempOBJ[i].keyFrameTable[j].attributes[7]);
                    glBegin(GL_LINES);
                    glVertex3d(tempOBJ[i].keyFrameTable[j].attributes[1], tempOBJ[i].keyFrameTable[j].attributes[2], tempOBJ[i].keyFrameTable[j].attributes[3]);
                    glPopMatrix();
                }
            }
        }
    }
}
