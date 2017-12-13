// FILE:     hello.cpp
// PURPOSE:  An example of a simple I/O stream 

#include <iostream>
using namespace std;

int main()
{
	char name[50];
	cout << "Please enter your name:" << endl;
	
	cin >> name;
	cout << "Hello, " << name << endl;
	return 0;
}