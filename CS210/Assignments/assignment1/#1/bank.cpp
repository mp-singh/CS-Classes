#include <iostream>
#include "bank.h"
#include <iomanip>
using namespace std;





//********* Getter and Setter Functions **************//
string CAccount::getName() const
{
	return name;
}

float CAccount::getBalance() const
{
	return balance;
}

void CAccount::getPassword(char pass1[])
{
	memcpy(pass1, password, MAXCHAR);
}

void CAccount::setName(string n)
{
	name = n;
}

void CAccount::setBalance(float b)
{
	balance = b;
}

void CAccount::setPassword(char p[])
{
	memcpy( password, p, MAXCHAR );
	
}
//*****************************************************//

//********** Constructor and Destructor **************//
CAccount::CAccount() //constructor
{
	
	name = ' ';
	balance = 0.00;
	memset(password, '0', MAXCHAR);
		
}

CAccount::~CAccount() {}//destructor
//*****************************************************//

//******** Function to print balance of an account **********//
void CAccount::printBalance() const 
{
	if(getBalance() < 0.0000001) //correction for $-0.00
	{
		cout << "The current account balance is: $0.00. "<<endl;
	}
	else
		cout << "The current account balance is: $" << getBalance() << endl; 

}

//******** Function to deposit money in an account **********//
void CAccount::deposit()
{
	float tempDeposit = 0;
	int Quotient;
	float newBalance;
	cout << "Please enter the amount you wish to deposit: ";
	cin >> tempDeposit;
	if(tempDeposit >= 1000) //check to see if deposit is greater than 1000.
	{
		Quotient = tempDeposit/ 1000; //find the quotient
		newBalance = getBalance() + tempDeposit + Quotient*5.0; //multiply that quoteient by 5 for bonus
		setBalance(newBalance);//set the balance to newBalance
		cout << "You have successfully deposited $" << tempDeposit << ". "<< endl;
		cout << "You also recieve a bonus of $" << Quotient*5.0 << ". "<< endl; 
	}
	else //if the deposit is less than $1000
	{
		newBalance = getBalance() + tempDeposit;
		setBalance(newBalance);
		cout << "You have successfully deposited $" << newBalance << ". "<< endl;
	}
	
}

//******** Function to withdraw money in an account **********//
void CAccount::withdraw()
{
	float tempWithdraw = 0;
	float newBalance = 0;
	cout << "Please enter the amount you wish to withdraw: ";
	cin >> tempWithdraw;
	if(getBalance() >= tempWithdraw + 1.0)//check if there are sufficent funds in the account
	{
		newBalance = getBalance() - tempWithdraw - 1.0;
		setBalance(newBalance);
		cout << "You have successfully withdrawn $" << tempWithdraw <<endl;
		cout << "with an additional withdrawal fee of $1.00." << endl;
	}
	else if(getBalance() <= tempWithdraw + 1.0)
	{
		cout << "Transaction cancelled due to insifficient funds." << endl;
	}
}


//******** Function to destroy an account **********//
void destroyAccount(CAccount account[], int index)
{
	string destroy;
	string password;
	
	char temp[MAXCHAR];
	
	cout << "Please enter the name of the account you wish to destroy: ";
	cin >> destroy;
	for(int i=0; i<MAX; i++)
	{
		
		if(destroy == account[i].getName())
		{

			cout << "Please enter the password for this account: ";
			cin >> password;
			account[i].getPassword(temp);

			if(password == temp)
			{
				account[i] = account[index];//move the last element to the element you want ot delete.
				//account[i].setName("abc");
				//account[i].setBalance(0);
				cout << "The account has been destroyed." << endl;
				return;
			}	
		}
 
	}
		cout << "Account " << destroy << " not found." << endl;

}

//******** Function to create an account **********//
void createAccount(CAccount account[], int index1)
{	
	string name; 
	char pass[MAXCHAR];
    
	cout <<"Please enter a name you wish your account to have: ";
	cin >> name;
	account[index1].setName(name);
	cout << "Please set a five character password for this account: ";
	cin >> pass;
	account[index1].setPassword(pass);
	
	
}


//******** Function to check  user input **********//
char check(int j)
{
	char c;
	cin >> c;
	if(j==1)
	{
		while(c != 'c' && c != 'a' && c != 'd' && c !='q')
		{
			cout << "Not a valid option.\nPlease enter again: ";
			cin >> c;
		}
		return c;
	}
	else
	{
		while(c != 'd' && c != 'w' && c != 'p' && c != 'r')
		{
			cout << "Not a valid option.\nPlease enter again: ";
			cin >> c;
		}
		return c;
	}

}


//Menu Functions//
void printMenu() 
{ 
		cout << endl;
		cout << "**************** Main Menu ***************************"<<endl;
		cout << setw(10) << "Please enter 'c' to create an account"<< endl;
		cout << setw(10) << "Please enter 'a' to access an account." << endl;
		cout << setw(10) << "Please enter 'd' to destroy an account" << endl;
		cout << setw(10) << "Please enter 'q' to quit the program."<< endl;
		cout << "******************************************************"<<endl;
		cout << endl;

}

void printOptions() 
{
		cout << endl;
		cout << "**************** Sub-Menu ***************************"<<endl;
		cout << setw(10) << "Please enter 'd' to deposit money." <<endl;
		cout << setw(10) << "Please enter 'w' to withdraw money." << endl;
		cout << setw(10) << "Please enter 'p' to print the balance." << endl;
		cout << setw(10) << "Please enter 'r' to return to main menu." <<endl;
		cout << "******************************************************"<<endl;
}