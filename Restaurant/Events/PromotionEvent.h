//#ifndef __ARRIVAL_EVENT_H_
//#define __ARRIVAL_EVENT_H_
#pragma once

#include "..\Rest\Restaurant.h"
#include "Event.h"
#include "..\Rest\MyRegion.h"

//class for the arrival event
class PromotionEvent : public Event
{
	int exMon;

public:
	PromotionEvent(int eTime, int oID, int exMon, PriorityQueue<Event*> & EventsQueue);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

//#endif