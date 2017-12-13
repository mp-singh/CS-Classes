//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//
//  from "A Laboratory Course in C++ Data Structures" (Roberge,Brandle,Whittington)
//--------------------------------------------------------------------

template < class DT >
void selectionSort ( DT keyList [], int numKeys )

// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
    DT temp;     // Temporary storage used in swapping
    int minPt,   // Index of the smallest key in the remaining entries
        j, k;    // Loop counters

    for ( j = 0 ; j < numKeys-1 ; j++ )
    {
        minPt = j;
        for ( k = j+1 ; k < numKeys ; k++ )
            if ( keyList[k] < keyList[minPt] )
               minPt = k;
        temp           = keyList[j];
        keyList[j]     = keyList[minPt];
        keyList[minPt] = temp;
    }
}

//--------------------------------------------------------------------

template < class DT >
void quickSort ( DT keyList [], int numKeys )

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList,numKeys,0,numKeys-1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void quickPartition ( DT keyList [], int numKeys,
                      int left, int right         )

// Recursive partner of the quickSort routine. Partitions the array
// entries between left and right into two subarrays. One subarray
// contains the keys that are less than or equal to splitValue, and
// the other contains the keys that are greater than splitValue.
// Recursively sorts each of these subarrays.

{
    DT splitValue,   // "Mid" value to use in splitting
        temp;        // Temporary storage used in swapping
    int splitL,      // Keys in [left..splitL-1] are <= splitValue
        splitR;      // Keys in [splitR+1..right] are > splitValue

    splitValue = keyList[ ( left + right ) / 2 ];

    splitL = left;    // Start at left and move toward right
    splitR = right;   // Start at right and move toward left

    do
    {
        // Go right until key >= splitValue found.
        while ( keyList[splitL] < splitValue ) splitL++;
        // Go left until key <= splitValue found.
        while ( splitValue < keyList[splitR] ) splitR--;

        if ( splitL <= splitR )
        {
            temp            = keyList[splitL];   // Swap keys
            keyList[splitL] = keyList[splitR];   // at limits
            keyList[splitR] = temp;
            splitL++;                            // Continue
            splitR--;                            // partitioning
        }
    }
    while ( splitL <= splitR );

    // Sort each subarray.

    if ( left < splitR )
       quickPartition(keyList,numKeys,left,splitR);
    if ( splitL < right )
       quickPartition(keyList,numKeys,splitL,right);
}

//--------------------------------------------------------------------

template < class DT >
void unknownSort ( DT keyList [], int numKeys )

// Unknown sort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    DT temp;    // Temporary storage used in swapping
    int j, k;   // Loop counters

    for ( j = 0 ; j < numKeys-1 ; j++ )
        for ( k = numKeys-1 ; k > j ; k-- )
            if ( keyList[k-1] > keyList[k] )
            {
               temp         = keyList[k];
               keyList[k]   = keyList[k-1];
               keyList[k-1] = temp;
            }
}
