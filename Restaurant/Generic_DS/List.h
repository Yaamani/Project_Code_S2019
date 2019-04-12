#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class List { // Linked list

	int size;
	Node<T>* head;

	bool Search(int index, Node<T>*& node, Node<T>*& prevNode) /*const*/;
	//bool Search(int index, Node<T*>*& node, Node<T>*& prevNode, Node<T>*& prevPrevNode) /*const*/;

public:

	List();
	
	//void insertBeg(T item, int index);
	bool insertBeg(const T& item);

	//bool Remove(int index);
	bool Remove(T& item, int index);
	bool Remove(int index);
	bool List<T>::RemoveLast(T & last);

	int getSize();
	Node<T>* GetHead();
	Node<T>** getArray();

	bool isEmpty();

	//void printIds();
	~List();
	
};

template <typename T>
bool List<T>::Search(int index, Node<T> *& node, Node<T>*& prevNode) /*const*/
{
	node = head;
	prevNode = NULL;

	if (head == NULL)
		return false;

	for (int i = 0; node; i++) {
		if (i == index)
			return true;

		prevNode = node;

		node = node->getNext();
	}

	return false;
}

//template <typename T>
//Node<T>* List<T>::Search(int index, Node<T*>*& node, Node<T>*& prevNode, Node<T>*& prevPrevNode) /*const*/
//{
//	Node<T>* currentNode = head;
//	prevNode = NULL;
//	prevPrevNode = NULL;
//
//	if (head == NULL)
//		return NULL;
//
//	while (currentNode) {
//		if (currentNode->getItem() == item)
//			return currentNode;
//
//		prevPrevNode = prevNode;
//
//		prevNode = currentNode;
//
//		currentNode = currentNode->getNext();
//	}
//	return currentNode;
//}

template <typename T>
List<T>::List():head(nullptr) {
	//head = NULL;
	size = 0;
}

template <typename T>
bool List<T>::insertBeg(const T& item) {
	Node<T>* ptrNewNode = new Node<T>(item, head);
	if (!ptrNewNode) return false;

	head = ptrNewNode;
	size++;

	return true;
}

template <typename T>
bool List<T>::Remove(T& item, int index) {
	
	Node<T>* prevNode;
	Node<T>* toBeDeleted; // current
	bool found = Search(index, toBeDeleted, prevNode);

	if (!found)
		//if (prevNode) prevNode->setNext(NULL);
		return false;
	
	item = toBeDeleted->getItem();

	if (prevNode)
		prevNode->setNext(toBeDeleted->getNext());
	else
		head = toBeDeleted->getNext();

	size--;
	delete toBeDeleted;
	//toBeDeleted = NULL;
	return true;
}

template<typename T>
bool List<T>::Remove(int index)
{
	T dummy;
	return Remove(dummy, index);
}

template<typename T>
bool List<T>::RemoveLast(T & last)
{
	/*Node<T>* firstAdded;
	Search(NULL, firstAdded)
	return firstAdded;*/
	
	//if (isEmpty()) return false;

	//Node<T>* prevNode;
	//Node<T>* toBeDeleted;
	//Search(NULL, toBeDeleted, prevNode);

	//if (prevNode) prevNode->setNext(NULL);
	//else head = NULL;

	//size--;

	////T* firstAdded = new T(toBeDeleted->getItem()); 
	//last = toBeDeleted->getItem();
	//delete toBeDeleted;
	////toBeDeleted = NULL;

	//return true;
	return Remove(last, size-1);
}

template<typename T>
int List<T>::getSize()
{
	return size;
}

template<typename T>
Node<T>* List<T>::GetHead()
{
	return head;
}

template<typename T>
Node<T>** List<T>::getArray()
{
	Node<T>* current = head;
	Node<T>** arr = new Node<T>*[size];

	for (int i = 0; current; i++) {
		arr[i] = current;
		current = current->getNext();
	}

	return arr;
}

template<typename T>
bool List<T>::isEmpty() {
	if (head == NULL)
		return true;
	return false;
}

//template<typename T>
//void List<T>::printIds()
//{
//	Node<T>* current = head;
//	while (current)
//	{
//		std::cout << current->getItem()->GetID() << ", ";
//		current = current->getNext();
//	}
//
//	std::cout << "(size = " << size << ")" << std::endl;
//}

template<typename T>
List<T>::~List()
{
	std::cout << "\n\n\n\n CAUTION BAG DISTRUCTED \n\n\n\n";
}
