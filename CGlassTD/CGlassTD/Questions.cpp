#include "Questions.h"

Questions* Questions::instance = 0;

Questions::Questions(MyGUI::Gui* gui) : mGUI(gui)
{
}

void Questions::init(MyGUI::Gui* gui)
{
	if (instance != 0) delete instance;
	instance = new Questions(gui);
}

Questions* Questions::getInstance()
{
	return instance;
}

void Questions::destroyInstance()
{
	if (instance != 0) 
	{
		delete instance;
		instance = 0;
	}
}

void Questions::popUpQuestion()
{
	widgetVector = MyGUI::LayoutManager::getInstance().loadLayout("question.layout");
	//MyGUI::Button* button = mGUI->findWidget<MyGUI::Button>("
}

void Questions::handUpAnswer()
{
}

void Questions::giveUp()
{
	MyGUI::LayoutManager::getInstance().unloadLayout(widgetVector);
}