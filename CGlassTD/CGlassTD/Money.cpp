#include "Money.h"


Money* Money::instance = 0;

Money::Money() : mAmount(20)
{
}

Money* Money::getInstance()
{
	if (instance == 0)
	{
		instance = new Money();
	}
	return instance;
}

void Money::destroyInstance()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

void Money::correctAnswer()
{
	mAmount += 10;
}

bool Money::placeTrap(Money::TrapType type)
{
	int cost = 0;
	switch (type)
	{
	case Money::TrapType::SPIKEWEED:
		cost = 10;
		break;
	case Money::TrapType::SWAMP:
		cost = 15;
		break;
	case Money::TrapType::TRAP:
		cost = 10;
		break;
	}

	if (mAmount - cost < 0)
	{
		return false;
	}
	else
	{
		mAmount -= cost;
		return true;
	}
}


int Money::getAmount() const
{
	return mAmount;
}