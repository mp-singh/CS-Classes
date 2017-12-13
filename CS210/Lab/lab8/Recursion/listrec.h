//--------------------------------------------------------------------
//
//  Laboratory 8                                          listrec.h
//
//  Class declarations for a partial linked list implementation of
//  the List ADT with additional recursive linked list functions
//
//--------------------------------------------------------------------
using namespace std;

template < class DT >         // Forward declaration of the List class
class List;

template < class DT >
class ListNode                // Facilitator class for the List class
{
private:

	// Constructor
	ListNode ( const DT &initData, ListNode *nextPtr );

	// Data members
	DT dataItem;		// List data item
	ListNode *next;		// Pointer to the next list node

	friend class List<DT>;
};

//--------------------------------------------------------------------

template < class DT >
class List
{
public:

	// Constructor
	List ();

	// Destructor
	~List ();

	// List manipulation functions
	void insert ( const DT &newData );         // Insert after cursor
	void clear ();                             // Clear list

	// Output the list structure -- used in testing/debugging
	void showStructure () const;

	// functions for getting recursive things going
	void write () const;                       // Output list data items
	void insertEnd ( const DT &newData );      // Insert at end
	void aBeforeb ();                          // In-lab Exercise 3



private:

	// Recursive partners of the Prelab functions
	void writeSub ( ListNode<DT> *p ) const;
	void insertEndSub ( ListNode<DT> *&p, const DT &newElement );

	// Recursive partners of the In-lab functions
	void aBeforebSub ( ListNode<DT> *&p );        // In-lab Exercise 3

private:

	// Data members
	ListNode<DT> *head;     // Pointer to the beginning of the list
	ListNode<DT> *cursor;   // Cursor pointer
};


//--------------------------------------------------------------------
//
//  Laboratory 8                                        listrec.cpp
//
//  SOLUTION: Partial linked list implementation of the List ADT
//            with additional recursive linked list functions
//
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//
// Uses parts of the singly linked list implementation 
// (from Laboratory 6):
//
//   - The ListNode class constructor
//
//   - The List class constructor, destructor, insert(), clear(), and
//     showstructure() functions.
//
//--------------------------------------------------------------------

template < class DT >
ListNode<DT>:: ListNode ( const DT &nodeDataItem, ListNode<DT> *nextPtr )

// Creates a list node containing item elem and next pointer
// nextPtr.

: dataItem(nodeDataItem),
next(nextPtr)
{}

//--------------------------------------------------------------------

template < class DT >
List <DT> :: List ()
// Creates an empty list. The argument is included for compatibility
// with the array implementation and is ignored.

: head(0),
cursor(0)
{}

//--------------------------------------------------------------------

template < class DT >
List<DT>:: ~List ()

	// Frees the memory used by a list.

{
	clear ();
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: insert ( const DT &newDataItem )

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data item in the
// list. In either case, moves the cursor to newDataItem.

{
	if ( head == 0 )             // Empty list
	{
		head = new ListNode<DT>(newDataItem,0);
		cursor = head;
	}
	else                         // After cursor
	{
		cursor->next = new ListNode<DT>(newDataItem,cursor->next);
		cursor = cursor->next;
	}
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: clear ()

// Removes all the data items from a list.

{
	ListNode<DT> *p,      // Points to successive nodes
		*nextP;  // Points to next node
		p = head;
		while ( p != 0 )
		{
			nextP = p->next;
			delete p;
			p = nextP;
		}

		head = 0;
		cursor = 0;
	}

//--------------------------------------------------------------------

template < class DT >
	void List<DT>:: showStructure () const

// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

	{
	ListNode<DT> *p;   // Iterates through the list

	if ( head == 0 )
		cout << "Empty list" << endl;
	else
	{
		for ( p = head ; p != 0 ; p = p->next )
			if ( p == cursor )
				cout << "[" << p->dataItem << "] ";
			else
				cout << p->dataItem << " ";
			cout << endl;
		}
	}

//--------------------------------------------------------------------
//
// Recursively implemented linked list functions used in the Prelab
// Exercise
//
//--------------------------------------------------------------------

template < class DT >
	void List<DT>:: write () const

// Outputs the data items in a list from beginning to end. Assumes that
// objects of type DT can be output to the cout stream.

	{
		cout << "List : ";
		writeSub(head);
		cout << endl;
	}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
	void List<DT>:: writeSub ( ListNode<DT> *p ) const
	{

// Recursive partner of the write() function. Processes the sublist
// that begins with the node pointed to by p.


		if ( p != 0)
		{
		   // Output data item
			writeSub(p->next);    // Continue with next node
			cout << p->dataItem;
		}
	}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: insertEnd ( const DT &newDataItem )

// Inserts newDataItem at the end of a list. Moves the cursor to
// newDataItem.

{
	insertEndSub(head,newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: insertEndSub ( ListNode<DT> *&p,
	const DT &newDataItem )

// Recursive partner of the insertEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
	if ( p != 0 )
		insertEndSub(p->next,newDataItem);    // Continue searching for
	else                                     // end of list
	{
		p = new ListNode<DT>(newDataItem,0);  // Insert new node
		cursor = p;                           // Move cursor
	}
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: aBeforeb ()

// Inserts an data item containing 'a' before each data item
// containing 'b'.
//The sole purpose of this function is to call aBeforebSub and
//send the head as an argument.
//ie. only one line of code is necessary here.

{
	
	aBeforebSub(head); 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>::aBeforebSub ( ListNode<DT> *&p )

// Recursive partner of the aBeforeb() function. Processes the sublist
// that begins with the node pointed to by p.

{
	//add code here to complete the function


	if(p != NULL)
	{
		aBeforebSub(p->next);
		if (p->dataItem == 'b')
		{
			p = new ListNode<DT>('a', p);
		}
	}
	
	//if p not null
	//go through the nodes till you reach the end
	// on the way back, if you find a b,
	//insert a new node 'a' at p->next 



}



		
	

