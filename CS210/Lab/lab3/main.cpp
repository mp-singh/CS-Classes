#include <iostream>
#include "swapper.h"

using namespace std;


int main()
{	

	my_class<int>temp(3, 4);
	temp.printem();
	temp.swapper ();
	cout << "AFTER SWAP" << endl;
	temp.printem();
	return 0;
}


