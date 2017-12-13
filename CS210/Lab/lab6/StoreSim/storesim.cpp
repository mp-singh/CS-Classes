//--------------------------------------------------------------------
//
//  file:    storesim.cpp
//
// Modified Mar. 2015 - Alex Clarke
// Changed main's return type from void to int. The only universal
// return type for main in C++ is void.
// https://isocpp.org/wiki/faq/newbie#main-returns-int
//--------------------------------------------------------------------

// Simulates the flow of customers through a line in a store.
// makes use of queues.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "queuelnk.h"

using namespace std;

int main ()
{
	Queue<int> custQ;      // Line (queue) of customers containing the
	//   time that each customer arrived and
	//   joined the line
	int simLength,         // Length of simulation (minutes)
		minute,            // Current minute
		timeArrived,       // Time dequeued customer arrived
		waitTime,          // How long dequeued customer waited
		totalServed = 0,   // Total customers served
		totalWait   = 0,   // Total waiting time
		maxWait     = 0,   // Longest wait
		numArrivals = 0;

	cout << endl
		<< "Enter the length of time to run the simulator : ";
	cin >> simLength;

	for ( minute = 0 ; minute < simLength ; minute++ )
	{
		if ( !custQ.isEmpty() )
		{
			custQ.dequeue();
			timeArrived = minute;
			totalServed++;
			//* Add code here to do the following:
			//* 1) dequeue the first customer and capture its return
			//*    in timeArrived
			//* 2) increment totalServed
			//* 3) calculate the waitTime of the customer 
			//* 4) add the waitTime of the customer to totalWait
			//* 5) update maxWait if this customer waited longer than any 
			//* 	 previous customer. 

		}


		switch ( rand() % 4 )
		{
			// The number generated above will be between 0 and 3
			// If 0 or 3, then no customers will be added, If 2, then 2
			// customers will be added. If 1, then one customer will be added.

		case 0 :
		case 3 : numArrivals = 0; break;
		case 1 : numArrivals = 1; break;
		case 2 : numArrivals = 2;
		}
		for ( int j = 0 ; j < numArrivals ; j++ )
			custQ.enqueue(minute);

	}

	cout << endl;
	cout << "Customers served : " << totalServed << endl;
	cout << "Average wait     : " << setprecision(2)
		<< double(totalWait)/totalServed << endl;
	cout << "Longest wait     : " << maxWait << endl;

	return 0;
}
