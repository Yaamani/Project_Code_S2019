#include "Motorcycle.h"

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

void Motorcycle::printIds(Node<Motorcycle*>* current)
{
	while (current)
	{
		std::cout << current->getItem()->GetID() << ", ";
		current = current->getNext();
	}

	std::cout << std::endl;
}

int Motorcycle::GetID()
{
	return ID;
}


Motorcycle::~Motorcycle()
{
}
