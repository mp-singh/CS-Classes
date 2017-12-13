#include <iostream>
#include "Deck.h"
using namespace std;

int main()
{
	char choice, choice2, choice3;//variables used for different choices made by the user
	CDeck Deck;// Deck object
	CCard a, b, c;//card objects

	

	cout << "This program simulates a deck of cards represented as a stack." << endl;	
	cout << "The deck has been created." << endl;
	cout << "Please eneter one of the following options." << endl;
	printOptions();
	cout << "Please enter a choice: ";
	cin >> choice;

	while(choice !='q' || choice !='Q')
	{
		switch(choice)
		{
			case 'a':
			{
				cout << "Please choose from 'a', 'b', 'c': ";
				cin >> choice2;
				switch(choice2)
				{
					case 'a':
					{
						Deck.Push(a);
						{
							cout << "Variable a was added." << endl;
						}
						
						printOptions();
						cout << "Please make a selection: ";
						cin >> choice;
						break;
					}
					case 'b':
					{
						Deck.Push(b);
						{
							cout << "Variable b was added." << endl;
						}
							
						printOptions();
						cout << "Please make a selection: ";
						cin >> choice;
						break;
					}
					case 'c':
					{
						Deck.Push(c);
						{
							cout << "Variable c was added." << endl;
						}
						

						printOptions();
						cout << "Please make a selection: ";
						cin >> choice;
						break;
					}
					break;
				}
				break;
			}
			case 'r':
			{
				cout << "Please choose the variable 'a', 'b', 'c' to store in: ";
				cin >> choice3;
				switch(choice3)
				{
					case 'a':
					{
						if(Deck.Top(a))
						{
						}
						Deck.Pop();
						{
							cout <<"Top card removed and stored in variable 'a'."<<endl;
							printOptions();
							cout << "Please make a selection: ";
							cin >> choice;
						}
						break;
					}
					case 'b':
					{
						if(Deck.Top(b)){}
						Deck.Pop();
						{
							cout <<"Top card removed and stored in variable 'b'."<<endl;
							printOptions();
							cout << "Please make a selection: ";
							cin >> choice;
						}
						
						break;
					}
					case 'c':
					{
						if(Deck.Top(c)){}
						Deck.Pop();
						{
							cout <<"Top card removed and stored in variable 'c'."<<endl;
							printOptions();
							cout << "Please make a selection: ";
							cin >> choice;
						}
						
						break;
					}
					break;
				}
				break;
			}
			case 'p':
			{	
				Deck.PrintAll();
				printOptions();
				cout << "Please make a selection: ";
				cin >> choice;
				break;
			}
			case 'g':
			{
				Deck.numOfCards();
				printOptions();
				cout << "Please make a selection: ";
				cin >> choice;
				break;
			}
			case 'q':
			{
				cout << "Program ended.";
				return 0;
			}
			case 's':
			{
				Deck.Shuffle();
				printOptions();
				cout << "Please make a selection: ";
				cin >> choice;
				break;
			}
			case 'c':
			{
				Deck.cutDeck();
				printOptions();
				cout << "Please make a selection: ";
				cin >> choice;
				break;
			}
		}

	}
	return 0;

}