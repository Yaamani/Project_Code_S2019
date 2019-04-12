#include "Order.h"

int Order::autoPromotionLimit = 0;

Order::Order(int ID) : ID(ID)
{
	delivered = false;
}

Order::Order(int ID, ORD_TYPE r_Type, MyRegion * r_region, int ArrTime, int distance, int money)
{
	this->ID = (ID > 0 && ID < 1000) ? ID : 0;	//1<ID<999
	type = r_Type;
	Region = r_region;

	delivered = false;

	SetArrTime(ArrTime);
	SetDistance(distance);
	SetMoney(money);

	if (r_Type == TYPE_NRM)
		r_region->AddToNormal(this);
	else if (r_Type == TYPE_VIP) {
		double weight = calculateVipWeight();
		r_region->enqueueToFrozen_VIP(this, weight);
	}
	else {
		r_region->enqueueToFrozen_VIP(this, -DBL_MAX);
	}
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


int Order::GetType() const
{
	return type;
}

MyRegion* Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

bool Order::isDelivered()
{
	return delivered;
}

void Order::SetMoney(int m)
{
	totalMoney = m;
}

int Order::GetMoney() const
{
	return totalMoney;
}

void Order::SetArrTime(int a)
{
	ArrTime = a;
}

int Order::GetArrTime() const
{
	return ArrTime;
}

void Order::SetWaitTime(int w)
{
	WaitTime = w;
}

int Order::GetWaitTime() const
{
	return WaitTime;
}

void Order::SetServTime(int s)
{
	ServTime = s;
}

int Order::GetServTime() const
{
	return ServTime;
}

int Order::GetFinishTime() const
{
	return ArrTime + WaitTime + ServTime;
}



//bool Order::operator==(Order * o)
//{
//	return ID == o->GetID();
//}

double Order::promoteAndReturnWeight(int promotionMoney)
{
	if (type != TYPE_NRM) {
		std::cout << "You're promoting a non normal order\n";
		return 0;
	}
	totalMoney += promotionMoney;
	//Region->enqueueToFrozen_VIP(this, calculateVipWeight());
	type = TYPE_VIP;

	return calculateVipWeight();
}

void Order::setAutoPromotionLimit(int apl)
{
	Order::autoPromotionLimit = apl;
}

void Order::printIds(Node<Order*> * current)
{
	while (current)
	{
		std::cout << current->getItem()->GetID() << ", ";
		current = current->getNext();
	}

	std::cout << std::endl;
	//std::cout << "(size = " << size << ")" << std::endl;
}

double Order::calculateVipWeight()
{
	double disWeight = 1 - tanh(Distance / 33.5);
	double monWeight = tanh(totalMoney / 165);
	double arrTimeWeight = 1 - 0.01 * ArrTime;

	double weight = disWeight + monWeight + arrTimeWeight;
	return weight;
}
