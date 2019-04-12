//#ifndef __ARRIVAL_EVENT_H_
//#define __ARRIVAL_EVENT_H_
#pragma once

#include "..\Rest\Restaurant.h"
#include "Event.h"
#include "..\Rest\MyRegion.h"

//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	MyRegion* OrdRegion;  //Region of this order	                
	int OrdMoney;	//Total order money
	

public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, MyRegion* reg, PriorityQueue<Event*> &  EventsQueue);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, MyRegion* reg, int distance, int money, PriorityQueue<Event*> & EventsQueue);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

//#endif