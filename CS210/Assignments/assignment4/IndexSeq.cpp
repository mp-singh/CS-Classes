#include <iostream>
#include "IndexSeq.h"

using namespace std;



CIndexedSeq::CIndexedSeq()
{
	currIndex=0;
	currItem=0;
	headItem=0;
	headIndex=0;
}

CIndexedSeq::~CIndexedSeq()
{
	while(headItem !=0)
	{
		currItem = headItem->pNext;
		delete headItem;
		headItem = currItem;
		// cout << "worked" <<endl;
	}
	while(headIndex !=0)
	{
		currIndex = headIndex->pNext;
		delete headIndex;
		headIndex = currIndex;
		// cout << "worked" <<endl;
	}
}

void CIndexedSeq::insertW(string x, int y)
{
	IndexNode *p =  new IndexNode();
	ItemNode *q = new ItemNode();
	p->index =y;
	q->item = x;
	p->pItem = q;
	//both need search
	//inserting new nodes with the index.
	if(headIndex == nullptr)
	{
		headIndex = p;
		p->pNext= nullptr;
		headItem = q;
		q->pNext=nullptr;

	}
	else if(headIndex->index > y)
	{
		p->pNext = headIndex;
		headIndex = p;
		q->pNext = headItem;
		headItem = q;
	}
	else
	{
		currIndex = headIndex;
		currItem = headItem;
		while(currIndex -> pNext != nullptr && currItem ->pNext != nullptr)
		{
			if(currIndex -> pNext -> index > y)
			{
				q-> pNext = currItem -> pNext;
				currItem -> pNext = q;
				p -> pNext = currIndex -> pNext;
				currIndex -> pNext = p;
				return;
			}

			currIndex = currIndex->pNext;
			currItem = currItem -> pNext;
		}
		currIndex -> pNext = p;
		currItem -> pNext = q;
		p->pNext = nullptr;
		q->pNext = nullptr;
	}
}

void CIndexedSeq::insertWO(string x)
{
	

	//check if the difference in index is greater than 2;
	currIndex = headIndex;
	currItem = headItem;
	while(currIndex->pNext != nullptr && currItem ->pNext != nullptr)
	{
		int curr = currIndex->index;
		int next = currIndex -> pNext -> index;
		if(next - curr >= 2)
		{
			insertW(x, curr+1);
			return;
		}
		else if( currIndex ->pNext->pNext == nullptr && currItem->pNext->pNext == nullptr)
		{
			int last = currIndex->pNext->index;
			insertW(x, last+1);
			return;
		}
		currIndex = currIndex->pNext;
		currItem =  currItem->pNext;

	}


}
void CIndexedSeq::printW()
{
	currIndex = headIndex;
	currItem = headItem;
	while(currIndex != nullptr && currItem != nullptr)
	{
		if(currIndex -> pNext != nullptr && currItem->pNext != nullptr)
		{
			cout << "'" << currIndex->pItem->item <<"'" << "(" << currIndex->index << ")" << ", " ;	
			currIndex = currIndex->pNext;
		}
		else
			{	
				cout << "'" << currIndex->pItem->item <<"!'" << "(" << currIndex->index << ")";
				cout << endl;
				return;
			}

	}
	cout << endl;
}
void CIndexedSeq::printWO()
{
	currItem = headItem;
	while(currItem != nullptr)
	{
		if(currItem ->pNext != nullptr)
		{
			cout << "'"<< currItem->item << "', ";
			currItem = currItem->pNext; 
		}
		else
		{
			cout << "'"<< currItem->item << "!'";
			cout << endl;
			return;
		}
		
	}
	cout << endl;
}


// delete the last index in the 
void CIndexedSeq::deleteLast()
{
	if(headIndex != nullptr && currItem != nullptr)
	{
		currIndex = headIndex;
		currItem = headItem;


		while(currIndex->pNext != nullptr && currItem->pNext != nullptr)
		{

			if(currIndex -> pNext -> pNext == nullptr && currItem -> pNext -> pNext == nullptr)
			{
				delete currIndex->pNext;
				delete currItem ->pNext;
				currIndex ->pNext = nullptr;
				currItem -> pNext = nullptr;
				cout << "Last Item deleted." << endl<<endl;
				// cout << "check: " << currIndex->pNext << ", " << currItem -> pNext << endl;
				return;
			} 
			currIndex= currIndex ->pNext;
			currItem=currItem->pNext;
		}
	}

}

