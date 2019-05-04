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

void MyRegion::enqueueToVIP(Order * order, double weight)
{
	VIP.enqueue(order,weight);
}

void MyRegion::enqueueTofrozen(Order * order)
{
	frozen.enqueue(order);
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
	PrioritizedNode<Order*>* frozenVipCurrent = frozen_VIP.getFront();
	while (frozenVipCurrent) {
		pGUI->AddOrderForDrawing(frozenVipCurrent->getItem());
		frozenVipCurrent = frozenVipCurrent->getNext();
	}

	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////

	Order** normalOrdersInReverseOrder = new Order*[normal.getSize()];
	Node<Order*>* normalCurrent = normal.GetHead();
	for (int i = 0; normalCurrent; i++) {
		normalOrdersInReverseOrder[i] = normalCurrent->getItem();
		normalCurrent = normalCurrent->getNext();
	}
	for (int i = normal.getSize() - 1; i >= 0; i--) {
		pGUI->AddOrderForDrawing(normalOrdersInReverseOrder[i]);
	}
}

int MyRegion::getNormalOrdersCount()
{
	return normal.getSize();
}

int MyRegion::getFrozenOrdersCount()
{
	return frozen.getSize();
}

int MyRegion::getVipOrdersCount()
{
	return VIP.getSize();
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
		normal.deletionDoneOutside();
	}
	else if (index == 0)
		normal.Remove(0);
	else {
		normalList[index - 1]->setNext(NULL);
		delete normalList[index];
		normal.deletionDoneOutside();
	}

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

void MyRegion::doAssigningStuff(int currentTime)
{
	assignMotorcycles(currentTime);
	getReturnedMotorcycles(currentTime);
}

void MyRegion::assignMotorcycles(int currentTime)
{
	while (!VIP.isEmpty()&&(!fastMotorcycles.isEmpty()||!frozenMotorcycles.isEmpty()||!normalMotorcycles.isEmpty())) {
		Order * currentOrder;
		VIP.dequeue(currentOrder);
		Motorcycle * mc = NULL;
		if (fastMotorcycles.dequeue(mc)) {
			currentOrder->SetWaitTime(currentTime-currentOrder->GetArrTime());
			currentOrder->SetServTime(ceil(currentOrder->GetDistance() / mc->getSpeed()));
			mc->setOrder(currentOrder);
			int returnTime = currentTime + ceil(2 * currentOrder->GetDistance() / mc->getSpeed());
			mc->setReturnTime(returnTime);
			InServiceMotorcycles.enqueue(mc,1/returnTime);
			continue;
		}
		if (frozenMotorcycles.dequeue(mc)) {
			currentOrder->SetWaitTime(currentTime - currentOrder->GetArrTime());
			currentOrder->SetServTime(ceil(currentOrder->GetDistance() / mc->getSpeed()));
			mc->setOrder(currentOrder);
			int returnTime = currentTime + ceil(2 * currentOrder->GetDistance() / mc->getSpeed());
			mc->setReturnTime(returnTime);
			InServiceMotorcycles.enqueue(mc, 1 / returnTime);
			continue;
		}
		if (normalMotorcycles.dequeue(mc)) {
			currentOrder->SetWaitTime(currentTime - currentOrder->GetArrTime());
			currentOrder->SetServTime(ceil(currentOrder->GetDistance() / mc->getSpeed()));
			mc->setOrder(currentOrder);
			int returnTime = currentTime + ceil(2 * currentOrder->GetDistance() / mc->getSpeed());
			mc->setReturnTime(returnTime);
			InServiceMotorcycles.enqueue(mc, 1 / returnTime);
			continue;
		}
	}

	while (!frozen.isEmpty() && !frozenMotorcycles.isEmpty()) {
		Order * currentOrder;
		Motorcycle * mc = NULL;

		frozen.dequeue(currentOrder);
		frozenMotorcycles.dequeue(mc);
		
		currentOrder->SetWaitTime(currentTime - currentOrder->GetArrTime());
		currentOrder->SetServTime(ceil(currentOrder->GetDistance() / mc->getSpeed()));
		mc->setOrder(currentOrder);
		
		int returnTime = currentTime + ceil(2 * currentOrder->GetDistance() / mc->getSpeed());
		mc->setReturnTime(returnTime);
		
		InServiceMotorcycles.enqueue(mc, 1 / returnTime);	
	}

	while (!normal.isEmpty() && !normalMotorcycles.isEmpty()) {
		Order * currentOrder;
		Motorcycle * mc = NULL;
		
		normal.RemoveLast(currentOrder);
		normalMotorcycles.dequeue(mc);
		
		currentOrder->SetWaitTime(currentTime - currentOrder->GetArrTime());
		currentOrder->SetServTime(ceil(currentOrder->GetDistance() / mc->getSpeed()));
		mc->setOrder(currentOrder);
		
		int returnTime = currentTime + ceil(2 * currentOrder->GetDistance() / mc->getSpeed());
		mc->setReturnTime(returnTime);

		InServiceMotorcycles.enqueue(mc, 1 / returnTime);
	}
}

void MyRegion::getReturnedMotorcycles(int currentTime)
{
	Restaurant * R_ptr;
	Motorcycle * mc;
	InServiceMotorcycles.peekFront(mc);
	if (InServiceMotorcycles.isEmpty())
		return;
	
	while (!InServiceMotorcycles.isEmpty()&&mc->getReturnTime()<=currentTime) {
		InServiceMotorcycles.dequeue(mc);
		Order * deliveredOrder;
		deliveredOrder = mc->getOrder();
		deliveredOrder->setDelivered(TRUE);
		R_ptr->addToDelivered(deliveredOrder);
		mc->setOrder(NULL);
		switch (mc->getMotorCycleType()) {
		case TYPE_NRM:
			normalMotorcycles.enqueue(mc);
			break;
		case TYPE_FROZ:
			frozenMotorcycles.enqueue(mc);
			break;
		case TYPE_VIP:
			fastMotorcycles.enqueue(mc);
			break;
		}
		InServiceMotorcycles.peekFront(mc);
	}
}


