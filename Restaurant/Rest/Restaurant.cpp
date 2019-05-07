#pragma once
#include "Restaurant.h"
#include "MyRegion.h"
#include "Order.h"

#define NOC getNormalOrdersCount()
#define FOC getFrozenOrdersCount()
#define VOC getVipOrdersCount()
#define NMC getNormalMotorcyclesCount()
#define FMC getFrozenMotorcyclesCount()
#define VMC getFastMotorcyclesCount()

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

void Restaurant::testFileOuting() {
	char ch;

	ofstream o("omar.txt");
	o << "FT\t" << "ID\t" << "AT\t" << "WT\t" << "ST\n";
	//////// delivered Orders

	for (int i = 0; i < REGCOUNT; i++)
	{
		switch (i)
		{
		case 0:
			ch = 'A';
			break;
		case 1:
			ch = 'B';
			break;
		case 2:
			ch = 'C';
			break;
		default:
			ch = 'D';
			break;
		}

		o << "\nRegion " << ch << ":\n\t";
		o << "Orders: " << regions[i]->NOC + regions[i]->FOC + regions[i]->VOC << " [Norm:" << regions[i]->NOC << ", FROZ:" << regions[i]->FOC << ",VIP:" << regions[i]->VOC << "]\n\t";
		o << "MotorC: " << regions[i]->VMC + regions[i]->FMC + regions[i]->NMC << " [Norm:" << regions[i]->NMC << ", FROZ:" << regions[i]->FMC << ",VIP:" << regions[i]->VMC << "]\n\t";
		o << "Avg Wait = " << ", " << "Avg Serv = ";

	}

}

void Restaurant::testFileLoading() {
	loadFiles("test1.txt");

	Event::printIds(EventsQueue.getItemArray(), EventsQueue.getSize());
	for (int i = 0; i < REGCOUNT; i++) {
		regions[i]->printContents();
	}
}

void Restaurant::simulation(PROG_MODE mode)
{
	for (int currentTimeStep = 0; shouldTheSimulationContinue(); currentTimeStep++)
	{
		if (mode == MODE_INTR)			// Interactive
			pGUI->waitForClick();
		else if (mode == MODE_STEP)		// Step By Step
			Sleep(1000);
		else if (mode == MODE_SLNT)		// Silent
		{/*Nothing*/
		}

		eventExcecution(currentTimeStep);

		autoPromotionHandler(currentTimeStep);
		motorcycleshandler(currentTimeStep);

		//////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////

		if (mode == MODE_INTR || mode == MODE_STEP) {
			guiUpdate();
			statusBarPrnting(currentTimeStep);
			consolePrinting(currentTimeStep);
		}
	}
	//testFileOuting();
	OutFile();
}

void Restaurant::eventExcecution(int currentTimeStep)
{
	if (EventsQueue.isEmpty())
		return;

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
}

void Restaurant::motorcycleshandler(int currentTimeStep)
{
	for (int i = 0; i < REGCOUNT; i++) {
		//regions[i]->doAssigningStuff(currentTimeStep);
		regions[i]->handleReturnedMotorcycles(currentTimeStep);
		regions[i]->assignOrdersToMotorcycles(currentTimeStep);
	}
}

bool Restaurant::shouldTheSimulationContinue()
{
	bool thereAreWaitingOrders = false;
	for (int i = 0; i < REGCOUNT; i++) {
		if (regions[i]->isThereAnyWaitingOrder()) {
			thereAreWaitingOrders = true;
			break;
		}
	}

	bool thereAreInServiceMotorcycles = false;
	for (int i = 0; i < REGCOUNT; i++) {
		if (regions[i]->isThereAnyInServiceMotorcycles()) {
			thereAreInServiceMotorcycles = true;
			break;
		}
	}

	return !EventsQueue.isEmpty() || thereAreWaitingOrders || thereAreInServiceMotorcycles/*true*/;
}

void Restaurant::autoPromotionHandler(int currentTimeStep)
{
	for (int i = 0; i < REGCOUNT; i++) {
		regions[i]->handleAutoPromotion(currentTimeStep);
	}
}

void Restaurant::guiUpdate()
{
	pGUI->ResetDrawingList();
	fillOrdersGUI();
	pGUI->UpdateInterface();
}

void Restaurant::statusBarPrnting(int currentTimeStep)
{
	string statusBar = "";
	string statusBar1 = "";
	string statusBar2 = "";
	string statusBar3 = "";
	string statusBar4 = "";

	char ch[10], r;
	itoa(currentTimeStep, ch, 10);
	statusBar.append("Time Step : ");
	statusBar.append(ch);

	int normalCount = 0, frozenCount = 0, vipCount = 0;
	int motoNormCount = 0, motoFastCount = 0, motoFrCount = 0;

	for (int i = 0; i < REGCOUNT; i++)
	{
		normalCount = regions[i]->NOC;
		frozenCount = regions[i]->FOC;
		vipCount = regions[i]->VOC;

		char nC[10], fC[10], vC[10];
		itoa(normalCount, nC, 10);
		itoa(frozenCount, fC, 10);
		itoa(vipCount, vC, 10);


		motoNormCount = regions[i]->NMC;
		motoFastCount = regions[i]->VMC;
		motoFrCount = regions[i]->FMC;

		char motoNormC[10], motoFastC[10], motoFrC[10];
		itoa(motoNormCount, motoNormC, 10);
		itoa(motoFastCount, motoFastC, 10);
		itoa(motoFrCount, motoFrC, 10);

		if (i == 0)
		{
			statusBar1.append("Region A:   ");
			statusBarRegionInfo(statusBar1, nC, fC, vC, motoNormC, motoFastC, motoFrC);
		}
		else if (i == 1)
		{
			statusBar2.append("Region B:   ");
			statusBarRegionInfo(statusBar2, nC, fC, vC, motoNormC, motoFastC, motoFrC);
		}
		else if (i == 2)
		{
			statusBar3.append("Region C:   ");
			statusBarRegionInfo(statusBar3, nC, fC, vC, motoNormC, motoFastC, motoFrC);
		}
		else if (i == 3)
		{
			statusBar4.append("Region D:   ");
			statusBarRegionInfo(statusBar4, nC, fC, vC, motoNormC, motoFastC, motoFrC);
		}

	}
	pGUI->PrintMessage(statusBar, statusBar1, statusBar2, statusBar3, statusBar4);
}

void Restaurant::statusBarRegionInfo(string & s, char nc[], char fc[], char vc[], char motoNormC[], char motoFastC[], char motoFrC[])
{
	s.append("Normal Count = ");
	s.append(nc);
	s.append(" | Frozen Count = ");
	s.append(fc);
	s.append(" | Vip Count = ");
	s.append(vc);


	s.append(" | Norm Moto Count = ");
	s.append(motoNormC);
	s.append(" | Froz Moto Count = ");
	s.append(motoFrC);
	s.append(" | Fast Moto Count = ");
	s.append(motoFastC);
}

void Restaurant::consolePrinting(int currentTimeStep)
{
	std::cout << "================================= currentTimeStep = " << currentTimeStep << "================================" << endl;
	Event::printIds(EventsQueue.getItemArray(), EventsQueue.getSize());
	for (int i = 0; i < REGCOUNT; i++) {
		regions[i]->printContents();
	}
}

bool Restaurant::loadFiles(string path)
{
	ifstream i(path + ".txt");
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
	Order::printIds(pq.getItemArray(), pq.getSize());

	pq.enqueue(order2, 22);
	Order::printIds(pq.getItemArray(), pq.getSize());

	pq.enqueue(order1, 11);
	Order::printIds(pq.getItemArray(), pq.getSize());

	pq.enqueue(order3, 22);
	Order::printIds(pq.getItemArray(), pq.getSize());

	pq.enqueue(order4, 33);
	Order::printIds(pq.getItemArray(), pq.getSize());

	std::cout << "Ay ha\n";

	Order* o;

	while (pq.dequeue(o))
	{
		Order::printIds(pq.getItemArray(), pq.getSize());
		std::cout << o->GetID() << std::endl;
	}

	pq.enqueue(order3, 22);
	Order::printIds(pq.getItemArray(), pq.getSize());

	pq.enqueue(order4, 33);
	Order::printIds(pq.getItemArray(), pq.getSize());

	pq.enqueue(order1, 11);
	Order::printIds(pq.getItemArray(), pq.getSize());

	while (pq.dequeue(o))
	{
		Order::printIds(pq.getItemArray(), pq.getSize());
		std::cout << o->GetID() << std::endl;
	}
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;

	pGUI->PrintMessage("Please Enter File Name : ");
	while (!loadFiles(pGUI->GetString())) {
		pGUI->PrintMessage("File Name Was Incorrect. Enter Again : ");
	}

	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		StepByStep();
		break;
	case MODE_SLNT:
		Silent();
		break;
		/*case MODE_DEMO:
			Just_A_Demo();*/

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
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current time
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
//void Restaurant::Just_A_Demo()
//{
//	
//	//
//	// THIS IS JUST A DEMO FUNCTION
//	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//	
//	int EventCnt;	
//	Order* pOrd;
//	Event* pEv;
//	srand(time(NULL)); 
//
//	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
//	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
//	
//	pGUI->UpdateInterface();
//
//	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
//		
//	int EvTime = 0;
//	
//	//Create Random events
//	//All generated event will be "ArrivalEvents" for the demo
//	for(int i=0; i<EventCnt; i++)
//	{
//		int O_id = i+1;
//		
//		//Rendomize order type
//		int OType;
//		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
//			OType = TYPE_VIP;
//		else if(i<EventCnt*0.5)	
//			OType = TYPE_FROZ;	//let next 30% be Frozen
//		else
//			OType = TYPE_NRM;	//let the rest be normal
//
//		
//		int reg = rand()% REG_CNT;	//randomize region
//
//
//		//Randomize event time
//		EvTime += rand()%4;
//		 
//		switch (reg)
//		{
//		case A_REG:
//			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionA, EventsQueue);
//			break;
//		case B_REG:
//			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionB, EventsQueue);
//			break;
//		case C_REG:
//			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionC, EventsQueue);
//			break;
//		case D_REG:
//			pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, regionD, EventsQueue);
//			break;
//		}
//		
//		AddEvent(pEv);
//
//	}	
//
//	int CurrentTimeStep = 1;
//	//as long as events queue is not empty yet
//	while(!EventsQueue.isEmpty())
//	{
//		//print current timestep
//		char timestep[10];
//		itoa(CurrentTimeStep,timestep,10);	
//		pGUI->PrintMessage(timestep);
//
//
//		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
//		//The above line may add new orders to the DEMO_Queue
//
//		//Let's draw all arrived orders by passing them to the GUI to draw
//
//		while(DEMO_Queue.dequeue(pOrd))
//		{
//			pGUI->AddOrderForDrawing(pOrd);
//			pGUI->UpdateInterface();
//		}
//		Sleep(1000);
//		CurrentTimeStep++;	//advance timestep
//	}
//
//
//	pGUI->PrintMessage("generation done, click to END program");
//	pGUI->waitForClick();
//
//	
//}
////////////////

//void Restaurant::AddtoDemoQueue(Order *pOrd)
//{
//	DEMO_Queue.enqueue(pOrd);
//}

//Order* Restaurant::getDemoOrder()
//{
//	Order* pOrd;
//	DEMO_Queue.dequeue(pOrd);
//	return pOrd;
//
//}


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

	simulation(MODE_INTR);
}

void Restaurant::StepByStep()
{
	simulation(MODE_STEP);
}

void Restaurant::Silent()
{
	simulation(MODE_SLNT);
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


void Restaurant::OutFile()
{
	//PrioritizedNode<Order*>* helper = NULL;
	ofstream out("Statistics.txt");

	/*int allDeliveredOrdersSize = regionA->GetDeliveredOrdersCount() +
									regionB->GetDeliveredOrdersCount() +
									regionC->GetDeliveredOrdersCount() +
									regionD->GetDeliveredOrdersCount();*/
	//Order ** allDeliveredOrders = new Order * [allDeliveredOrdersSize];
	PriorityQueue<Order *> allDeliveredOrders;

	out << "FT" << " | " << "ID" << " | " << "AT" << " | " << "WT" << " | " << "ST" << endl;

	for (int i = 0; i < REGCOUNT; i++) {

		Order ** deliveredOrders = regions[i]->GetDeliverdOrdersItemArray();
		double * deliveredOrdersWeights = regions[i]->GetDeliverdOrdersWeightArray();
		int sizeOfDeliveredOrders = regions[i]->GetDeliveredOrdersCount();

		for (int j = 0; j < sizeOfDeliveredOrders; j++) {
			allDeliveredOrders.enqueue(deliveredOrders[j], deliveredOrdersWeights[j]);
		}
	}

	Order * o;
	while (allDeliveredOrders.dequeue(o)) {
		out << o->GetFinishTime() << "   ";
		if (o->GetFinishTime() < 10) out << ' ';

		out << o->GetID() << "   ";
		if (o->GetID() < 10) out << ' ';

		out << o->GetArrTime() << "   ";
		if (o->GetArrTime() < 10) out << ' ';

		out << o->GetWaitTime() << "   ";
		if (o->GetWaitTime() < 10) out << ' ';

		out << o->GetServTime() << endl << endl;
	}


	out << "*___________________________*" << endl;


	int numberOfOrdersForEachRegion = 0;
	int numberOfVipForEachRegion = 0;
	int numberOfFrozenForEachRegion = 0;
	int numberOfNormalForEachRegion = 0;


	int numberOfOrdersForAllRegions = 0;
	int numberOfNormOrdersForAllRegions = 0;
	int numberOfFrozOrdersForAllRegions = 0;
	int numberOfVIPOrdersForAllRegions = 0;

	int numberOfMotorCForAllRegions = 0;

	int numberOfMotForEachRegion = 0;
	int numberOfNormMotorCForAllRegions = 0;
	int numberOfFrozMotorCForAllRegions = 0;
	int numberOfFastMotorCForAllRegions = 0;

	double totalAvgWait = 0;
	double totalAvgServ = 0;

	double AvgTotalWait = 0;
	double AvgTotalServ = 0;

	for (int i = 0; i < REGCOUNT; i++) {

		int sizeOfDeliveredOrders = regions[i]->GetDeliveredOrdersCount();
		Order ** deliveredOrders = regions[i]->GetDeliverdOrdersItemArray();

		numberOfOrdersForEachRegion = sizeOfDeliveredOrders;
		numberOfOrdersForAllRegions += numberOfOrdersForEachRegion;

		numberOfMotForEachRegion = regions[i]->getFastMotorcyclesCount()
			+ regions[i]->getFrozenMotorcyclesCount()
			+ regions[i]->getNormalMotorcyclesCount();
		numberOfMotorCForAllRegions += numberOfMotForEachRegion;


		numberOfVipForEachRegion = 0;
		numberOfNormalForEachRegion = 0;
		numberOfFrozenForEachRegion = 0;
		for (int j = 0; j < sizeOfDeliveredOrders; j++) {
			switch (deliveredOrders[j]->GetType()) {
			case TYPE_VIP:
				numberOfVipForEachRegion++;
				numberOfVIPOrdersForAllRegions++;
				break;
			case TYPE_NRM:
				numberOfNormalForEachRegion++;
				numberOfNormOrdersForAllRegions++;
				break;
			case TYPE_FROZ:
				numberOfFrozenForEachRegion++;
				numberOfFrozOrdersForAllRegions++;
				break;
			}
		}

		switch (i) {
		case 0:
			out << "Region A :" << endl;
			break;
		case 1:
			out << "Region B :" << endl;
			break;
		case 2:
			out << "Region C :" << endl;
			break;
		case 3:
			out << "Region D :" << endl;
			break;
		}

		out << "\t";

		out << "Orders:" << " " << numberOfOrdersForEachRegion;
		out << " " << "[" << "Norm:" << numberOfNormalForEachRegion;
		out << "," << "Froz" << numberOfFrozenForEachRegion;
		out << "," << "VIP:" << numberOfVipForEachRegion << "]" << "." << endl;

		out << "\t";

		out << "MotorC:" << " " << numberOfMotForEachRegion;
		out << " " << "[" << "Norm:" << regions[i]->getNormalMotorcyclesCount();
		out << "," << "Froz" << regions[i]->getFrozenMotorcyclesCount();
		out << "," << "VIP:" << regions[i]->getFastMotorcyclesCount() << "]" << "." << endl;

		out << "\t";

		out << "Avg Wait=" << " " << regions[i]->getAvgWait() << "," << " ";
		out << "Avg Serv=" << " " << regions[i]->getAvgService() << "." << endl;

		out << "*___________________________*";
		out << endl;
		
		
		totalAvgWait += regions[i]->getAvgWait();
		totalAvgServ += regions[i]->getAvgService();
	}

	AvgTotalWait = totalAvgWait / 4;
	AvgTotalServ = totalAvgServ / 4;

	out << "For All Regions:" << endl;
	out << "\t";

	out << "Orders:" << " " << numberOfOrdersForAllRegions;
	out << " " << "[" << "Norm:" << numberOfNormOrdersForAllRegions;
	out << "," << "Froz" << numberOfFrozOrdersForAllRegions;
	out << "," << "VIP:" << numberOfVIPOrdersForAllRegions << "]" << "." << endl;

	out << "\t";

	out << "MotorC:" << " " << numberOfMotorCForAllRegions;
	out << " " << "[" << "Norm:" << numberOfNormMotorCForAllRegions;
	out << "," << "Froz" << numberOfFrozMotorCForAllRegions;
	out << "," << "VIP:" << numberOfFastMotorCForAllRegions << "]" << "." << endl;

	out << "\t";

	out << "Avg Wait=" << " " << AvgTotalWait << "," << " ";
	out << "Avg Serv=" << " " << AvgTotalServ << "." << endl;

	out.close();
}


//void Restaurant::addToDelivered(Order * delivered)
//{
//	int FT = delivered->GetFinishTime();
//	deliveredOrders.enqueue(delivered,1/FT);
//}
