#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, MyRegion * reg, PriorityQueue<Event*> &  EventsQueue) : Event(eTime, oID, EventsQueue)
{
	OrdType = oType;
	OrdRegion = reg;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, MyRegion* reg, int distance, int money, PriorityQueue<Event*> &  EventsQueue):Event(eTime, oID, EventsQueue)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance = distance;
	OrdMoney = money;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(OrderID, OrdType, OrdRegion, EventTime, OrdDistance, OrdMoney);
	//pRest->addToAllOrders(pOrd);

	//double weight = 0;
	
	//switch (OrdType)
	//{
	//case TYPE_NRM:
	//	//pOrd->GetRegion()->AddToNormal(pOrd);
	//	return;
	//	//pRest->addToAllOrders(pOrd);
	//	break;
	//case TYPE_VIP:
	//	/// Calculate weight
	//	weight = 1;
	//	break;
	//}

	////pOrd->GetRegion()->enqueueToFrozen_VIP(pOrd, weight);
}
