/*************************
program: swap two integers
**************************/

#include <iostream>
using namespace std;

template<typename T>
void swapper (T & x, T & y);

int main()
{
	int myx=3, myy=4;

	cout << "Integers before swapping " << myx << " " << myy << endl;
	swapper (myx, myy);
	cout << "Integers after swapping " << myx << " " << myy << endl;

	return 0;
}

template<typename T>
void swapper (T & x, T & y)
{
		T TempVal = x;
		x = y;
		y = TempVal;
}