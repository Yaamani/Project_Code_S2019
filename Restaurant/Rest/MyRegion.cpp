#include "MyRegion.h"
#include "Order.h"
#include "Motorcycle.h"
//#include "Restaurant.h"
#include "..\Rest\Restaurant.h"


MyRegion::MyRegion(REGION regionType):regionType(regionType), rushHour(false)
{
	
}

void MyRegion::AddToNormal(Order * order)
{
	normal.insertBeg(order);
}

void MyRegion::enqueueToFrozen_VIP(Order * order, double weight)
{
	frozen_VIP.enqueue(order, weight); //according to weight
}

void MyRegion::enqueueToFastMotorcycles(Motorcycle * order)
{
	fastMotorcycles.enqueue(order);
}

void MyRegion::enqueueToFrozenMotorcycles(Motorcycle * order)
{
	frozenMotorcycles.enqueue(order);
}

void MyRegion::enqueueToNormalMotorcycles(Motorcycle * order)
{
	normalMotorcycles.enqueue(order);
}

REGION MyRegion::GetRegionType() const
{
	return regionType;
}

bool MyRegion::isRushHour()
{
	return rushHour;
}

bool MyRegion::dequeueFrozen_VIP_PHASE_1_ONLY(Order *& o)
{
	return frozen_VIP.dequeue(o);
}

bool MyRegion::isThereAnyOrder()
{
	return !normal.isEmpty() || !frozen_VIP.isEmpty();
}

bool MyRegion::NormalOrdersRemoveLast(Order *& o)
{
	return normal.RemoveLast(o);
}

void MyRegion::addMyOrdersToDrawOrdersArr(GUI * pGUI)
{
	Order * mark = NULL;
	Order * o = NULL;

	PrioritizedNode<Order*>* frozenVipCurrent = frozen_VIP.getFront();
	while (frozenVipCurrent) {
		pGUI->AddOrderForDrawing(frozenVipCurrent->getItem());
		frozenVipCurrent = frozenVipCurrent->getNext();
	}

	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////

	if (normal.RemoveLast(mark)) {

		pGUI->AddOrderForDrawing(mark);
		normal.insertBeg(mark);
		normal.RemoveLast(o);
		if (mark == o) normal.insertBeg(mark);

		while (o != mark) {
			pGUI->AddOrderForDrawing(o);
			normal.insertBeg(o);
			normal.RemoveLast(o);
		}
	}
}

int MyRegion::getNormalOrdersCount()
{
	return normal.getSize();
}

int MyRegion::getFrozenOrdersCount()
{
	int count = 0;

	Node<Order*>* current = frozen_VIP.getFront();
	while (current) {
		if (current->getItem()->GetType() == TYPE_FROZ) count++;
		
			current = current->getNext();
	}

	return count;
}

int MyRegion::getVipOrdersCount()
{
	int count = 0;

	Node<Order*>* current = frozen_VIP.getFront();
	while (current) {
		if (current->getItem()->GetType() == TYPE_VIP) count++;

		current = current->getNext();
	}

	return count;
}

int MyRegion::getNormalMotorcyclesCount()
{
	return normalMotorcycles.getSize();
}

int MyRegion::getFrozenMotorcyclesCount()
{
	return frozenMotorcycles.getSize();
}

int MyRegion::getFastMotorcyclesCount()
{
	return fastMotorcycles.getSize();
}

bool MyRegion::GetNormalByID(int ID, Order *& o)
{
	int index = getNormalOrderIndexFromID(ID);
	if (index == -1) return false;

	Node<Order*>** normalList = normal.getArray();

	o = normalList[index]->getItem();

	//if (index > 0 && index < normal.getSize() - 1) {
	//	normalList[index - 1]->setNext(normalList[index + 1]);
	//	//delete normalList[index];
	//}
	//else if (index == 0)
	//	normal.Remove(o, 0);
	//else
	//	normalList[index - 1]->setNext(NULL);

	return true;
}

int MyRegion::getNormalOrderIndexFromID(int ID)
{
	int i;
	Node<Order*>* current = normal.GetHead();

	for (i = 0; current; i++) {
		if (current->getItem()->GetID() == ID)
			return i;

		current = current->getNext();
	}

	return -1;
}

bool MyRegion::ExcludeNormalOrderFromNormalListByID(int ID, Order *& o)
{
	int index = getNormalOrderIndexFromID(ID);
	if (index == -1) return false;

	Node<Order*>** normalList = normal.getArray();

	o = normalList[index]->getItem();
	//delete o;

	if (index > 0 && index < normal.getSize() - 1) {
		normalList[index - 1]->setNext(normalList[index + 1]);
		delete normalList[index];
	}
	else if (index == 0)
		normal.Remove(0);
	else
		normalList[index - 1]->setNext(NULL);
}

void MyRegion::printContents()
{
	std::cout << "\n----------------------- " << regionType << " ----------------------- \n";

	std::cout << "frozenVIP = ";
	Order::printIds(frozen_VIP.getFront());

	std::cout << "normal = ";
	Order::printIds(normal.GetHead());

	std::cout << " ------------------------ \n";

	std::cout << "normalMotorcycles = ";
	Motorcycle::printIds(normalMotorcycles.getFront());

	std::cout << "frozenMotorcycles = ";
	Motorcycle::printIds(frozenMotorcycles.getFront());

	std::cout << "fastMotorcycles = ";
	Motorcycle::printIds(fastMotorcycles.getFront());
	
	std::cout << " __________________________________________________________ \n";
}


