#include<iostream>
using namespace std;



void deckarray();


	const int SUIT=4;
	 const int VALUE =13;
string card[SUIT][VALUE];
int main()
{
	 //biuldDeck();

	 cout << endl;

	 deckarray();




return 0;
}



void deckarray()
{

for(int i=0; i<3; i++)
  {
  	for(int j=0; j<12; j++)
  	{	
  		if(j==0)
  		{
  			card[i][j]="1 of Heart";
  		}
  		else if(j==1)
  		{
  			card[i][j]="2 of Heart";
  		}
  		else if(j==2)
  		{
  			card[i][j]="3 of Heart";
  		}
  		else if(j==3)
  		{
  			card[i][j]="4 of Heart";
  		}
  		else if(j==4)
  		{
  			card[i][j]="5 of Heart";
  		}
  		else if(j==5)
  		{
  			card[i][j]="6 of Heart";
  		}
  		else if(j==6)
  		{
  			card[i][j]="7 of Heart";
  		}
  		else if(j==7)
  		{
  			card[i][j]="8 of Heart";
  		}
  		else if(j==8)
  		{
  			card[i][j]="9 of Heart";
  		}
  		else if(j==10)
  		{
  			card[i][j]="Jack of Heart";
  		}
  		else if(j==11)
  		{
  			card[i][j]="Queen of Heart";
  		}
  		else
  		{
  			card[i][j]="King of Heart";
  		}
  		
      cout << card[i][j] << endl;
  	}
  }

 
}


