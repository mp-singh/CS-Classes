#include <iostream>
using namespace std;




struct ItemNode
{
	string item;
	ItemNode *pNext;
};

struct IndexNode
{
	int index;
	ItemNode *pItem;
	IndexNode *pNext; 
};

class CIndexedSeq
{
private:

	 IndexNode *currIndex, *headIndex;
	 ItemNode *currItem, *headItem;
public:
	void insertW(string x, int y);//insert with a specified index
	void insertWO(string x);//insert without a specified index
	void printW();//print with the specified index
	void printWO();//print without the specified index
	void deleteLast();//delete the last item of the sequence 
	CIndexedSeq();
	~CIndexedSeq();

};

