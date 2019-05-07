#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int eTime, int oID, int exMon, PriorityQueue<Event*> & EventsQueue):Event(eTime, oID, EventsQueue), exMon(exMon)
{
	
}

void PromotionEvent::Execute(Restaurant* pRest)
{
	MyRegion* r;
	Order* o;

	for (int i = 0; i < REGCOUNT; i++) {
		r = pRest->GetMyRegion(i);
		if (r->ExcludeNormalOrderFromNormalListByID(OrderID, o)) {
			//pRest->getAllOrders()[OrderID] = NULL;
			double weight = o->promoteAndReturnWeight(exMon);
			r->enqueueToFrozen_VIP(o, weight);
			r->enqueueToVIP(o,weight);
			break;
		}
	}
	//pRest->AddtoDemoQueue(pOrd);
}
