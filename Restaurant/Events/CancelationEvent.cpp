#include "CancelationEvent.h"

CancelationEvent::CancelationEvent(int eTime, int oID, PriorityQueue<Event*> & EventsQueue):Event(eTime, oID, EventsQueue)
{
	
}

void CancelationEvent::Execute(Restaurant* pRest) 
{
	// This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	MyRegion* r;
	Order* o;

	for (int i = 0; i < REGCOUNT; i++) {
		r = pRest->GetMyRegion(i);
		/// Handle cancelation event when the order is already canceled
		//if (r->DeleteNormalOrderByID(OrderID)) {
		if (r->ExcludeNormalOrderFromNormalListByID(OrderID, o)) {
			//pRest->getAllOrders()[OrderID] = NULL;
			delete o;
			break;
		}
	}
}
