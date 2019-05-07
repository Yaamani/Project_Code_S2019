#include "Event.h"


Event::Event(int eTime, int ordID, PriorityQueue<Event*> & EventsQueue)
{
	EventTime = eTime;
	OrderID	= ordID;

	EventsQueue.enqueue(this, 1.0/eTime);
}


int Event::getEventTime()
{
	return EventTime;
}
int Event::getOrderID()
{
	return OrderID;
}


Event::~Event()
{

}

int Event::GetID()
{
	return getOrderID();
}

void Event::printIds(Event ** arr, int size)
{
	/*while (current)
	{
		std::cout << current->getItem()->GetID() << ", ";
		current = current->getNext();
	}*/
	for (int i = 0; i < size; i++) {
		std::cout << arr[i]->GetID() << ", ";
	}

	std::cout << std::endl;
}

