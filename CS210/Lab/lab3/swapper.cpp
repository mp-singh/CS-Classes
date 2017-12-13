
#include "swapper.h"
#include <iostream>
using namespace std;

#ifndef swapper_cpp
#define swapper_cpp

template<typename T1>
my_class<T1>::my_class(T1 a, T1 b)
{
	x = a;
	y = b;
}

template<typename T1>
void my_class<T1>::swapper()
{
	T1 TempVal = x;
	x = y;
	y = TempVal;
} 

template<typename T1>
void my_class<T1>::printem()
{	
	cout << "First value is: " << x << " Second value is: " << y << endl;
}
#endif