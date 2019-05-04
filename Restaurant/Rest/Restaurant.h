//#ifndef __RESTAURANT_H_
//#define __RESTAURANT_H_

#define REGCOUNT 4
#define MAXID 500

#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\List.h"
#include "..\Events\Event.h"
#include "MyRegion.h"
#include "Order.h"
#include "..\Generic_DS\PriorityQueue.h"
#include <iostream>
#include <fstream>

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	PriorityQueue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

	MyRegion* regions[REGCOUNT];

	MyRegion* regionA;
	MyRegion* regionB;
	MyRegion* regionC;
	MyRegion* regionD;

	PriorityQueue<Order*> deliveredOrders;
	
	bool loadFiles(string path);
	void fillOrdersGUI();

	//List<Order*> bagOfOrdersNormal;

	void testBagADT();
	void testPrioritizedNode();
	void testPriorityQueue();
	void testFileLoading();

	bool phase1CancelationForTesting();

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 

	//
	// TODO: Add More Member Functions As Needed
	//

	void Interactive();
	MyRegion* GetMyRegion(int i);

	void addToDelivered(Order* delivered);

};

//#endif