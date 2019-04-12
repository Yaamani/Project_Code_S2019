#pragma once
#include "Node.h"

template <typename T>
class PrioritizedNode :	public Node<T>
{
	//PrioritizedNode<T>* next; // Pointer to next node

	double weight;

public:
	PrioritizedNode();
	PrioritizedNode(const T & r_Item, double weight = 0);
	PrioritizedNode(const T & r_Item, PrioritizedNode<T>* nextNodePtr, double weight = 0);

	void setWeight(double weight);
	double getWeight();

	virtual void setNext(PrioritizedNode<T>* nextNodePtr);
	virtual PrioritizedNode<T>* getNext() const;

	//~PrioritizedNode();
};

template<typename T>
PrioritizedNode<T>::PrioritizedNode():Node<T>()
{
	weight = 0;
}

template<typename T>
PrioritizedNode<T>::PrioritizedNode(const T & r_Item, double weight) : Node<T>(r_Item)
{
	setWeight(weight);
}

template<typename T>
PrioritizedNode<T>::PrioritizedNode(const T & r_Item, PrioritizedNode<T>* nextNodePtr, double weight) : Node<T>(r_Item)
{
	setNext(nextNodePtr);
	setWeight(weight);
}

template<typename T>
void PrioritizedNode<T>::setWeight(double weight)
{
	this->weight = weight;
}

template<typename T>
double PrioritizedNode<T>::getWeight()
{
	return weight;
}

template<typename T>
void PrioritizedNode<T>::setNext(PrioritizedNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
PrioritizedNode<T>* PrioritizedNode<T>::getNext() const
{
	return dynamic_cast<PrioritizedNode*>(next);
}
