//#ifndef __MOTORCYCLE_H_
//#define __MOTORCYCLE_H_

#pragma once

#include "..\Defs.h"
#include "MyRegion.h"

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
	static void printIds(Node<Motorcycle*> * current);
	
	void setOrder(Order* inServiceOrder);
	Order * getOrder();
	ORD_TYPE getMotorCycleType();

	void setReturnTime(int time);
	int getReturnTime();

	int GetID();//
	int getSpeed();
	virtual ~Motorcycle();
};

//#endif