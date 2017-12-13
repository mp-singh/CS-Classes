//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 2                    timesort.cpp
//
//  Timing program for a set of sorting routines
//
//--------------------------------------------------------------------

// Computes the length of time that it takes to execute a given
// sorting routine on an array containing numKeys integers.

#include <iostream>
#include <iomanip>
#include <cstdlib>     // For exit()
#include "timer.h"
#include "sort.h"
using namespace std;

//--------------------------------------------------------------------
// By default Windows XP has a time resolution of about 16 milliseconds
// This is called a quantum. To get 3 significant figures in a measured
// result you will need to ensure that you measure times at least
// 100 times longer than the minimum resolution. Tweak numRepetitions
// until you get a minimum time > 1.6s for 1000 keys.

//Default timing multiplier
const int numRepetitions = 100;    // Number of times to repeat each 
                                   //   search -- several repetitions
                                   //   may be needed in order to
                                   //   produce a meaningful timing
                                   
//Extra timing multipliers
const int SEL_SORT = 17;            // Some algorithms are much faster
const int QCK_SORT = 140;           // than the others and need an
const int UNK_SORT = 5;             // extra boost to produce a reliable 
                                    // timing number. These have been tuned
                                    // to produce similar times at 1000 keys.
                                   
//--------------------------------------------------------------------

//--------------------------------------------------------------------

int main ()
{
    Timer copyTimer,      // Timer for array copy
          sortTimer;      // Timer for sorting routine

    int *masterKeyList,   // Master array of integer keys
        *keyList,         // Array of integer keys to be sorted
        numKeys,          // Number of array entries
        j, k;             // Loop counters

    double timeForCopy,   // Time to copy array numRepetitions times
           timePerSort;   // Time to sort array once

    // Get the number of keys.

    cout << endl << "Enter the number of keys : ";
    cin >> numKeys;

    // Allocate both arrays of keys.

    masterKeyList = new int [numKeys];
    keyList       = new int [numKeys];
    if ( masterKeyList == 0  ||  keyList == 0 )
    {
       cout << "Cannot allocate enough memory for that many keys"
            << endl;
       exit(1);
    }

    // Initialize the master array of keys.

    for ( j = 0 ; j < numKeys ; j++ )
        masterKeyList[j] = rand();

    // Compute the time it takes to create numRepetitions copies of
    // masterKeyList.

    copyTimer.start();
    for ( j = 0 ; j < numRepetitions ; j++ )
        for ( k = 0 ; k < numKeys ; k++ )
            keyList[k] = masterKeyList[k];
    copyTimer.stop();
    timeForCopy = copyTimer.getElapsedTime();

    // Output header
    //We're doing science here. Let's set the scientific flag for numerical output
    //And set output precision slightly higher than measurement precision
    cout << scientific << setprecision(3);
    cout << endl << endl;
    cout << "     Sort     | Number of |  Total Time  |   Time  per  " << endl;
    cout << "     Type     |   Sorts   |     (s)      |    Sort(s)   " << endl;
    cout << "--------------|-----------|--------------|--------------" << endl;


    // Selection sort --
    // Time numRepetitions calls to the selectionSort routine.
    sortTimer.start();
    for ( j = 0 ; j < numRepetitions*SEL_SORT ; j++ )
    {
        for ( k = 0 ; k < numKeys ; k++ )    // Copy keys
            keyList[k] = masterKeyList[k];
        selectionSort(keyList,numKeys);      // Sort key list
    }
    sortTimer.stop();

    timePerSort =
           ( sortTimer.getElapsedTime() - timeForCopy ) / double(numRepetitions*SEL_SORT);

    //Output sample info for Selection sort
    cout << "Selection sort|" 
         << setw(11) << (numRepetitions * SEL_SORT) << "|"
         << setw(14) << sortTimer.getElapsedTime() << "|" 
         << setw(14) << timePerSort << endl;


    // QuickSort --
    // Time numRepetitions calls to the quickSort routine.
    sortTimer.start();
    for ( j = 0 ; j < numRepetitions*QCK_SORT ; j++ )
    {
        for ( k = 0 ; k < numKeys ; k++ )    // Copy keys
            keyList[k] = masterKeyList[k];
        quickSort(keyList,numKeys);          // Sort key list
    }
    sortTimer.stop();

    timePerSort =
           ( sortTimer.getElapsedTime() - timeForCopy ) / double(numRepetitions*QCK_SORT);

    //Output sample info for QuickSort
    cout << "QuickSort     |" 
         << setw(11) << (numRepetitions * QCK_SORT) << "|"
         << setw(14) << sortTimer.getElapsedTime() << "|" 
         << setw(14) << timePerSort << endl;



    // Unknown sort --
    // Time numRepetitions calls to the unknownSort routine.
    sortTimer.start();
    for ( j = 0 ; j < numRepetitions*UNK_SORT ; j++ )
    {
        for ( k = 0 ; k < numKeys ; k++ )    // Copy keys
            keyList[k] = masterKeyList[k];
        unknownSort(keyList,numKeys);        // Sort key list
    }
    sortTimer.stop();

    timePerSort =
           ( sortTimer.getElapsedTime() - timeForCopy ) / double(numRepetitions*UNK_SORT);

    //Output sample info for Unknown Sort
    cout << "unknown sort  |" 
         << setw(11) << (numRepetitions * UNK_SORT) << "|"
         << setw(14) << sortTimer.getElapsedTime() << "|" 
         << setw(14) << timePerSort << endl;
		 
	return 0;
}
