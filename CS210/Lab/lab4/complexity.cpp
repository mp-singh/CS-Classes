//
// Author:  Qiang Hu
// Purpose: This program demonstrates the running time measurement and 
//          complexity measurement of a simple nested while loop.
// Date:    January 2000
//
// Revised by: S. Goodwin (August 2000)
// Revised by: Nova Scheidt (September 29, 2003)
#include <iostream>
using namespace std;
#include "timer.h"

int main()
{
	Timer myTimer; 
	int i, j, n, count;
	n = 5000; // should be enough to keep your machine busy.
        count = 0;  // counts the number of times we go through the loops
	double timeused;

	// before entering the nested for loop
	cout << "The value of n is " << n << endl;

	// Turn on the timing function
	myTimer.start();

	// Entering the loop
	for(i = 0; i < n; i++)
	  for (j = 0; j < n; j++)
	    {
	      count++; // increment count by 1 everytime the loops are entered
            }
	
	// Turn off the timer and get the elapsed time
	myTimer.stop();
	timeused = myTimer.getElapsedTime();

	cout  << endl << "The number of times through the loops was  " ;
	cout << count << endl;
        cout << "The value of n squared is " << n*n << endl;
	cout << "Therefore, we can see that the time complexity of executing"<<endl;
	cout <<"the nested loop is order n squared" << endl;
	cout << endl << "The actually amount of time used was "; 
 	cout << timeused << " seconds." << endl;

	return 0;

}
