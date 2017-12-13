//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 1                    timesrch.cpp
//
//  Timing program for a set of searching routines
//
//
//  from "A Laboratory Course in C++ Data Structures" (Roberge,Brandle,Whittington)
//--------------------------------------------------------------------

// Computes the length of time that it takes to execute a given
// searching routine. Searches for numSearches keys in an ordered
// array of numKeys integers.

#include <iostream>
#include <iomanip>
#include <cstdlib>     // For exit()
#include "timer.h"
#include "sort.h"
#include "search.h"
using namespace std;


//--------------------------------------------------------------------
// By default Windows XP has a time resolution of 15.625 milliseconds
// This is called a quantum. To get 3 significant figures in a measured
// result you will need to ensure that you measure times at least
// 100 times longer than the minimum resolution. Tweak numRepetitions
// until you get a minimum time > 1.5s for 1000 keys. On my system
// (numRepetitions == 700) gets me ~ 3.1s at 1000 keys.

//Default timing multiplier
const int numRepetitions = 700;    // Number of times to repeat each 
                                   //   search -- several repetitions
                                   //   may be needed in order to
                                   //   produce a meaningful timing
                                   
//Extra timing multipliers
const int LIN_MULT = 2;            // Some algorithms are much faster
const int BIN_MULT = 18;           // than the others and need an
const int UNK_MULT = 1;            // extra boost to produce a reliable 
                                   // timing number. These have been tuned
                                   // to produce similar times at 1000 keys.

                                   
const int numSearches    = 1000;   // Number of searches to perform
                                   // This provides a variety of 
                                   // search sets to help remove bias
                                   // from results
//--------------------------------------------------------------------

int main ()
{
    Timer searchTimer;            // Timer for searching routine
    int *keyList,                 // Array of integer keys
        numKeys,                  // Number of array entries
        searchSet[numSearches],   // Array of keys to search for
        dummy,                    // Status returned by search
        index,                    // Index returned by search
        j, k;                     // Loop counters
    double timePerSearch;         // Time per search (in seconds)


    // Get the number of keys.
    cout << endl << "Enter the number of keys (must be at least "
         << numSearches << ") : ";
    cin >> numKeys;
    if ( numKeys < numSearches )
    {
       cout << "Number of keys is too small" << endl;
       exit(1);
    }

    // Allocate the array of keys.
    keyList = new int [numKeys];
    if ( keyList == 0 )
    {
       cout << "Cannot allocate enough memory for that many keys"
            << endl;
       exit(1);
    }

    // Initialize the array of keys and the search set.
    for ( j = 0 ; j < numKeys ; j++ )
        keyList[j] =  rand();
    quickSort(keyList,numKeys);

    for ( j = 0 ; j < numSearches ; j++ )
        searchSet[j] = rand();

    // Output header
    //   We're doing science here. Let's set the scientific flag for numerical 
	//   output, and set output precision slightly higher than measurement 
	//   precision
    cout << scientific << setprecision(3);
    cout << endl << endl;
    cout << "    Search    | Number of|  Total Time  |   Time  per  " << endl;
    cout << "     Type     | Searches |     (s)      |   Search(s)  " << endl;
    cout << "--------------|----------|--------------|--------------" << endl;


    // Linear search --
    // Determine how long it takes to search for the keys in
    // searchSet. Repeat the searches numRepetitions times.
    searchTimer.start();
    for ( j = 0 ; j < numRepetitions*LIN_MULT ; j++ )
        for ( k = 0 ; k < numSearches ; k++ )
            dummy = linearSearch(keyList,numKeys,searchSet[k],index);
    searchTimer.stop();

    timePerSearch = searchTimer.getElapsedTime() /
                    ( double(numSearches) * double(numRepetitions*LIN_MULT) );
    //Output sample info for Linear Search
    cout << "linearSearch  |" 
         << setw(10) << (numSearches * numRepetitions * LIN_MULT) << "|"
         << setw(14) << searchTimer.getElapsedTime() << "|" 
         << setw(14) << timePerSearch << endl;


    // Binary search --
    // Determine how long it takes to search for the keys in
    // searchSet. Repeat the searches numRepetitions times.
    searchTimer.start();
    for ( j = 0 ; j < numRepetitions*BIN_MULT ; j++ )
        for ( k = 0 ; k < numSearches ; k++ )
            dummy = binarySearch(keyList,numKeys,searchSet[k],index);
    searchTimer.stop();
    timePerSearch = searchTimer.getElapsedTime() /
                    ( double(numSearches) * double(numRepetitions*BIN_MULT) );
    cout << "binarySearch  |" 
         << setw(10) << (numSearches * numRepetitions * BIN_MULT ) << "|"
         << setw(14) << searchTimer.getElapsedTime() << "|" 
         << setw(14) << timePerSearch << endl;


    // Unknown search --
    // Determine how long it takes to search for the keys in
    // searchSet. Repeat the searches numRepetitions times.
    searchTimer.start();
    for ( j = 0 ; j < numRepetitions*UNK_MULT ; j++ )
        for ( k = 0 ; k < numSearches ; k++ )
            dummy = unknownSearch(keyList,numKeys,searchSet[k],index);
    searchTimer.stop();

    timePerSearch = searchTimer.getElapsedTime() /
                    ( double(numSearches) * double(numRepetitions*UNK_MULT) );
    cout << "unknownSearch |" 
         << setw(10) << (numSearches * numRepetitions*UNK_MULT) << "|"
         << setw(14) << searchTimer.getElapsedTime() << "|" 
         << setw(14) << timePerSearch << endl;

    // Deallocate the array of keys.
    delete [] keyList;

	return 0;
}
