//
//  myFunctions.cpp
//  Problem2
//
//  Created by Mandeep Singh on 2017-02-16.
//  Copyright © 2017 Mandeep Singh. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "myFunctions.h"

using namespace std;

//GLobal Variables
#define MAX_STEPS 100
#define PI 3.14159265358979323846


bool sine = false;
bool parabolic = false;



float ctrlpoints[11][3] = {
    {0.0, 0.0, 0.0}, {1.0, 3.5, 0.0},
    {4.8,  1.8, 0.0}, {6.5, 7.0, 0.0},
    {9.0,  3.5, 0.0},{32.5, 4.8, 0.0},
    {33.2,  2.6, 0.0},{36.8, 7.0, 0.0},
    {37.8,  5.0, 0.0},{41.2, 20.5, 0.0},
    {41.5, 21.5, 0.0}
};
int m = 11;
int seg = 20*(m - 3);
//float ctrlpoints[5][3] = {
//    {-1,5,0},{2,-1,0},{6,8,0}, {8,-6,0},{0,2,0}};

struct QVector{
    float x;
    float y;
    float z;
    float value;
};

vector<QVector> QVectorArr;

//float QVector = {0};
vector <double> H;
vector<double> G;
vector<double> len;
vector <double> U;
//float arcLenth[MAX_STEPS] = {0};

float B0(float u)
{
    return (1 - u)* (1 - u) * (1 - u) / 6;
}

float B1(float u)
{
    return ((3*(u*u*u)) - (6*(u*u)) + 4) / 6;
}

float B2(float u)
{
    return ((-3*(u*u*u)) + (3*(u*u)) + 3*u + 1) / 6;
}

float B3(float u)
{
    return u*u*u / 6;
}




void drawCntrlPoints()
{
    int x,y,z;
    glBegin(GL_POINTS);
    glPointSize(5.0);
    for(int i = 0; i < m; i ++)
    {
        x = ctrlpoints[i][0];
        y = ctrlpoints[i][1];
        z = ctrlpoints[i][2];
        glBegin(GL_POINTS);
        glColor3f(0, 0, 0);
        glVertex3d(x, y, z);
    }
    glEnd();
}


void buildTable()
{
    float Qx, Qy, Qz;
    double tempU = 0.0;
    double tempu = 0.0;
    double tempG = 0.0;
    for (int i = 0; i <= (m - 3)*20; i++)
    {
        U.push_back(tempU);
        int segment = (int)floor(tempU);
        if(segment > 7)
        {
            segment = 7;
        }
        tempu = tempU - segment;
        Qx = B0 (tempu) * ctrlpoints[segment][0]+
        B1 (tempu) * ctrlpoints[segment+1][0] +
        B2 (tempu) * ctrlpoints[segment+2][0] +
        B3 (tempu) * ctrlpoints[segment+3][0];
        
        Qy = B0 (tempu) * ctrlpoints[segment][1] +
        B1 (tempu) * ctrlpoints[segment+1][1] +
        B2 (tempu) * ctrlpoints[segment+2][1] +
        B3 (tempu) * ctrlpoints[segment+3][1];
        
        Qz = B0 (tempu) * ctrlpoints[segment][2] +
        B1 (tempu) * ctrlpoints[segment+1][2] +
        B2 (tempu) * ctrlpoints[segment+2][2] +
        B3 (tempu) * ctrlpoints[segment+3][2];
        // for 3d, Qz = same as above only with z instead of x
        
        QVector temp;
        temp.x = Qx;
        temp.y = Qy;
        temp.z = Qz;
        QVectorArr.push_back(temp);
        
        tempU += 0.05;
        //cout << "i:" << i <<" X:" << QVectorArr[i].x << " Y:" << QVectorArr[i].y << " Z:" << QVectorArr[i].z << endl;
        
        
        
        if( i > 0)
        {
            tempG += sqrt(pow(QVectorArr[i].x - QVectorArr[i-1].x, 2) + pow(QVectorArr[i].y - QVectorArr[i-1].y, 2) + pow(QVectorArr[i].z - QVectorArr[i-1].z, 2));
        }
        //        cout << "i:" << i << " " << tempG << endl;
        G.push_back(tempG);
    }
    for(int i = 0; i < G.size(); i++)
    {
        H.push_back(G[i]/G[G.size()-1]);
        //        cout << H[i] << endl;
    }
    
}


void drawCurve()
{
    
    //    int MAX_STEPS = 100;
    float Qx, Qy, Qz;
    
    for (int i = 0; i < m - 3; i++)
    {
        for (int j = 0; j < MAX_STEPS; j++)
        {
            
            double u = double(j)/double(MAX_STEPS);
            Qx = B0 (u) * ctrlpoints[i][0]+
            B1 (u) * ctrlpoints[i+1][0] +
            B2 (u) * ctrlpoints[i+2][0] +
            B3 (u) * ctrlpoints[i+3][0];
            
            Qy = B0 (u) * ctrlpoints[i][1] +
            B1 (u) * ctrlpoints[i+1][1] +
            B2 (u) * ctrlpoints[i+2][1] +
            B3 (u) * ctrlpoints[i+3][1];
            
            Qz = B0 (u) * ctrlpoints[i][2] +
            B1 (u) * ctrlpoints[i+1][2] +
            B2 (u) * ctrlpoints[i+2][2] +
            B3 (u) * ctrlpoints[i+3][2];
            // for 3d, Qz = same as above only with z instead of x
            
            drawPoint (Qx, Qy, Qz);
            
        }
        
    }
}

void drawSphereY(int &startTime)
{
    double tempU = 0;
    double tempu;
    double Qx,Qy,Qz;
    
    
    double s;
    double t1 = 1.0/6.0;
    double t2 = 5.0/6.0;
    double vo = 1.2;
    double current;
    
    int curr = glutGet(GLUT_ELAPSED_TIME);
    
    if(curr - startTime > 5000.0)
    {
        startTime = (glutGet(GLUT_ELAPSED_TIME));
        curr = (glutGet(GLUT_ELAPSED_TIME));
    }
    current = (curr - startTime)/5000.0;
    if(sine)
    {
               s = (sin((current * PI) - (PI/2)) + 1) / 2;
//
    }
    else if(parabolic)
    {
        if(current >= 0 && current <= t1)
        {
            s = vo * (current * current)/(2 * t1);
//            cout << "s(t1): " << s << endl;
        }
        else if(current > t1 && current <= t2)
        {
            s = (vo * (current/2)) + (vo * (current - t1));
//            cout << "s(t2): " << s << endl;
        }
        else
        {
            s = vo * (t1/2) +
            (vo * (t2 - t1)) +
            (vo - ((vo * (current - t2)/(1-t2))/2)) * (current - t2);
            //            cout << "s(t3): " << s << endl;
        }
    }
    else
    {
        s = current;
    }
    
    for(int i = 0; i <= H.size(); i++)
    {
        if(s < H[i])
        {
//            cout << "H:" << H[i] << endl;
            tempU = U[i-1] + ((s - H[i-1]) / (H[i] - H[i-1])) * (U[i]-U[i-1]);
        }
        else if(s == H[i])
        {
            tempU = U[i];
        }
    }
    int segment = (int)floor(tempU);
    if(segment > 7)
    {
        segment = 7;
    }
    tempu = tempU - segment;
//    cout << tempU << endl;
    
    Qx = B0 (tempu) * ctrlpoints[segment][0]+
    B1 (tempu) * ctrlpoints[segment+1][0] +
    B2 (tempu) * ctrlpoints[segment+2][0] +
    B3 (tempu) * ctrlpoints[segment+3][0];
    
    Qy = B0 (tempu) * ctrlpoints[segment][1] +
    B1 (tempu) * ctrlpoints[segment+1][1] +
    B2 (tempu) * ctrlpoints[segment+2][1] +
    B3 (tempu) * ctrlpoints[segment+3][1];
    
    Qz = B0 (tempu) * ctrlpoints[segment][2] +
    B1 (tempu) * ctrlpoints[segment+1][2] +
    B2 (tempu) * ctrlpoints[segment+2][2] +
    B3 (tempu) * ctrlpoints[segment+3][2];
    
//    cout << " Qx:" << Qx << " " << " Qy:" << Qy << " Qz:" << Qz << endl;
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(Qx, Qy, Qz);
    glutSolidSphere(1, 500, 500);
    glPopMatrix();
    //            glutSwapBuffers();
    
}


void drawPoint(float Qx, float Qy, float Qz)
{
    
    //    std::cout << x << ", " << y << ", " << z <<"\n";
    
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 1);
    glVertex3d(Qx, Qy, Qz);
    glEnd();
}

