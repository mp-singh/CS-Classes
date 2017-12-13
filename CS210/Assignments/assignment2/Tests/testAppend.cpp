
#include <iostream>
#include <iomanip>
#include "StackType2.h"
//#include <stack>
using namespace std;

int main()
{
	StackType s;
	int x;
	cout << "enter 5 numbers: ";

	for(int i=0; i< 5; i++)
	{
		cin >> x;
		s.Push(x);
	}
	
	return 0;

}