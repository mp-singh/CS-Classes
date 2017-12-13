#include <iostream>
#include "IndexSeq.h"

using namespace std;

int main()
{



// create an indexed sequence (of string indexed by int)
	CIndexedSeq s;
// insert “incredible” at index 4
	cout << endl;
	s.insertW("incredible", 4);
	cout << "Inserted “incredible” at index 4."<< endl;
// insert “magic” at index 9
	s.insertW("magic", 9);
	cout << "Inserted “magic” at index 9." <<endl;
// insert “I” at index 0
	s.insertW("I", 0);
	cout << "Inserted “I” at index 0." <<endl <<endl;
// print full contents of indexed sequence
	cout << "The full content of the Indexed Sequence: " <<endl;
	s.printW();
	cout << endl;
// delete last item
	s.deleteLast();
// insert “can” (no specified index)
	s.insertWO("can");
	cout << "Inserted “can” with no specified index." << endl;
// insert “you” at index 3
	s.insertW("you", 3);
	cout << "Inserted  “you” at index 3." <<endl;
// insert “show” (no specified index)
	s.insertWO("show");
	cout << "Inserted “show” with no specified index." << endl;
// insert “things!” (no specified index)
	s.insertWO("things!");
	cout << "Inserted “things!” with no specified index."<< endl<<endl;
// print items of indexed sequence
	cout << "The items of the the Indexed Sequence: "<<endl;
	s.printWO();
	cout << endl;
// insert “madness” at index 100
	s.insertW("madness", 100);
	cout << "Inserted “madness” at index 100." << endl <<endl;
// print full contents of indexed sequence
	cout << "The full content of the Indexed Sequence: "<<endl;
	s.printW();
	cout << endl;
// delete last item
	s.deleteLast();
// print items of indexed sequence
	cout << "The items of the Indexed Sequence: " <<endl;
	s.printWO();
	cout << endl;
	cout << "Program terminating." <<endl;


	return 0;
}