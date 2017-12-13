#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include "Map.h"
using namespace std;


//**************** Constructors **********************//
CTile::CTile()
{
	terrainType = 1;
	length=0;
	currentPos=0;

}
CTile::~CTile()
{}


CMap::CMap(){}


CMap::~CMap()
{}

//***************************************************//

//*************** Getters and Setters *************//
void CMap::setTerrainType(int x, int y, int type)
{
	Tiles[x][y].setTerrainType(type);
}

int CMap::getTerrain(int x, int y)
{
	return Tiles[x][y].getTerrainType();
}

void CTile::setTerrainType(int x)
{
	terrainType=x;
}

int CTile::getTerrainType() const
{
	return terrainType;
}

int CTile::getLength() const
{
	return length;
}

//***************************************************//


//********************** inserting *****************//
void CMap::addObject(int x, int y, int a)
{
	Tiles[x][y].insertObjectId(a);
}


void CTile::insertObjectId(int a)
{
	if(a >=0 && a<= 2)
	{
		if(!isFull())
		{
			objectId[length] = a;
			length++;		
		}
		else
			cout << "Cannot add anymore objects. "<< endl;
	}
	else
		cout << "Please enter a valid entry." << endl;
	
}

//***************************************************//

//********************** Removing *******************//

void CMap::removeObject(int x, int y, int a)
{
	Tiles[x][y].removeObjectId(a);
}


// void CTile::removeObjectId(int a)
// {
// 	if(!isEmpty())
// 	{
// 		for(int i=0; i<=getLength(); i++)
// 		{
// 			if(getObjectId(i) == a)
// 			{
// 				for(int j=i+1; j<getLength(); j++)
// 				{	
// 					objectId[i]=objectId[j];
					
// 				}
// 			}	
// 		}
// 		length--;	
// 	}
// 	else
// 		cout << "No Objects in the list." << endl;
// }

void CTile::removeObjectId(int a)
{
	int k=searchObjectId(a);
	if(!isEmpty())
	{
		for(int j=k+1; j<getLength(); j++)
		{
			objectId[k]=objectId[j];
		}
		length--;
	}
}

int CTile::searchObjectId(int a)
{
	for(int i=0; i<=getLength(); i++)
	{
		if(getObjectId(i)==a)
		{
			return i;
		}
	}
	return -1;
}

void CMap::removeAll(int x, int y, int a)
{
	Tiles[x][y].removeAllObjectId(a);
}

void CTile::removeAllObjectId(int a)
{

	if(a == 0)
	{
		int j= getNumOfObjectS();
		for(int i=0; i<j; i++)
		{
			removeObjectId(a);

		}
	}
	else if( a== 1)
	{
		int j= getNumOfObjectM();
		for(int i=0; i<j; i++)
		{
			removeObjectId(a);
		}
	}
	else 
	{
		int j= getNumOfObjectV();
		for(int i=0; i<j; i++)
		{
			removeObjectId(a);
		}
	}
	// for(int i = 0; i < getLength(); i++)
	// {
	// 	objectId[i]= -1;
	// }
}
//***************************************************//


int CTile::getObjectId(int index) //search
{
	return objectId[index];
}


//*************** Getting # of Objects in Lists ***********//

int CTile::getNumOfObjectS() ///soldier
{
	int counter =0;
	
	for(int i = 0; i < getLength(); i++)
	{
		if(getObjectId(i) == 0) 
			counter++;
	}
	return counter;
}
int CTile::getNumOfObjectM()//Monster
{
	int counter =0;
	//run through queue counter++ when objectID == 0
	for(int i = 0; i < getLength(); i++)
	{
		if(getObjectId(i) == 1)
			counter++;
	}
	return counter;
}
int CTile::getNumOfObjectV()// Vehicle
{
	int counter =0;
	for(int i = 0; i < getLength(); i++)
	{
		if(getObjectId(i) == 2)
			counter++;
	}
	return counter;
}

//***************************************************//



//******************8 Checks *********************//
bool CTile::isFull()
{
	return (length == MAXITEMS);
}

bool CTile::isEmpty()
{
	return (length == 0);
}

//***************************************************//

void CMap::printToScreen(int x, int y) //printing to the screen
{
	
	
	cout << "(" << x << ","<< y<< "):" << Tiles[x][y].convertToString() << "; #S = " 
	<< Tiles[x][y].getNumOfObjectS()<< ", "<< " #M = " << Tiles[x][y].getNumOfObjectM() << ", "<<
	" #V = " << Tiles[x][y].getNumOfObjectV() << endl; 


}

void CMap::printToText() //Printing to a text file
{
	ofstream myfile;
	myfile.open("map.txt");
	
	for(int k=0; k<TILESX; k++)
	{
		for (int j = 0; j<TILESY; j++)
		{
			myfile << "(" << k << ", "<< j<< "):" << Tiles[k][j].convertToString() << "; #S = " 
			<< Tiles[k][j].getNumOfObjectS() << ", " << " #M = " << Tiles[k][j].getNumOfObjectM()<<", " <<
			" #V = " << Tiles[k][j].getNumOfObjectV()<<endl; 
		}
	}
	cout << "Map copied to map.txt"<<endl;
	myfile.close();	
}



void printMainMenu() //helper function
{
	cout << endl;
	cout << "**************** Main Menu ***************************"<<endl;
	cout << setw(10) << "Please enter 't' to set the terrain." <<endl;
	cout << setw(10) << "Please enter 'a' to add an object." <<endl;
	cout << setw(10) << "Please enter 'r' to  remove an object." << endl;
	cout << setw(10) << "Please enter 'f' to print to file." << endl;
	cout << setw(10) << "Please enter 'p' to print to screen." <<endl;
	cout << setw(10) << "Please enter 'q' to quit the program." <<endl;
	cout << "******************************************************"<<endl;
	cout << endl;
	cout << "Please make a selection: ";
}
void printRemoveOptions()
{
	cout << endl;
	cout << "**************** Remove Menu ***************************"<<endl;
	cout << setw(10) << "Please enter 's' to remove a Soldier." << endl;
	cout << setw(10) << "Please enter 'm' to remove a Monster." << endl;
	cout << setw(10) << "Please enter 'v' to remove a Vehicle." << endl;
	cout << setw(10) << "Please enter 'a' to remove all Soldier objects." << endl;
	cout << setw(10) << "Please enter 'b' to remove all Monster objects." << endl;
	cout << setw(10) << "Please enter 'c' to remove all Vehicle objects." << endl;
	cout << "******************************************************"<<endl;
	cout << endl;
	cout << "Please make a selection: ";

}

void printAddOptions()
{
	cout << endl;
	cout << "**************** Add Menu ***************************"<<endl;
	cout << setw(10) << "Please enter 's' to add a Soldier." << endl;
	cout << setw(10) << "Please enter 'm' to add a Monster." << endl;
	cout << setw(10) << "Please enter 'v' to add a Vehicle." << endl;
	cout << "******************************************************"<<endl;
	cout << endl;
	cout << "Please make a selection: ";	
}



string CTile::convertToString() //converting integers to strings
{
	if(getTerrainType() == 1)
	{
		return "Land";
	}
	else if(getTerrainType() == 0)
	{
		return "Water";
	}
	else
		return 0;
}

void getCoordinates(int &x, int &y)
{

	cout << "Enter the cordinate x: ";
	cin >> x;
	cout << "Enter the cordinate y: ";
	cin >> y;

}

