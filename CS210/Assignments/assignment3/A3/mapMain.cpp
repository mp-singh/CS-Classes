#include <iomanip>
#include <iostream>
#include <string>
#include "Map.h"
#include <fstream>

using namespace std;


int main()
{

	
	CMap map;
	

	int x, y, type;
	char choice;
	cout << "Welcome to a tile-based game." <<endl;
	cout << "All tiles are set to Land by default." <<endl
	<< "Choose one of the following options."<< endl;
	printMainMenu();
	cin >> choice;

	while(choice !='q')
	{
		switch(choice)
		{
			case 't':
			{
				cout << "Please give the coordinates the tile you wish to change the terrain of:" << endl;
				getCoordinates(x,y);
				cout<<"You have entered: (" <<x << "," << y << ")"<<endl;
				cout << "Enter the terrain type ('0' for water or '1' for Land): ";
				cin >> type;
				map.setTerrainType(x,y,type);
				if(type == 0)
				{
					cout << "Terrain set to: Water" <<endl;
				}
				else if(type == 1)
				{

					cout << "Terrain set to: Land" <<endl;
				}
				printMainMenu();
				cin >> choice;
				break;
			}
			case 'a':
			{
				printAddOptions();
				char choice2;
				cin >> choice2;
				switch(choice2)
				{
					case 's':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to place the Soldier." << endl;
						getCoordinates(x,y);
						map.addObject(x,y,0);
						cout << "A Soldier has been added to tile: (" <<x << "," << y << ")"<<endl;
						printMainMenu();
						cin >> choice;

						break;
					}
					case 'm':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to place the Monster." << endl;
						getCoordinates(x,y);
						map.addObject(x,y,1);
						cout << "A Monster has been added to tile: (" <<x << "," << y << ")"<<endl;
						printMainMenu();
						cin >> choice;
						break;
					}
					case 'v':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to place the Vehicle." << endl;
						getCoordinates(x,y);
						map.addObject(x,y,2);
						cout << "A Vehicle has been added to tile: (" <<x << "," << y << ")"<<endl;
						printMainMenu();
						// cout << "Please make a selection: ";
						cin >> choice;
						break;
					}
				}
				break;
			}
			case 'r':
			{
				printRemoveOptions();
				char choice3; 
				cin >> choice3;
				switch(choice3)
				{
					case 's':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to remove the Soldier." << endl;
						getCoordinates(x,y);
						map.removeObject(x,y,0);
						cout << "A Soldier has been removed from tile: (" <<x << "," << y << ")"<<endl;
						printMainMenu();
						cin >> choice;
						break;
					}
					case 'm':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to remove the Monster." << endl;
						getCoordinates(x,y);
						map.removeObject(x,y,1);
						cout << "A Monster has been removed from tile: (" <<x << "," << y << ")"<<endl;
						printMainMenu();
						cin >> choice;
						break;
					}
					case 'v':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to remove the Vehicle." << endl;
						getCoordinates(x,y);
						map.removeObject(x,y,2);
						cout << "A Vehicle has been removed from tile: (" <<x << "," << y << ")"<<endl;
						printMainMenu();
						cin >> choice;
						break;
					}
					case 'a':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to remove all the Objects from." << endl;
						getCoordinates(x,y);
						map.removeAll(x,y,0);
						printMainMenu();
						cin >> choice;
						break;
					}
					case 'b':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to remove all the Objects from." << endl;
						getCoordinates(x,y);
						map.removeAll(x,y,1);
						printMainMenu();
						cin >> choice;
						break;
					}
					case 'c':
					{
						int x,y;
						cout << "Please give the coordinates of where you wish to remove all the Objects from." << endl;
						getCoordinates(x,y);
						map.removeAll(x,y,2);
						printMainMenu();
						cin >> choice;
						break;
					}
				}
				break;
			}
			case 'f':
			{
				map.printToText();
				printMainMenu();
				cin >> choice;
				break;
			}
			case 'p':
			{
				int x,y;
				cout << "Please give the coordinates the tile you wish to print." << endl;
				getCoordinates(x,y);
				map.printToScreen(x,y);
				cout << endl<< ;
				printMainMenu();
				cin >> choice;
				break;
			}
			case 'q':
			{
				cout << "Program terminated" <<endl;
				return 0;
			}
		}
	}
	cout << "Program terminated";
	return 0;
}