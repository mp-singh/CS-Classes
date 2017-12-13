#include <iostream>
#include <string>
#include "bank.h"
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	cout << fixed <<showpoint << setprecision(2);//formatting
	int member = 0;//keep track of elements in the array

	CAccount account[MAX]; //object array
	CAccount::CAccount();//constructor

	char choice1;//choice for Main Menu
	char choice2;//choice for Menu 2
	string name1;
	string pass;
	bool found = false;
	char tempPass[MAXCHAR] = {0};


	cout << "This program simulates a Bank Account. " << endl;
	cout << "Please enter one of the following options." <<endl;
	printMenu();
	cout << "Please make a selection: ";
	choice1 = check(1);


	while(choice1 !='q' || choice1 !='Q')
	{
		switch(choice1)
		{
			case 'c': case 'C'://Create account
			{
				
				createAccount(account, member); 
				member++;
				cout << "Account has been created." <<endl;	
				printMenu();
				cout << "Please make a selection: ";
				choice1 = check(1); //check for valid input
				break;
			}
			


			
			case 'd': case 'D'://Destroy account
			{
				destroyAccount(account, --member); 
				printMenu();
				cout << "Please make a selection: ";
				choice1 = check(1); //check for valid input
				break;
			}

			

			case 'a': case 'A'://accesss account
			{
				cout << endl << "Please enter the name of the account you wish to accesss: "; //ask user for account name
				cin >> name1;
				cout << "Please enter the password for this account: "; //ask for password
				cin >> pass;
				cout << endl; //formatting


				for(int counter=0; counter<MAX; counter++)
				{	
					account[counter].getPassword(tempPass);

					if(pass == tempPass && name1 == account[counter].getName())// check if name and passowrd match
					{
						cout << "Accesss granted." << endl;
						cout << endl;
						found = true;
						break;
					}
				}
				if(found)
				{
					cout << "Please enter one of the following options." << endl;
					printOptions(); //sub menu
					cout << endl;
					cout << "Please make a selection: ";
					choice2=check(2); //check for valid input
					while(found)
					{
						switch(choice2)
						{
							case 'd': case 'D'://Deposit money
							{
								account[counter].deposit();//call deposit function
								printOptions();
								cout <<endl<< "Please make a selection: ";
								choice2=check(2);//check for valid input
								break;
							}
							case 'w': case 'W'://Withdraw money
							{
								account[counter].withdraw(); //call withdraw function
								printOptions();
								cout << endl <<  "Please make a selection: ";
								choice2=check(2);//check for valid input
								break;
							}
							case 'p': case 'P'://Print Balance
							{
								account[counter].printBalance(); //call print balance function
								printOptions();
								cout << endl << "Please make a selection: ";
								choice2=check(2);//check for valid input
								break;
							}
							case 'r': case 'R'://reprint Menu
							{
								printMenu();
								cout << "Please make a selection:";
								choice1 = check(1);//check for valid input
								found = false;//exit the loop
								break;
							}	
						}
					}
				}
			else//do this if incorrect password or username
			{
				cout << "Incorrect account name or password." << endl; 
				printMenu();
				cout << "Please make a selection: ";
				choice1=check(1);//check for valid input
			}
			break;
		}




		case 'q': case 'Q'://Quit Program
		{
			cout << "Thanks for your bussiness and have a good day!" << endl;
			CAccount::~CAccount();//Destructor
			return 0;
		}
	}
}
CAccount::~CAccount();//Destructor
return 0;
}

