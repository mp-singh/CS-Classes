#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int TILESX = 4;
const int TILESY = 4;
const int MAXITEMS = 50;

class CList
{
private:
	// bool used[maxQueue];
	int objectId[MAXITEMS];//check < 0 /\ > 2 error 
	int length;
	int currentPos;
	

public:
	int getObjectId(int);
	void insertObjectId(int);
	void removeObjectId(int);
	void getNextId(int);
	void MakeEmpty();
	int getLength() const; 
	bool isFull();
	bool isEmpty();
	CList();
	~CList();
};

class CTile
{
private:
	CList Object 
	int terrainType;
	int numOfObject;
public:
	void setTerrainType(int);
	int getTerrainType() const;
	int getNumOfObjectS(CList&) ;
	int getNumOfObjectM(CList&) const;
	int getNumOfObjectV(CList&) const;
	void addObject(int value, CList&);
	
	CTile();
	~CTile();
};


class CMap
{
private:
	CTile Tiles[TILESX][TILESY];

public:
CMap();
~CMap();
int getTerrain(int x, int y);
void addObject(int x, int y, int value);
void removeObjectOne(int x, int y, int value);
void setTerrainType(int x, int y, int type);

};

void printToMap();
void printToScreen();
void printMainMenu();
void printRemoveOptions();
void printAddOptions();




//**************************
#include <iomanip>
#include <iostream>
#include <string>
#include "Map.h"
using namespace std;

void CMap::addObject(int x, int y, int a)
{
	Tiles[x][y].addObject(a);
}



void CMap::setTerrainType(int x, int y, int type)
{
	Tiles[x][y].setTerrainType(type);
}

int CMap::getTerrain(int x, int y)
{
	return Tiles[x][y].getTerrainType();
}

void CTile::addObject(int x)
{
	O.insertObjectId(x);
}


void CList::insertObjectId(int a)
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

int CList::getObjectId(int index)
{
	return objectId[index];
}


int CTile::getNumOfObjectS(CList &p) ///soldier
{
	int counter =0;
	//run through queue counter++ when objectID == 0
	for(int i = 0; i <= p.getLength(); i++)
	{
		if(p.getObjectId(i) == 0) //(&& O.isUsed(i))
			counter++;
	}
	return counter;
}
// int CTile::getNumOfObjectM(queue &O) const///soldier
// {
// 	int counter =0;
// 	//run through queue counter++ when objectID == 0
// 	for(int i = 0; i <= O.getIndexEnd(); i++)
// 	{
// 		if(O.getObjectId(i) == 1 && O.isUsed(i))
// 			counter++;
// 	}
// 	return counter;
// }
// int CTile::getNumOfObjectV(queue &O) const///soldier
// {
// 	int counter =0;
// 	//run through queue counter++ when objectID == 0
// 	for(int i = 0; i <= O.getIndexEnd(); i++)
// 	{
// 		if(O.getObjectId(i) == 2 && O.isUsed(i))
// 			counter++;
// 	}
// 	return counter;
// }



void CTile::setTerrainType(int x)
{
	terrainType=x;
}

int CTile::getTerrainType() const
{
	return terrainType;
}

CTile::CTile()
{
	terrainType = 1;
	numOfObject = 0;

}

CMap::CMap(){}


CMap::~CMap()
{}

CTile::~CTile()
{}

CList::CList()
{
	length=0;
	currentPos=0;
}

CList::~CList(){}

bool CList::isFull()
{
	return (length == MAXITEMS);
}

bool CList::isEmpty()
{
	return (length == 0);
}

int CList::getLength() const
{
	return length;
}


void printMainMenu() //helper function
{
		cout << endl;
		cout << "**************** Main Menu ***************************"<<endl;
		cout << setw(10) << "Please enter 't' to set the terrain." <<endl;
		cout << setw(10) << "Please enter 'a' to add an objects." <<endl;
		cout << setw(10) << "Please enter 'r' to  remove a objects." << endl;
		cout << setw(10) << "Please enter 'f' to print to file." << endl;
		cout << setw(10) << "Please enter 'c' to print to screen." <<endl;
		cout << setw(10) << "Please enter 'q' to quit the program." <<endl;
		cout << "******************************************************"<<endl;
		cout << endl;
}
void printRemoveOptions()
{
	cout << endl;
	cout << "**************** Remove Menu ***************************"<<endl;
	cout << setw(10) << "Please enter 'S' to remove a Soldier." << endl;
	cout << setw(10) << "Please enter 'M' to remove a Monster." << endl;
	cout << setw(10) << "Please enter 'V' to remove a Vehicle." << endl;
	cout << setw(10) << "Please enter 'A' to remove all objects." << endl;
	cout << "******************************************************"<<endl;
	cout << endl;

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
}

