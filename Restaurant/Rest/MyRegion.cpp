#include "MyRegion.h"
#include "Order.h"
#include "..\GUI\GUI.h"
//#include "Motorcycle.h"
#include "Restaurant.h"
//#include "..\Rest\Restaurant.h"


MyRegion::MyRegion(REGION regionType) :regionType(regionType), rushHour(false)
{
	inServiceFrozenCounter = 0;
	inServiceNormalCounter = 0;
	inServiceVipCounter = 0;

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

//bool MyRegion::dequeueFrozen_VIP_PHASE_1_ONLY(Order *& currentNode)
//{
//	return frozen_VIP.dequeue(currentNode);
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
	/*PrioritizedNode<Order *> * VipCurrent = VIP.getFront();
	while (VipCurrent) {
		pGUI->AddOrderForDrawing(VipCurrent->getItem());
		VipCurrent = VipCurrent->getNext();
	}*/
	int vipSize = VIP.getSize();
	Order ** vipOrders = new Order * [vipSize];
	double * vipOrdersWeights = new double[vipSize];
	for (int i = 0; i < vipSize; i++) {
		VIP.dequeue(vipOrders[i], vipOrdersWeights[i]);
	}
	for (int i = 0; i < vipSize; i++) {
		pGUI->AddOrderForDrawing(vipOrders[i]);
		VIP.enqueue(vipOrders[i], vipOrdersWeights[i]);
	}

	/*Node<Order *> * frozenCurrent = frozen.getFront();
	while (frozenCurrent) {
		pGUI->AddOrderForDrawing(frozenCurrent->getItem());
		frozenCurrent = frozenCurrent->getNext();
	}*/
	int frozSize = frozen.getSize();
	Order ** frozOrders = new Order *[frozSize];
	//Order * current;
	for (int i = 0; i < frozSize; i++) {
		frozen.dequeue(frozOrders[frozSize - 1 - i]);
		frozen.enqueue(frozOrders[frozSize - 1 - i]);
	}
	for (int i = frozSize - 1; i >= 0; i--) {
		pGUI->AddOrderForDrawing(frozOrders[i]);
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

int MyRegion::GetDeliveredOrdersCount()
{
	return deliveredOrders.getSize();
}

Order ** MyRegion::GetDeliverdOrdersItemArray()
{
	return deliveredOrders.getItemArray();
}

double * MyRegion::GetDeliverdOrdersWeightArray()
{
	return deliveredOrders.getWeightArray();
}

int MyRegion::getInServiceVIPCount()
{
	return inServiceVipCounter;
}

int MyRegion::getInServiceNormalCount()
{
	return inServiceNormalCounter;
}

int MyRegion::getInServiceFrozenCount()
{
	return inServiceFrozenCounter;
}

bool MyRegion::GetNormalByID(int ID, Order *& o)
{
	int index = getNormalOrderIndexFromID(ID);
	if (index == -1) return false;

	Node<Order*>** normalList = normal.getNodeArray();

	o = normalList[index]->getItem();

	//if (index > 0 && index < normal.getSize() - 1) {
	//	normalList[index - 1]->setNext(normalList[index + 1]);
	//	//delete normalList[index];
	//}
	//else if (index == 0)
	//	normal.Remove(currentNode, 0);
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

	Node<Order*>** normalList = normal.getNodeArray();

	o = normalList[index]->getItem();
	//delete currentNode;

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
	Order::printIds(VIP.getItemArray(), VIP.getSize());

	std::cout << "frozen = ";
	Order::printIds(frozen.getItemArray(), frozen.getSize());

	std::cout << "normal = ";
	Order::printIds(normal.getItemArray(), normal.getSize());

	std::cout << "inService VIP = "<< getInServiceVIPCount() << endl;
	std::cout << "inService frozen = " << getInServiceFrozenCount()<< endl;
	std::cout << "inService normal = " << getInServiceNormalCount()<< endl;
	
	std::cout << " ------------------------ \n";
	std::cout << "delivered = ";
	Order::printIds(deliveredOrders.getItemArray(), deliveredOrders.getSize());


	std::cout << " ------------------------ \n";

	std::cout << "normalMotorcycles = ";
	Motorcycle::printIds(normalMotorcycles.getItemArray(), normalMotorcycles.getSize(), false, false);

	std::cout << "frozenMotorcycles = ";
	Motorcycle::printIds(frozenMotorcycles.getItemArray(), frozenMotorcycles.getSize(), false, false);

	std::cout << "fastMotorcycles = ";
	Motorcycle::printIds(fastMotorcycles.getItemArray(), fastMotorcycles.getSize(), false, false);

	std::cout << " ------------------------ \n";
	std::cout << "InServiceMotorcycles = ";
	Motorcycle::printIds(InServiceMotorcycles.getItemArray(), InServiceMotorcycles.getSize(), true, true);

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
		inServiceVipCounter++;
		mc->assignOrder(currentOrder, currentTime, InServiceMotorcycles);
	}
	/////////////////////////// Frozen Assignment ///////////////////////////
	while (!frozen.isEmpty() && !frozenMotorcycles.isEmpty()) {
		frozen.dequeue(currentOrder);
		frozenMotorcycles.dequeue(mc);
		inServiceFrozenCounter++;
		mc->assignOrder(currentOrder, currentTime, InServiceMotorcycles);
	}
	/////////////////////////// Normal Assignment ///////////////////////////
	while (!normal.isEmpty() && !normalMotorcycles.isEmpty()) {
		normal.RemoveLast(currentOrder);
		normalMotorcycles.dequeue(mc);
		inServiceNormalCounter++;
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
		if (!mc->getIsReturning()) {
			Order * deliveredOrder;
			deliveredOrder = mc->getOrder();
			deliveredOrder->setDelivered(true);
			int FT = deliveredOrder->GetFinishTime();
			deliveredOrders.enqueue(deliveredOrder, 1.0 / (double)FT);
			int returnTime = deliveredOrder->GetServTime() + currentTime;
			
			switch (deliveredOrder->GetType()) {
			case TYPE_NRM:
				inServiceNormalCounter--;
				break;
			case TYPE_FROZ:
				inServiceFrozenCounter--;
				break;
			case TYPE_VIP:
				inServiceVipCounter--;
				break;
			}
			
			mc->unassignOrder();
			mc->setIsReturning(true);
			mc->setReturnTime(returnTime);
			InServiceMotorcycles.enqueue(mc,1/returnTime);
		}
		else {
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
		}
		InServiceMotorcycles.peekFront(mc);
	}
}

void MyRegion::handleAutoPromotion(int currentTime)
{
	Node<Order *> * currentNode = normal.GetHead();
	for (int i = 0; currentNode; i++) {
		Order * o = currentNode->getItem();
		currentNode = currentNode->getNext();

		if (currentTime - o->GetArrTime() >= Order::getAutoPromotionLimit()) {
			normal.Remove(i);
			i--;
			double w = o->perpareForPromotionAndReturnWeight(0);
			VIP.enqueue(o, w);
		}
	}
}

double MyRegion::getAvgWait()
{
	Order ** delivered = GetDeliverdOrdersItemArray();;
	int deliveredSize = GetDeliveredOrdersCount();

	int sumOfWaitTime = 0;
	double AvgWaitTime = 0;

	for (int i = 0; i < deliveredSize; i++) {
		sumOfWaitTime += delivered[i]->GetWaitTime();
	}

	if (sumOfWaitTime == 0)
		return 0;

	return AvgWaitTime = (double)sumOfWaitTime / (double)deliveredSize;
}

double MyRegion::getAvgService()
{
	Order ** delivered = GetDeliverdOrdersItemArray();;
	int deliveredSize = GetDeliveredOrdersCount();

	int sumOfServiceTime = 0;
	double AvgServiceTime = 0;


	for (int i = 0; i < deliveredSize; i++) {
		sumOfServiceTime += delivered[i]->GetServTime();
	}

	if (sumOfServiceTime == 0)
		return 0;

	return AvgServiceTime = (double)sumOfServiceTime / (double)deliveredSize;
}
