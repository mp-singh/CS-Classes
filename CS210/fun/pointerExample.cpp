#include <iostream>
using namespace std;


void ex1();
void ex2();
void ex3();
void ex4();

int main()
{
	ex2();

	return 0;
}



void ex1()
{



	int i = 10;
int *p1 = &i;
int *p2;
p2 = &i;
cout << &p1 << endl; // output?
cout << p1 << endl; // output?
cout << *p1 << endl; // output?
*p1 = *p1 + 1;
cout << *p1 << endl; // output?
}

void ex2()
{
	char ch1 = 'a', ch2 = 'b';
char ch3[5] = { 'c', 'd', 'e', 'f', '\0' };
char *pch[3];
pch[0] = &ch1;
pch[1] = &ch2;
pch[2] = ch3; // point to start of array ch3
cout << *pch[0] << endl; // output?
cout << *pch[1]<< endl; // output?
cout << *pch[2]<< endl; // output?
cout << pch[2]<< endl; // output?
cout << *( pch[2] + 1 )<< endl; // output?
}

void ex3()
{
	int i;
int *p1;
p1 = new int; // allocate memory for p1
*p1 = 10;
*p1 = 2 + *p1;
cout << *p1<< endl; // output?
delete p1; // must do this to prevent a memory leak
p1 = new int[3];
*( p1 + 0 ) = 2;
*( p1 + 1 ) = 4;
p1[2] = 6;
for( i = 0; i < 3; i++ )
cout << p1[i]<< endl; // output?
for( i = 0; i < 3; i++)
cout << *( p1 + i )<< endl; // output?
p1 = new int; // memory leak, forgot to delete int[3]
delete p1;
cout << *p1<< endl; // output?
}

void ex4()
{
		int a;
	int b=10;
	float c=5.8;
	
	cout << "the address of a is: " << &a << endl;
	cout << "the address of a is: " << &b << endl;
	cout << "the address of a is: " << &c << endl;

	int *p1;
	p1 = &a;

	int *p2 = &b;
	float *p3 = &c;

	cout << "Value of p1: " << &a << endl;
	cout << "Value of p2: " << &b << endl;
	cout << "Value of p3: " << &c << endl;
	


}