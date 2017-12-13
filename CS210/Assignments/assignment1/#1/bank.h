#include <iostream>
using namespace std;



const int MAX = 10;
const int MAXCHAR = 6;
class CAccount
{
	

private: 
	string name;
	float balance;
	char password[MAXCHAR];
	
public:
	//*****setters and getters*****//
	void setName(string);
	string getName() const;
	void setBalance(float);
	float getBalance() const;
	void setPassword(char p[]);
	void getPassword(char pass1[]);
	//*****************************//
	void accessAccount() const;
	void deposit();
	void withdraw();
	void printBalance() const;
	
CAccount();//Constructor
~CAccount();//Destructor
};

void createAccount(CAccount account[], int index1);
void destroyAccount(CAccount account[], int index);
void printMenu();
void printOptions();
char check(int j);

