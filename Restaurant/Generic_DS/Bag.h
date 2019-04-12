#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class Bag { // Linked list

	int size;
	Node<T>* head;

	Node<T>* Search(const T& item, Node<T>*& prevNode) /*const*/;
	Node<T>* Search(const T& item, Node<T>*& prevNode, Node<T>*& prevPrevNode) /*const*/;

public:

	Bag();
	
	//void AddBeg(T item, int index);
	bool AddBeg(const T& item);

	//bool Remove(int index);
	bool Remove(const T& item);
	bool Bag<T>::RemoveLast(T & last);

	Node<T>* GetHead();

	bool isEmpty();

	void printIds();
	~Bag();
	
};

template <typename T>
Node<T>* Bag<T>::Search(const T& item, Node<T>*& prevNode) /*const*/
{
	Node<T>* currentNode = head;
	prevNode = NULL;

	if (head == NULL)
		return NULL;

	while (currentNode) {
		if (currentNode->getItem() == item) 
			return currentNode;

		prevNode = currentNode;

		currentNode = currentNode->getNext();
	}
	return currentNode;
}

template <typename T>
Node<T>* Bag<T>::Search(const T& item, Node<T>*& prevNode, Node<T>*& prevPrevNode) /*const*/
{
	Node<T>* currentNode = head;
	prevNode = NULL;
	prevPrevNode = NULL;

	if (head == NULL)
		return NULL;

	while (currentNode) {
		if (currentNode->getItem() == item)
			return currentNode;

		prevPrevNode = prevNode;

		prevNode = currentNode;

		currentNode = currentNode->getNext();
	}
	return currentNode;
}

template <typename T>
Bag<T>::Bag():head(nullptr) {
	//head = NULL;
	size = 0;
}

template <typename T>
bool Bag<T>::AddBeg(const T& item) {
	Node<T>* ptrNewNode = new Node<T>(item, head);
	if (!ptrNewNode) return false;

	head = ptrNewNode;
	size++;

	return true;
}

template <typename T>
bool Bag<T>::Remove(const T& item) {
	
	Node<T>* prevNode;
	Node<T>* toBeDeleted = Search(item, prevNode);

	if (!toBeDeleted) {
		//if (prevNode) prevNode->setNext(NULL);
		return false;
	}

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
bool Bag<T>::RemoveLast(T & last)
{
	/*Node<T>* firstAdded;
	Search(NULL, firstAdded)
	return firstAdded;*/
	
	if (isEmpty()) return false;

	Node<T>* prevNode;
	Node<T>* toBeDeleted;
	Search(NULL, toBeDeleted, prevNode);

	if (prevNode) prevNode->setNext(NULL);
	else head = NULL;

	size--;

	//T* firstAdded = new T(toBeDeleted->getItem()); 
	last = toBeDeleted->getItem();
	delete toBeDeleted;
	//toBeDeleted = NULL;

	return true;
}

template<typename T>
Node<T>* Bag<T>::GetHead()
{
	return head;
}

template<typename T>
bool Bag<T>::isEmpty() {
	if (head == NULL)
		return true;
	return false;
}

template<typename T>
void Bag<T>::printIds()
{
	Node<T>* current = head;
	while (current)
	{
		std::cout << current->getItem()->GetID() << ", ";
		current = current->getNext();
	}

	std::cout << std::endl;
}

template<typename T>
Bag<T>::~Bag()
{
	std::cout << "\n\n\n\n CAUTION BAG DISTRUCTED \n\n\n\n";
}
