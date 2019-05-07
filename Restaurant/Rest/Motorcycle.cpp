#pragma once
#include "Motorcycle.h"
#include "MyRegion.h"
#include "Order.h"

int Motorcycle::normalSpeed = 0;
int Motorcycle::frozenSpeed = 0;
int Motorcycle::vipSpeed = 0;

Motorcycle::Motorcycle(int ID, int speed, MyRegion* region, ORD_TYPE type) 
	: status(IDLE), ID(ID), region(region), type(type)
{
	if (type == TYPE_NRM)
		region->enqueueToNormalMotorcycles(this);
	else if (type == TYPE_FROZ) {
		//calculate weight
		region->enqueueToFrozenMotorcycles(this);
	}
	else {
		region->enqueueToFastMotorcycles(this);
	}

	currentInServiceOrder = NULL;
}

void Motorcycle::setNormalSpeed(int ns)
{
	Motorcycle::normalSpeed = ns;
}

void Motorcycle::setFrozenSpeed(int fs)
{
	Motorcycle::frozenSpeed = fs;
}

void Motorcycle::setVipSpeed(int vs)
{
	Motorcycle::vipSpeed = vs;
}

void Motorcycle::printIds(Node<Motorcycle*>* current, bool printType, bool printOrderInfo)
{
	while (current)
	{
		Motorcycle * m = current->getItem();
		if (printType) {
			std::cout << '\n' << m->GetID() << "-";
			switch (m->getMotorcycleType())
			{
			case TYPE_VIP:
				std::cout << "FAST";
				break;
			case TYPE_FROZ:
				std::cout << "FROZ";
				break;
			case TYPE_NRM:
				std::cout << "NORM";
				break;
			}
		} else std::cout << m->GetID();

		if (m->currentInServiceOrder && printOrderInfo) {
			Order * o = m->currentInServiceOrder;
			std::cout << " (oID = " << o->GetID()
				<< ", Dis = " << o->GetDistance()
				<< ", $ = " << o->GetMoney()
				<< ", AT = " << o->GetArrTime()
				<< ", WT = " << o->GetWaitTime()
				<< ", ST = " << o->GetServTime()
				<< ')';
			//std::cout << ", \n";
		}
		std::cout << ", ";
		current = current->getNext();
	}

	std::cout << std::endl;
}

void Motorcycle::assignOrder(Order * inServiceOrder, int assignmentTime, PriorityQueue<Motorcycle*> & InServiceMotorcycles)
{
	status = SERV;

	inServiceOrder->calculateStatistics(assignmentTime, this);
	currentInServiceOrder = inServiceOrder;

	int returnTime = assignmentTime + ceil(2 * inServiceOrder->GetServTime());
	setReturnTime(returnTime);
	InServiceMotorcycles.enqueue(this, 1 / returnTime);
}

void Motorcycle::unassignOrder()
{
	status = IDLE;
	currentInServiceOrder = NULL;
}

Order * Motorcycle::getOrder()
{
	return currentInServiceOrder;
}

ORD_TYPE Motorcycle::getMotorcycleType()
{
	return type;
}

void Motorcycle::setReturnTime(int time)
{
	returnTime = time;
}

int Motorcycle::getReturnTime()
{
	return returnTime;
}

int Motorcycle::GetID()
{
	return ID;
}

int Motorcycle::getSpeed()
{
	switch (type){
		case TYPE_NRM:
			return normalSpeed;
			break;
		case TYPE_FROZ:
			return frozenSpeed;
			break;
		case TYPE_VIP:
			return vipSpeed;
			break;
	}
}


Motorcycle::~Motorcycle()
{
}
