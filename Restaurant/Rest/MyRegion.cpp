#include "MyRegion.h"
#include "Order.h"
#include "..\GUI\GUI.h"
//#include "Motorcycle.h"
#include "Restaurant.h"
//#include "..\Rest\Restaurant.h"


MyRegion::MyRegion(REGION regionType) :regionType(regionType), rushHour(false)
{

}

void MyRegion::AddToNormal(Order * order)
{
	normal.insertBeg(order);
}

//void MyRegion::enqueueToFrozen_VIP(Order * order, double weight)
//{
//	frozen_VIP.enqueue(order, weight); //according to weight
//}

void MyRegion::enqueueToVIP(Order * order, double weight)
{
	VIP.enqueue(order, weight);
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

//bool MyRegion::dequeueFrozen_VIP_PHASE_1_ONLY(Order *& o)
//{
//	return frozen_VIP.dequeue(o);
//}

bool MyRegion::isThereAnyWaitingOrder()
{
	//return !normal.isEmpty() || !frozen_VIP.isEmpty();
	return !normal.isEmpty() || !VIP.isEmpty() || !frozen.isEmpty();
}

bool MyRegion::isThereAnyInServiceMotorcycles()
{
	return !InServiceMotorcycles.isEmpty();
}

bool MyRegion::NormalOrdersRemoveLast(Order *& o)
{
	return normal.RemoveLast(o);
}

void MyRegion::addMyOrdersToDrawOrdersArr(GUI * pGUI)
{
	PrioritizedNode<Order*>* VipCurrent = VIP.getFront();
	while (VipCurrent) {
		pGUI->AddOrderForDrawing(VipCurrent->getItem());
		VipCurrent = VipCurrent->getNext();
	}

	Node<Order*>* frozenCurrent = frozen.getFront();
	while (frozenCurrent) {
		pGUI->AddOrderForDrawing(frozenCurrent->getItem());
		frozenCurrent = frozenCurrent->getNext();
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

	std::cout << "VIP = ";
	Order::printIds(VIP.getFront());

	std::cout << "frozen = ";
	Order::printIds(frozen.getFront());

	std::cout << "normal = ";
	Order::printIds(normal.GetHead());

	std::cout << " ------------------------ \n";
	std::cout << "delivered = ";
	Order::printIds(deliveredOrders.getFront());


	std::cout << " ------------------------ \n";

	std::cout << "normalMotorcycles = ";
	Motorcycle::printIds(normalMotorcycles.getFront(), false, false);

	std::cout << "frozenMotorcycles = ";
	Motorcycle::printIds(frozenMotorcycles.getFront(), false, false);

	std::cout << "fastMotorcycles = ";
	Motorcycle::printIds(fastMotorcycles.getFront(), false, false);

	std::cout << " ------------------------ \n";
	std::cout << "InServiceMotorcycles = ";
	Motorcycle::printIds(InServiceMotorcycles.getFront(), true, true);

	std::cout << " __________________________________________________________ \n";
}

//void MyRegion::doAssigningStuff(int currentTime)
//{
//	assignOrdersToMotorcycles(currentTime);
//	handleReturnedMotorcycles(currentTime);
//}

void MyRegion::assignOrdersToMotorcycles(int currentTime)
{
	Order * currentOrder;
	Motorcycle * mc = NULL;
	/////////////////////////// VIP Assignment ///////////////////////////
	while (!VIP.isEmpty() && 
		(!fastMotorcycles.isEmpty() || !frozenMotorcycles.isEmpty() || !normalMotorcycles.isEmpty())) {

		VIP.dequeue(currentOrder);

		if (!fastMotorcycles.dequeue(mc))
			if (!frozenMotorcycles.dequeue(mc))
				normalMotorcycles.dequeue(mc);

		mc->assignOrder(currentOrder, currentTime, InServiceMotorcycles);
	}
	/////////////////////////// Frozen Assignment ///////////////////////////
	while (!frozen.isEmpty() && !frozenMotorcycles.isEmpty()) {
		frozen.dequeue(currentOrder);
		frozenMotorcycles.dequeue(mc);

		mc->assignOrder(currentOrder, currentTime, InServiceMotorcycles);
	}
	/////////////////////////// Normal Assignment ///////////////////////////
	while (!normal.isEmpty() && !normalMotorcycles.isEmpty()) {
		normal.RemoveLast(currentOrder);
		normalMotorcycles.dequeue(mc);

		mc->assignOrder(currentOrder, currentTime, InServiceMotorcycles);
	}
}

void MyRegion::handleReturnedMotorcycles(int currentTime/*, Restaurant * R_ptr*/)
{
	//Restaurant * R_ptr;
	Motorcycle * mc;
	InServiceMotorcycles.peekFront(mc);
	if (InServiceMotorcycles.isEmpty())
		return;

	while (!InServiceMotorcycles.isEmpty() && mc->getReturnTime() <= currentTime) {
		InServiceMotorcycles.dequeue(mc);
		
		Order * deliveredOrder;
		deliveredOrder = mc->getOrder();
		deliveredOrder->setDelivered(true);
		int FT = deliveredOrder->GetFinishTime();
		deliveredOrders.enqueue(deliveredOrder, 1 / FT);
		
		mc->unassignOrder();
		switch (mc->getMotorcycleType()) {
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


