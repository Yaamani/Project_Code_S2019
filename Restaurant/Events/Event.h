#ifndef __EVENT_H_
#define __EVENT_H_

#include "..\Defs.h"
#include "..\Generic_DS\PriorityQueue.h"
#include <iostream>

class Restaurant;	//Forward declation
class MyRegion;
class Order;

//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
public:
	Event(int eTime, int ordID, PriorityQueue<Event*> & EventsQueue);
	int getEventTime();
	int getOrderID();
	virtual ~Event();

	int GetID();

	virtual void Execute(Restaurant* pRest)=0;	////a pointer to "Restaurant" and events need it to execute
	static void printIds(Node<Event*> * current);

};


#endif