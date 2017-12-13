
#include <iostream>
#include "Deck.h"
#include <string>
#include <iomanip>
#ifndef Deck_cpp
#define Deck_cpp
using namespace std;




CCard::CCard()
{
	value = 0;
	suit = " ";
}

CCard::~CCard(){}

CCard::CCard( int x, string y)
{
	value=x;
	suit=y;
}

string CCard::getSuit() const
{
	return suit;
}

int CCard::getValue() const
{
	return value;
}

//

CDeck::CDeck()
{//creating the deck of cards
	//initalizing all the cards
	top = -1;

	for(int i=0; i<4; i++)
	{
		if(i==0)
		{
			for(int j=1; j<14; j++)
			{
				CCard c(j, "Hearts");
				Push(c);
			}
		}
		if(i==1)
		{
			for(int j=1; j<14; j++)
			{
				CCard c(j, "Spades");
				Push(c);
			}
		}
		if(i==2)
		{
			for(int j=1; j<14; j++)
			{
				CCard c(j, "Clubs");
				Push(c);
			}
		}
		if(i==3)
		{
			for(int j=1; j<14; j++)
			{
				CCard c(j, "Diamonds");
				Push(c);
				
			}
		}
	}
	
}

CDeck::~CDeck(){}


//**********StackType ADT functions******//
void CDeck::Push(CCard &x)
{
  //check to see if full
  if(IsFull())
  {
  	cout <<"The Deck is full."<< endl;
    throw IsFull();
  }
  
  top++;
  cards[top]=x;
  
}

void CDeck::Pop()
{

  if (IsEmpty()) throw IsEmpty();
 top--;
}

bool CDeck::Top(CCard &y)
{
  if(IsEmpty())
  {
    return false;
  }

  y=cards[top];
  return true;
}


bool CDeck::IsEmpty() const
{
  return (top == -1);
}

bool CDeck::IsFull() const
{
  return (top ==  MAXCARD-1);
}
//*********************************************//

void CDeck::numOfCards()
{	
	cout << "The number of cards in the Deck currently is: " << top+1 << endl;
}


void CDeck::PrintAll()//print the deck
{

		for(int i=0; i<=top; i++)
		{
			//correcting for "Ace", "Jack", "Queen", "King". 
			if(cards[i].getValue()==1)
			{
				cout << "Ace" << " of " << cards[i].getSuit() << endl;
			}
			else if(cards[i].getValue() == 11)
			{
				cout << "Jack" << " of " << cards[i].getSuit() << endl;		
			}
			else if(cards[i].getValue() == 12)
			{
				cout << "Queen" << " of " << cards[i].getSuit() << endl;
			}
			else if(cards[i].getValue() ==13)
			{
				cout << "King" << " of " << cards[i].getSuit() << endl;
			}
			else//printing the rest of cards
				cout << cards[i].getValue() << " of " << cards[i].getSuit() << endl;
		}
}


void printOptions() //helper function
{
		cout << endl;
		cout << "**************** Menu ***************************"<<endl;
		cout << setw(10) << "Please enter 'a' to add a card to the top of the deck." <<endl;
		cout << setw(10) << "Please enter 'r' to  remove the top card from the deck." << endl;
		cout << setw(10) << "Please enter 'p' to print the remaining deck of cards." << endl;
		cout << setw(10) << "Please enter 'g' to get the number of cards in the deck." <<endl;
		cout << setw(10) << "Please enter 's' to shuffle the deck." <<endl;
		cout << setw(10) << "Please enter 'c' to cut the deck." <<endl;
		cout << setw(10) << "Please enter 'q' to quit the program." <<endl;
		cout << "******************************************************"<<endl;
		cout << endl;
}


void CDeck::cutDeck()
{
	CDeck S, T;
	CCard tempCard;
	srand( time(NULL) );
	int n = rand() % MAXCARD;

	for(int l=0; l<MAXCARD; l++)//empty the cards in the deck
	{
		S.Pop();
		T.Pop();
	}

	for(int i=0; i<n; i++)//Push original deck onto temperary S deck for n number of times
	{
		S.Push(cards[i]);
	}

	for(int k = n; k<MAXCARD; k++)//Push original deck onto temperary T deck for 52-n number of times
	{
		T.Push(cards[k]);
	}
	for(int m=0; m<MAXCARD; m++)
	{
		
		if(S.Top(tempCard))//store the top card in the S deck in a tempcard 
		{					
			S.Pop();//pop the S top card
			T.Push(tempCard);// push tempcard onto T deck
		}
		if(T.Top(tempCard))//store the top card in the S deck in a tempcard
		{
			cards[m]=tempCard;//store the tempcard in the oroginal deck
			T.Pop();//pop the T deck.		
		}
	}
	cout << "The deck has been cut."<< endl;
	
}

void CDeck::Shuffle()//shuffling deck
{
	srand( time(NULL) );

	for (int i = 1; i <= 10; i++)//shuffling
	{
		for (int j = 0; j < MAXCARD; j++)
		{
			int n = rand() % MAXCARD;
			CCard tempCard = cards[j];//store the jth card in a tempcard
			cards[j] = cards[n];//then take the nth card and store it in jth card
			cards[n] = tempCard;//store the tempcard in the nth card
		}
	}
	cout << "The deck has been shuffled." << endl;
}

#endif
