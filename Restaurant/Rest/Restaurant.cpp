#pragma once
#include "Restaurant.h"
#include "MyRegion.h"
#include "Order.h"

using namespace std;

Restaurant::Restaurant()
{
	pGUI = NULL;

	regionA = new MyRegion(A_REG);
	regionB = new MyRegion(B_REG);
	regionC = new MyRegion(C_REG);
	regionD = new MyRegion(D_REG);

	regions[0] = regionA;
	regions[1] = regionB;
	regions[2] = regionC;
	regions[3] = regionD;

	//testBagADT();
	//testPrioritizedNode();
	//testPriorityQueue();
	//testFileLoading();
	
	//loadFiles("test1.txt");


}

void Restaurant::testFileLoading() {
	loadFiles("test1.txt");

	Event::printIds(EventsQueue.getFront());
	for (int i = 0; i < REGCOUNT; i++) {
		regions[i]->printContents();
	}
}

bool Restaurant::loadFiles(string path)
{
	ifstream i(path);
	if (!i.is_open()) {
		//throw "FNF";
		return false;
	}

	int normalSpeed, frozenSpeed, fastSpeed;
	i >> normalSpeed >> frozenSpeed >> fastSpeed;
	Motorcycle::setNormalSpeed(normalSpeed);
	Motorcycle::setFrozenSpeed(frozenSpeed);
	Motorcycle::setVipSpeed(fastSpeed);

	int normalCount[REGCOUNT];
	int frozenCount[REGCOUNT];
	int vipCount[REGCOUNT];

	int k = 0;
	for (int c = 0; c < REGCOUNT; c++) {
		i >> normalCount[c] >> frozenCount[c] >> vipCount[c];

		for (int j = 0; j < normalCount[c]; j++) {
			//regions[c]->enqueueToNormalMotorcycles(
				new Motorcycle(k++, normalSpeed, regions[c], ORD_TYPE::TYPE_NRM)
			/*)*/;
		}

		for (int j = 0; j < frozenCount[c]; j++) {
			//regions[c]->enqueueToFrozenMotorcycles(
				new Motorcycle(k++, frozenSpeed, regions[c], ORD_TYPE::TYPE_FROZ)
			/*)*/;
		}

		for (int j = 0; j < vipCount[c]; j++) {
			//regions[c]->enqueueToFastMotorcycles(
				new Motorcycle(k++, fastSpeed, regions[c], ORD_TYPE::TYPE_VIP)
			/*)*/;
		}

	}

	int apl;
	i >> apl;
	Order::setAutoPromotionLimit(apl);

	int numOfEvents;
	i >> numOfEvents;

	char event;
	int TS, ID, TYP, DST, MON, REG, ExMon;
	for (int c = 0; c < numOfEvents; c++) { 
		i >> event;
		switch (event) {
		case 'R':
			i >> TS >> TYP >> ID >> DST >> MON >> REG;
			//EventsQueue.enqueue(
				new ArrivalEvent(TS, ID, ORD_TYPE(TYP), regions[REG], DST, MON, EventsQueue)
			/*)*/;
			break;
		case 'X':
			i >> TS >> ID;
			//EventsQueue.enqueue(
				new CancelationEvent(TS, ID, EventsQueue)
			/*)*/;
			break;
		case 'P':
			i >> TS >> ID >> ExMon;
			//EventsQueue.enqueue(
				new PromotionEvent(TS, ID, ExMon, EventsQueue)
			/*)*/;
			break;
		}
	}

	return true;
}



void Restaurant::testBagADT()
{
	//List<Order*> bagOfOrdersNormal; // For Testing

	//Order* order0 = new Order(0, TYPE_NRM, regionA);
	//Order* order1 = new Order(1, TYPE_NRM, regionA);
	//Order* order2 = new Order(2, TYPE_NRM, regionA);
	//Order* order3 = new Order(3, TYPE_NRM, regionA);
	//Order* order4 = new Order(4, TYPE_NRM, regionA);

	//bagOfOrdersNormal.insertBeg(order0);
	//bagOfOrdersNormal.insertBeg(order1);
	//bagOfOrdersNormal.insertBeg(order2);
	//bagOfOrdersNormal.insertBeg(order3);
	//bagOfOrdersNormal.insertBeg(order4);

	//bagOfOrdersNormal.printIds();

	//bagOfOrdersNormal.Remove(0);
	//bagOfOrdersNormal.printIds();

	//bagOfOrdersNormal.Remove(order2);
	//bagOfOrdersNormal.printIds();

	//bagOfOrdersNormal.Remove(order4);
	//bagOfOrdersNormal.printIds();

	//std::cout << "Ay ha\n";

	//Order* orderFirst;
	//bagOfOrdersNormal.RemoveLast(orderFirst);
	//bagOfOrdersNormal.printIds();
	//std::cout << orderFirst->GetID() << endl;

	//allOrders[3] = order3;

	//bool removeNotHere = bagOfOrdersNormal.Remove(allOrders[3]);
	//bagOfOrdersNormal.printIds();
	//std::cout << removeNotHere << endl;

	/*bagOfOrdersNormal.insert(orderFirst);
	bagOfOrdersNormal.printIds();

	orderFirst;
	bagOfOrdersNormal.RemoveLast();
	bagOfOrdersNormal.printIds();
	std::cout << orderFirst->GetID();

	orderFirst;
	bagOfOrdersNormal.RemoveLast();
	bagOfOrdersNormal.printIds();
	std::cout << orderFirst->GetID();*/

	//delete orderFirst;
}

void Restaurant::testPrioritizedNode()
{
	PrioritizedNode<int>* p0 = new PrioritizedNode<int>(0);
	PrioritizedNode<int>* p1 = new PrioritizedNode<int>(1, 2);

	p0->setNext(p1);

	std::cout << p0->getNext()->getWeight() << std::endl;
}

void Restaurant::testPriorityQueue()
{
	PriorityQueue<Order*> pq;

	Order* order0 = new Order(0, TYPE_NRM, regionA);
	Order* order1 = new Order(1, TYPE_NRM, regionA);
	Order* order2 = new Order(2, TYPE_NRM, regionA);
	Order* order3 = new Order(3, TYPE_NRM, regionA);
	Order* order4 = new Order(4, TYPE_NRM, regionA);

	pq.enqueue(order0, 11);
	Order::printIds(pq.getFront());

	pq.enqueue(order2, 22);
	Order::printIds(pq.getFront());
	
	pq.enqueue(order1, 11);
	Order::printIds(pq.getFront());
	
	pq.enqueue(order3, 22);
	Order::printIds(pq.getFront());
	
	pq.enqueue(order4, 33);
	Order::printIds(pq.getFront());
	
	std::cout << "Ay ha\n";

	Order* o;
	
	while (pq.dequeue(o))
	{
		Order::printIds(pq.getFront());
		std::cout << o->GetID() << std::endl;
	}

	pq.enqueue(order3, 22);
	Order::printIds(pq.getFront());

	pq.enqueue(order4, 33);
	Order::printIds(pq.getFront());

	pq.enqueue(order1, 11);
	Order::printIds(pq.getFront());

	while (pq.dequeue(o))
	{
		Order::printIds(pq.getFront());
		std::cout << o->GetID() << std::endl;
	}
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	
	pGUI->PrintMessage("Please Enter File Name (Choose \"Interactive\" next) : ");
	while (!loadFiles(pGUI->GetString())) {
		pGUI->PrintMessage("File Name Was Incorrect. Enter Again (Choose \"Interactive\" next) : ");
	}
	
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL)); 

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
	
	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		 
		switch (reg)
		{
		case A_REG:
			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionA, EventsQueue);
			break;
		case B_REG:
			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionB, EventsQueue);
			break;
		case C_REG:
			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionC, EventsQueue);
			break;
		case D_REG:
			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionD, EventsQueue);
			break;
		}
		
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}


/// ==> end of DEMO-related function

////////////////////////////////////////////////////////////////////

//bool Restaurant::phase1CancelationForTesting()
//{
//	Order* o;
//	bool allOrdersCanceled[] = { false, false, false, false };
//	for (int i = 0; i < REGCOUNT; i++) {
//		o = NULL;
//		if (!regions[i]->dequeueFrozen_VIP_PHASE_1_ONLY(o))
//			regions[i]->NormalOrdersRemoveLast(o);
//
//		if (o) 
//			delete o;
//
//		if (!regions[i]->isThereAnyWaitingOrder()) 
//			allOrdersCanceled[i] = true;
//
//		//o = NULL;
//	}
//
//	return allOrdersCanceled[0] && allOrdersCanceled[1] && allOrdersCanceled[2] && allOrdersCanceled[3];		
//}

/// ==> Interactive-related functions
void Restaurant::Interactive()
{
	/// Advance to the next time step by a mouce click
	/// 
	int motoNormCount = 0, motoFastCount = 0, motoFrCount = 0;
	for (int i = 0; i < REGCOUNT; i++) {
		motoNormCount += regions[i]->getNormalMotorcyclesCount();
		motoFastCount += regions[i]->getFastMotorcyclesCount();
		motoFrCount += regions[i]->getFrozenMotorcyclesCount();
	}

	bool thereAreWaitingOrders = true;
	bool thereAreInServiceMotorcycles = false;

	for (int currentTimeStep = 0; 
		!EventsQueue.isEmpty() || thereAreWaitingOrders || thereAreInServiceMotorcycles/*true*/;
		currentTimeStep++)
	{
		////////////////////// Events Excecution //////////////////////
		////////////////////// Events Excecution //////////////////////
		////////////////////// Events Excecution //////////////////////
		pGUI->waitForClick();
		Event* x;
		EventsQueue.peekFront(x);
		if (x->getEventTime() == currentTimeStep) {
			while (EventsQueue.dequeue(x)) {
				x->Execute(this);
				EventsQueue.peekFront(x);
				if (x->getEventTime() != currentTimeStep)
					break;
			}
		}

		////////////////////// Motorcycles Assignment & Auto Promotion //////////////////////
		////////////////////// Motorcycles Assignment & Auto Promotion //////////////////////
		////////////////////// Motorcycles Assignment & Auto Promotion //////////////////////
		
		for (int i = 0; i < REGCOUNT; i++) {
			//regions[i]->doAssigningStuff(currentTimeStep);

			regions[i]->assignOrdersToMotorcycles(currentTimeStep);
			regions[i]->handleReturnedMotorcycles(currentTimeStep);
		}

		//////////////////////
		//////////////////////
		//////////////////////

		thereAreWaitingOrders = false;
		for (int i = 0; i < REGCOUNT; i++) {
			if (regions[i]->isThereAnyWaitingOrder()) {
				thereAreWaitingOrders = true;
				break;
			}
		}

		thereAreInServiceMotorcycles = false;
		for (int i = 0; i < REGCOUNT; i++) {
			if (regions[i]->isThereAnyInServiceMotorcycles()) {
				thereAreInServiceMotorcycles = true;
				break;
			}
		}

		//////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////

		pGUI->ResetDrawingList();
		fillOrdersGUI();
		pGUI->UpdateInterface();		

		////////////////////// Status Bar Printing //////////////////////
		////////////////////// Status Bar Printing //////////////////////
		////////////////////// Status Bar Printing //////////////////////

		string statusBar = "";
		char ch[10];
		itoa(currentTimeStep, ch, 10);
		//pGUI->PrintMessage(timestep);
		statusBar.append(ch);

		int normalCount = 0, frozenCount = 0, vipCount = 0;
		for (int i = 0; i < REGCOUNT; i++) {
			normalCount += regions[i]->getNormalOrdersCount();
			frozenCount += regions[i]->getFrozenOrdersCount();
			vipCount += regions[i]->getVipOrdersCount();
		}


		char nC[10], fC[10], vC[10];
		itoa(normalCount, nC, 10);
		itoa(frozenCount, fC, 10);
		itoa(vipCount, vC, 10);
		statusBar.append(" | Normal Count = ");
		statusBar.append(nC);
		statusBar.append(" | Frozen Count = ");
		statusBar.append(fC);
		statusBar.append(" | Vip Count = ");
		statusBar.append(vC);

		char motoNormC[10], motoFastC[10], motoFrC[10];
		itoa(motoNormCount, motoNormC, 10);
		itoa(motoFastCount, motoFastC, 10);
		itoa(motoFrCount, motoFrC, 10);
		statusBar.append(" | Norm Moto Count = ");
		statusBar.append(motoNormC);
		statusBar.append(" | Froz Moto Count = ");
		statusBar.append(motoFrC);
		statusBar.append(" | Fast Moto Count = ");
		statusBar.append(motoFastC);

		pGUI->PrintMessage(statusBar);

		////////////////////// Console Printing //////////////////////
		////////////////////// Console Printing //////////////////////
		////////////////////// Console Printing //////////////////////

		std::cout << "================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================" << endl;
		Event::printIds(EventsQueue.getFront());
		for (int i = 0; i < REGCOUNT; i++) {
			regions[i]->printContents();
		}
	}

}

void Restaurant::fillOrdersGUI()
{
	for (int i = 0; i < REGCOUNT; i++) {
		regions[i]->addMyOrdersToDrawOrdersArr(pGUI);
	}
}

MyRegion * Restaurant::GetMyRegion(int i)
{
	return regions[i];
}

//void Restaurant::addToDelivered(Order * delivered)
//{
//	int FT = delivered->GetFinishTime();
//	deliveredOrders.enqueue(delivered,1/FT);
//}
