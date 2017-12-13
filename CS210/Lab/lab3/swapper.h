
#include <iostream>
using namespace std;

#ifndef SWAPPER_H
#define SWAPPER_H

template<typename T>
class my_class
{
	T x;
	T y;
public:
	my_class(T a, T b);
	void swapper();
	void printem();
};


#endif
#include "swapper.cpp"