#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int TILESX = 4;
const int TILESY = 4;
const int MAXITEMS = 50;




class CTile
{
private:
	//******
	int objectId[MAXITEMS];//check < 0 /\ > 2 error 
	int length;
	int currentPos;
	//***************
	int terrainType;


public:
//List functions//
	int getObjectId(int);
	void insertObjectId(int);
	void removeObjectId(int);
	void getNextId(int);
	void MakeEmpty();
	int getLength() const; 
	bool isFull();
	bool isEmpty();
	void removeAllObjectId(int);

//***********************//
	void setTerrainType(int);
	int getTerrainType() const;
	int getNumOfObjectS();
	int getNumOfObjectM();
	int getNumOfObjectV();
	void addObject(int value);
	string convertToString();
	int searchObjectId(int a);
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
void removeObject(int x, int y, int value);
void setTerrainType(int x, int y, int type);
void printToScreen(int x,int y);
void printToText();
void removeAll(int x, int y, int a);

};

//Helper Functions//
void printMainMenu();
void printRemoveOptions();
void printAddOptions();

void getCoordinates(int&, int&);