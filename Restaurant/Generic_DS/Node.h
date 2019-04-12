
#ifndef __NODE_H_
#define __NODE_H_

template <typename T>
class Node
{
private :
	T item; // A data item
	//float weight;

protected:
	Node<T>* next; // Pointer to next node

public :
	Node();
	Node(const T & r_Item);	//passing by const ref.
	Node(const T & r_Item, Node<T>* nextNodePtr);

	void setItem( const T & r_Item);
	virtual void setNext(Node<T>* nextNodePtr);
	
	T getItem() const ;
	virtual Node<T>* getNext() const ;
}; // end Node


template < typename T>
Node<T>::Node() 
{
	next = nullptr;
	//cout << "NODE0" << endl;
} 

template < typename T>
Node<T>::Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	//cout << "NODE1" << endl;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	//cout << "NODE2" << endl;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
} 

#endif