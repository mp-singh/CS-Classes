//--------------------------------------------------------------------
//
//  Laboratory 11                                         queuelnk.h
//
//  Class declarations for the linked list implementation of the
//  Queue ADT
//
// Modified Mar. 2015 - Alex Clarke
// * Exception specifications removed due to being deprecaated.
//   cf. https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
// * Templated class merged to header only. Separate .cpp required confusing
//   rebuilds in Visual C++ if it the templated .cpp was modified.
//   cf. https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
//--------------------------------------------------------------------

#include <stdexcept>
#include <new>

using namespace std;


template < class DT >        // Forward declaration of the Stack class 
class Queue;

template < class DT >
class QueueNode              // Facilitator class for the Queue class
{
private:

	// Constructor
	QueueNode ( const DT &nodeData, QueueNode *nextPtr );

	// Data members
	DT dataItem;         // Queue data item
	QueueNode *next;     // Pointer to the next element

	friend class Queue<DT>;
};

//--------------------------------------------------------------------

template < class DT >
class Queue
{
public:

	// Constructor
	Queue ( int ignored = 0 );

	// Destructor
	~Queue ();

	// Queue manipulation operations
	void enqueue ( const DT &newData ) ;       // Enqueue data element
	DT dequeue ()   ;                          // Dequeue data element
	void clear ();                            // Clear queue

	// Queue status operations
	bool isEmpty () const;                    // Queue is empty
	bool isFull () const;                     // Queue is full

	// Output the queue structure -- used in testing/debugging
	void showStructure () const;

private:

	// Data members
	QueueNode<DT> *front,   // Pointer to the front node
		*rear;    // Pointer to the rear node
};



//--------------------------------------------------------------------
//
//  Laboratory 11                                formerly queuelnk.cpp
//
//  Class implementations of the linked list Queue ADT
//
//--------------------------------------------------------------------

//--------------------------------------------------------------------

template < class DT >
QueueNode<DT>:: QueueNode( const DT &nodeDataItem,
						  QueueNode<DT> *nextPtr )

// Creates a queue node containing data item nodeDataItem and next
// pointer nextPtr.

	: dataItem(nodeDataItem),
	next(nextPtr)
{}

//--------------------------------------------------------------------

template < class DT >
Queue<DT>:: Queue ( int ignored )

// Creates an empty queue. Parameter is provided for compatability
// with the array implementation and is ignored.

	: front(0),
	rear(0)
{}

//--------------------------------------------------------------------

template < class DT >
Queue<DT>:: ~Queue ()

	// Frees the memory used by a queue.

{
	clear();
}

//--------------------------------------------------------------------

template < class DT >
void Queue<DT>:: enqueue ( const DT &newDataItem )

	// Inserts newElement at the rear of a queue.

{
	QueueNode<DT> *p;   // Pointer to enqueued data item

	//make p a new QueueNode that has newDataItem and link of zero
p = new QueueNode<DT>(newDataItem, 0);
	//If there are no nodes, set the front to be this new node
if(newDataItem == NULL)
{
	p = front;
}
else
{
	p = rear;
}
p = rear;
	//Otherwise, add the new node to the end

	//Reassign the rear to p
}

//--------------------------------------------------------------------

template < class DT >
DT Queue<DT>:: dequeue ()

	// Removes the least recently (front) element from a queue and
	// returns it.
	// If the list was empty, throws a logic error.

{
	QueueNode<DT> *p;   // Pointer to dequeued node
	DT temp;            // Temporarily stores dequeued element

	// Requires that the queue is not empty
	if ( front == 0 )
		throw logic_error("Queue<DT>::dequeue : list is empty");

	temp = front->dataItem;
	p = front;
	front = front->next;
	if ( front == 0 )
		rear = 0;
	delete p;

	return temp;
}

//--------------------------------------------------------------------

template < class DT >
void Queue<DT>:: clear ()

	// Removes all the elements from a queue.

{
	QueueNode<DT> *p,       // Points to successive nodes
		*nextP;   // Stores pointer to next node
	p = front;
	while ( p != 0 )
	{
		nextP = p->next;
		delete p;
		p = nextP;
	}

	front = 0;
	rear  = 0;
}

//--------------------------------------------------------------------

template < class DT >
bool Queue<DT>:: isEmpty () const

	// Returns true if a queue is empty. Otherwise, returns false.

{
	return ( front == 0 );
}

//--------------------------------------------------------------------

template < class DT >
bool Queue<DT>:: isFull () const

// Returns true if a queue is full. Otherwise, returns false.

{
	// This is a somewhat hacked way to test if the list is full.
	// If a node can be successfully allocated than the list is not
	// full.  If the allocation fails it is implied that there is no
	// more free memory therefore the list is full.
	QueueNode<DT> *p;
	DT junk;

	try
	{
		p = new QueueNode<DT>(junk, 0);
	}
	catch ( bad_alloc &e )
	{
		return true;
	}

	delete p;
	return false;
}


//--------------------------------------------------------------------

template < class DT >
void Queue<DT>:: showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
	QueueNode<DT> *p;   // Iterates through the queue

	if ( front == 0 )
		cout << "Empty queue" << endl;
	else
	{
		cout << "front ";
		for ( p = front ; p != 0 ; p = p->next )
			cout << p->dataItem << " ";
		cout << "rear" << endl;
	}
}
