/*************************
program: swap two integers
**************************/

#include <iostream>
using namespace std;

template<typename T>
void swapper (T & x, T & y);

template<typename S>
void printem(S &a, S &b);

int main()
{
	int myx=3, myy=4;
	char myx1='a', myy1='b';
	double myx2=5.5, myy2=8.5;

	printem(myx,myy);
	printem(myx1, myy1);
	printem(myx2, myy2);

	return 0;
}

template<typename T>
void swapper (T & x, T & y)
{
		T TempVal = x;
		x = y;
		y = TempVal;
}

template<typename S>
void printem(S &a, S &b)
{
cout << "First Value is: " << a << ". Second Value: " << b << endl;
cout << "AFTER SWAP"<< endl;
swapper(a,b);
cout << "First Value is: " << a << ". Second Value: " << b << endl;
cout << endl;
}
