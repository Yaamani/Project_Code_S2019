#pragma once

#include "..\Defs.h"
#include "MyRegion.h"

class Order
{

protected:
	static int autoPromotionLimit;

	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	MyRegion* Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, WaitTime, ServTime, FinishTime;	//arrival, wait time (Duration), service start (Duration), and finish times

	
	
	//
	// TODO: Add More Data Members As Needed
	//
	bool delivered;

	double calculateVipWeight();

public:
	Order(int ID);
	//Order(int ID, ORD_TYPE r_Type, MyRegion* r_region);
	Order(int ID, ORD_TYPE r_Type, MyRegion * r_region, int ArrTime = 0, int distance = 0, int money = 0);

	virtual ~Order();

	int GetID();

	int GetType() const;
	MyRegion* GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;

	//
	// TODO: Add More Member Functions As Needed
	//
	void setDelivered(bool i );
	bool isDelivered();

	void SetMoney(int m);
	int GetMoney() const;

	void SetArrTime(int a);
	int  GetArrTime() const;

	void SetWaitTime(int w);
	int  GetWaitTime() const;

	void SetServTime(int s);
	int  GetServTime() const;
	
	int  GetFinishTime() const;

	double promoteAndReturnWeight(int promotionMoney);
	
	static void setAutoPromotionLimit(int apl);
	static void printIds(Node<Order*> * current);
	//bool operator==(Order* o);
};



//#endif