#pragma once
#include "PrioritizedNode.h"
#include "Queue.h"

template <typename T>
class PriorityQueue :
	public Queue<T>
{
public:
	//PriorityQueue();

	//PrioritizedNode<T>* getFront();
	bool enqueue(const T& newEntry, double weight = 0);
	bool dequeue(T& frntEntry);
	bool dequeue(T& frntEntry, double & weight);

	double * getWeightArray();

	~PriorityQueue();
};

template<typename T>
bool PriorityQueue<T>::enqueue(const T & newEntry, double weight)
{
	PrioritizedNode<T>* newNode = new PrioritizedNode<T>(newEntry, weight);

	if (!newNode) return false;
	
	size++;

	if (!frontPtr) {
		frontPtr = newNode;
		backPtr = newNode;

		return true;
	}

	PrioritizedNode<T>* prevNode = dynamic_cast<PrioritizedNode<T>*>(frontPtr);
	PrioritizedNode<T>* currentNode = prevNode->getNext();

	if (weight > prevNode->getWeight()) {
		newNode->setNext(prevNode);
		frontPtr = newNode;

		return true;
	}

	while (currentNode) {

		if (currentNode->getWeight() < weight) {
			prevNode->setNext(newNode);
			newNode->setNext(currentNode);

			return true;
		}

		prevNode = currentNode;
		currentNode = currentNode->getNext();
	}

	prevNode->setNext(newNode);
	backPtr = newNode;

	return true;
}

template<typename T>
bool PriorityQueue<T>::dequeue(T & frntEntry)
{
	return Queue<T>::dequeue(frntEntry);
}

template<typename T>
bool PriorityQueue<T>::dequeue(T & frntEntry, double & weight)
{
	if (isEmpty())
		return false;

	weight = dynamic_cast<PrioritizedNode<T>*>(frontPtr)->getWeight();
	return Queue<T>::dequeue(frntEntry);
}

template<typename T>
double * PriorityQueue<T>::getWeightArray()
{
	PrioritizedNode<T>* current = dynamic_cast<PrioritizedNode<T>*>(frontPtr);
	double * arr = new double[size];

	for (int i = 0; current; i++) {
		arr[i] = current->getWeight();
		current = current->getNext();
	}

	return arr;
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
	std::cout << "\n\n\n\n CAUTION PRIORITY_QUEUE DISTRUCTED \n\n\n\n";
}


