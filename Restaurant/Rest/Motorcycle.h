//#ifndef __MOTORCYCLE_H_
//#define __MOTORCYCLE_H_

#pragma once

#include "..\Defs.h"
#include "..\\Generic_DS\PriorityQueue.h"

class MyRegion;
class Order;
//class PriorityQueue<Motorcycle>;

class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	//int speed;		//meters it can move in one clock tick (in one timestep)
	MyRegion* region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	Order* currentInServiceOrder;
	int returnTime;

protected:
	static int normalSpeed;
	static int frozenSpeed;
	static int vipSpeed;

public:
	Motorcycle(int ID, int speed, MyRegion* region, ORD_TYPE type);
	
	static void setNormalSpeed(int ns);
	static void setFrozenSpeed(int fs);
	static void setVipSpeed(int vs);
	static void printIds(Node<Motorcycle*> * current, bool printType, bool printOrderInfo);
	
	void assignOrder(Order* inServiceOrder, int assignmentTime, PriorityQueue<Motorcycle*> & InServiceMotorcycles);
	void unassignOrder();
	Order * getOrder();
	ORD_TYPE getMotorcycleType();

	void setReturnTime(int time);
	int getReturnTime();

	int GetID();
	int getSpeed();
	virtual ~Motorcycle();
};

//#endif