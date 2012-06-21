#include "Money.h"
#include <sstream>

Money* Money::instance = 0;

Money::Money(MyGUI::Gui* gui) : mAmount(20), mTextBox(0), mGui(gui)
{
}

Money* Money::getInstance()
{
	return instance;
}

void Money::init(MyGUI::Gui* gui)
{
	if (instance != 0) delete instance;
	
	instance = new Money(gui);
}

void Money::destroyInstance()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

Money::~Money()
{
	if (mTextBox != 0)
	{
		mGui->destroyWidget(mTextBox);
	}
}

void Money::display()
{
	if (mTextBox != 0) return;

	mTextBox = static_cast<MyGUI::TextBox*>( mGui->createWidgetT("TextBox", "TextBox", 30, 20, 180, 180, MyGUI::Align::Default, "Main") );
	mTextBox->setTextColour(MyGUI::Colour::White);
	mTextBox->setCaption(std::string("Money: ") + this->getAmountStr());
}

void Money::correctAnswer()
{
	mAmount += 10;
	mTextBox->setCaption(std::string("Money: ") + this->getAmountStr());
}

bool Money::enough(Money::TrapType type)
{
	int cost = 0;
	switch (type)
	{
	case Money::SPIKEWEED:
		cost = 10;
		break;
	case Money::SWAMP:
		cost = 15;
		break;
	case Money::TRAP:
		cost = 10;
		break;
	}

	if (mAmount - cost < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Money::placeTrap(Money::TrapType type)
{
	int cost = 0;
	switch (type)
	{
	case Money::SPIKEWEED:
		cost = 10;
		break;
	case Money::SWAMP:
		cost = 15;
		break;
	case Money::TRAP:
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
		mTextBox->setCaption(std::string("Money: ") + this->getAmountStr());
		return true;
	}
}


int Money::getAmount() const
{
	return mAmount;
}


std::string Money::getAmountStr() const
{
	std::ostringstream temp;
	temp << mAmount;
	return temp.str();
}