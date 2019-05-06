#pragma once

#include "..\Defs.h"
#include "..\Generic_DS\Queue.h"
//#include "Order.h"
//#include "Motorcycle.h"
#include "..\Generic_DS\List.h"
#include "..\Generic_DS\PriorityQueue.h"
//#include "Restaurant.h"

class Resturant;
class Order;
class Motorcycle;
class GUI;

class MyRegion
{
	REGION regionType;

	PriorityQueue<Order*> frozen_VIP;
	PriorityQueue<Order*> VIP;
	Queue<Order *> frozen;
	List<Order*> normal;

	PriorityQueue<Motorcycle*> InServiceMotorcycles;
	

	Queue<Motorcycle*> fastMotorcycles;
	Queue<Motorcycle*> frozenMotorcycles;
	Queue<Motorcycle*> normalMotorcycles;

	bool rushHour;

	int getNormalOrderIndexFromID(int ID);
	
	void assignMotorcycles(int currentTime);
	void getReturnedMotorcycles(int currentTime);

public:
	MyRegion(REGION regionType);

	// functions to add to each queue 
	void AddToNormal(Order* order);
	void enqueueToFrozen_VIP(Order* order, double weight = 0);
	void enqueueToVIP(Order* order, double weight);
	void enqueueTofrozen(Order* order);


	void enqueueToFastMotorcycles(Motorcycle* order);
	void enqueueToFrozenMotorcycles(Motorcycle* order);
	void enqueueToNormalMotorcycles(Motorcycle* order);

	REGION GetRegionType() const;
	bool isRushHour();

	bool dequeueFrozen_VIP_PHASE_1_ONLY(Order *& o);
	bool NormalOrdersRemoveLast(Order *& o);
	bool ExcludeNormalOrderFromNormalListByID(int ID, Order *& o);

	bool isThereAnyOrder();

	void addMyOrdersToDrawOrdersArr(GUI * pGUI);

	int getNormalOrdersCount();
	int getFrozenOrdersCount();
	int getVipOrdersCount();
	int getNormalMotorcyclesCount();
	int getFrozenMotorcyclesCount();
	int getFastMotorcyclesCount();

	bool GetNormalByID(int ID, Order *& o);

	void printContents();

	void doAssigningStuff(int currentTime);
	
	
};