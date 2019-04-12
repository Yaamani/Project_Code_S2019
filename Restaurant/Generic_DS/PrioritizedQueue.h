#pragma once

#include "PrioritizedNode.h"

template <typename T>
class PrioritizedQueue
{
private :
	
	PrioritizedNode<T>* backPtr;
	PrioritizedNode<T>* frontPtr;

public :
	PrioritizedQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry, float weight = 0);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;	
	~PrioritizedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: PrioritizedQueue()
The constructor of the PrioritizedQueue class.

*/

template <typename T>
PrioritizedQueue<T>::PrioritizedQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PrioritizedQueue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PrioritizedQueue<T>::enqueue(const T& newEntry, float weight)
{
	PrioritizedNode<T>* newNodePtr = new PrioritizedNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true ;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PrioritizedQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	PrioritizedNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// PrioritizedQueue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if PrioritizedQueue is empty
*/
template <typename T>
bool PrioritizedQueue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PrioritizedQueue<T>::~PrioritizedQueue()
{
}
