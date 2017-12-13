#include <iostream>
#include <string>
using namespace std;

int CountOnes(string b, int n);
void divByThree(int n);
double Power(double x, int n);
int Factorial(int n);
double SineFunction(double angle, int k);

int main()
{
	double p = 3.14159;//approximated pi
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;


//Programming question 1:
	cout << "This is the first Programming question." <<endl;
	count1 = CountOnes("001000001111",0);
	count2 = CountOnes("000000000000",0);
	count3 = CountOnes("101001010000",0);
	
	cout << "The number of ones contained in '001000001111' are: "<< count1 <<endl;
	cout << "The number of ones contained in '000000000000' are: "<< count2 <<endl;
	cout << "The number of ones contained in '101001010000' are: "<< count3 <<endl;
	cout << endl;

//*********************************************//



cout << "This is the second programming question." << endl;
	cout << "Is 1 divisible of by 3? The answer is: "; 
	divByThree(1);
	cout << "Is 2 divisible of by 3? The answer is: ";
	divByThree(2);
	cout << "Is 3 divisible of by 3? The answer is: ";
	divByThree(3);
	cout << "Is 21 divisible of by 3? The answer is: ";
	divByThree(21);
	cout << "Is 2011 divisible of by 3? The answer is: ";
	divByThree(2011);
	cout << "Is 2199 divisible of by 3? The answer is: ";
	divByThree(2199);
	cout << endl;


cout << "This is the third programing question." <<endl;
	cout << "The result is for -π/6 is: "<<  SineFunction(-p/6,0) <<endl;
	cout << "The result is for 2π/3 is: "<<  SineFunction(2*p/3,0) << endl;
	cout << "The result is for 3π/4 is: "<<  SineFunction(3*p/4,0) <<endl;
	
	return 0;
}


//*********Programming question number 1**********//
int CountOnes(string b, int n)
{
	
	if(n == b.length())
		return 0;
	else 
	{
		if(b[n] == '1')
			return 1+CountOnes(b, n+1);
		else
			return 0 + CountOnes(b, n+1);
	}
}
//*********************************************//

//*********Programming question number 2**********//
void divByThree(int n)
{
	if(n==0)
		cout <<"YES"<<endl;
	
	else if(n == 1)
		cout << "NO" << endl;
	else if (n == 2)
		cout << "NO" << endl;
	else
		divByThree(n-3);
		
	
}

//*********************************************//

//*********Programming question number 3**********//
int Factorial(int n)
{
	if(n==0)
		return 1;
	else
		return n*Factorial(n-1);
}

double Power(double x,int n)
{
	double aHalfPow = 0;
	if(n==0)
		return 1;
	else if(n%2 == 0)
	{
		aHalfPow = Power(x, n/2);
		return aHalfPow*aHalfPow;
	}
	else
	{
		aHalfPow = Power(x, n/2);
		return x * aHalfPow * aHalfPow;
	}
	
}

double SineFunction(double angle, int k)
{
	// cout << "angle:" <<angle << endl;
	if(k == 5)
		return 0;
	else 
	{
		double result = 0;
		double a= Power(angle, 2*k +1);
		 // cout <<"a:"<< a <<endl;
		double b= Factorial(2*k +1 );
		 // cout << "b:" << b << endl;
		double c = Power(-1, k);
		// cout << "c:" << c <<endl;
		result = (c*a)/b+SineFunction(angle, k+1);
		// cout << "Result for k: " << k << " is " << result << endl;
		return result ;
	}
}
//*********************************************//

