#include <iostream>

using namespace	std;



const int MAX=5;
int myPower(int x, int n);
void addIndex();
void printReverse(int x[], int i);
void printForward(int x[], int i);
int main()
{
	//recursive function to print out power
	int myArray[MAX]={1,2,3,4,6};
	int answer = myPower(8,2);
	cout << "The answer is: " << answer << endl;
	
	printReverse(myArray, MAX);
	cout << endl <<endl;
	printForward(myArray, 0);

	return 0;
}


void printForward(int x[], int i)
{
	
	if(i==MAX)
	{
		cout << x[MAX] <<endl;
		return;
	}
	else
	{	printReverse(x,i+1);
		cout << x[i] << endl;
		
	}
	
}
void printReverse(int x[], int i)
{
	
	if(i==0)
	{
		cout << x[0] <<endl;
		return;
	}
	else
	{cout << x[i] << endl;
		printReverse(x,i-1);
		
		
	}
	
}
int myPower(int x, int n)
{
	if(n == 0)
		return 1;
	else{
		return x*myPower(x,n-1);
	}

}

