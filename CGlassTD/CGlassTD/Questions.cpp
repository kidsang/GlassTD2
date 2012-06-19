#include "Questions.h"
#include "Money.h"
#include <string>

Questions* Questions::instance = 0;

Questions::Questions(MyGUI::Gui* gui) :
	mGUI(gui), mAnswering(false)
{
	widgetVector = MyGUI::LayoutManager::getInstance().loadLayout("question.layout");
	
	mFirstChoice = mGUI->findWidget<MyGUI::Button>("firstChoice");
	mFirstChoice->setStateSelected(true);
	mCurrentFlag = FIRST;
	mSecondChoice = mGUI->findWidget<MyGUI::Button>("secondChoice");
	mThirdChoice = mGUI->findWidget<MyGUI::Button>("thirdChoice");
	mFourthChoice = mGUI->findWidget<MyGUI::Button>("fourthChoice");
	mOkButton = mGUI->findWidget<MyGUI::Button>("okButton");
	mGiveUpButton = mGUI->findWidget<MyGUI::Button>("giveUpButton");
	
	mQuesText = mGUI->findWidget<MyGUI::TextBox>("questionText");
	mFirstText = mGUI->findWidget<MyGUI::TextBox>("firstChoiceText");
	mSecondText = mGUI->findWidget<MyGUI::TextBox>("secondChoiceText");
	mThirdText = mGUI->findWidget<MyGUI::TextBox>("thirdChoiceText");
	mFourthText = mGUI->findWidget<MyGUI::TextBox>("fourthChoiceText");
	
	mFirstChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	mSecondChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	mThirdChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	mFourthChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	
	mOkButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onButtonClick);
	mGiveUpButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onButtonClick);
	
	for (MyGUI::VectorWidgetPtr::iterator itr = widgetVector.begin(); itr != widgetVector.end(); ++itr)
	{
		(*itr)->setVisible(false);
	}

	mQuestBank = new QuestBank();
	mQuestBank->addQuests("QuestDefine.xml");
}

Questions::~Questions()
{
	MyGUI::LayoutManager::getInstance().unloadLayout(widgetVector);

	if (mQuestBank != 0) delete mQuestBank;
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
	for (MyGUI::VectorWidgetPtr::iterator itr = widgetVector.begin(); itr != widgetVector.end(); ++itr)
	{
		(*itr)->setVisible(true);
	}
	mAnswering = true;

	mFirstChoice->setStateSelected(true);
	mSecondChoice->setStateSelected(false);
	mThirdChoice->setStateSelected(false);
	mFourthChoice->setStateSelected(false);
	mCurrentFlag = FIRST;
	
	Quest* quest = mQuestBank->getQuest();
	mQuesText->setCaption(quest->getQuestion());
	QuestBank::Selection selection = quest->getSelections();
	mFirstText->setCaption(selection["a"]);
	mSecondText->setCaption(selection["b"]);
	mThirdText->setCaption(selection["c"]);
	mFourthText->setCaption(selection["d"]);
	mCorrectAnswer = quest->getAnswer();
}

bool Questions::isAnswering()
{
	return mAnswering;
}

void Questions::handUpAnswer()
{
	for (MyGUI::VectorWidgetPtr::iterator itr = widgetVector.begin(); itr != widgetVector.end(); ++itr)
	{
		(*itr)->setVisible(false);
	}
	mAnswering = false;
	
	std::string answer;
	if (mFirstChoice->getStateSelected())
		answer = "a";
	else if (mSecondChoice->getStateSelected())
		answer = "b";
	else if (mThirdChoice->getStateSelected())
		answer = "c";
	else (mFourthChoice->getStateSelected())
		answer = "d";
		
	if (answer.compare(mCorrectAnswer) == 0)
	{
		Money::getInstance()->correctAnswer();
	}
}

void Questions::giveUp()
{
	for (MyGUI::VectorWidgetPtr::iterator itr = widgetVector.begin(); itr != widgetVector.end(); ++itr)
	{
		(*itr)->setVisible(false);
	}

	mAnswering = false;
}

void Questions::onRadioClick(MyGUI::Widget* sender)
{
	MyGUI::Button* button = sender->castType<MyGUI::Button>();
	button->setStateSelected(true);
	
	if (button == mFirstChoice)
	{
		mCurrentFlag = FIRST;
		mSecondChoice->setStateSelected(false);
		mThirdChoice->setStateSelected(false);
		mFourthChoice->setStateSelected(false);
	}
	else if (button == mSecondChoice)
	{
		mCurrentFlag = SECOND;
		mFirstChoice->setStateSelected(false);
		mThirdChoice->setStateSelected(false);
		mFourthChoice->setStateSelected(false);
	}
	else if (button == mThirdChoice)
	{
		mCurrentFlag = THIRD;
		mFirstChoice->setStateSelected(false);
		mSecondChoice->setStateSelected(false);
		mFourthChoice->setStateSelected(false);
	}
	else if (button == mFourthChoice)
	{
		mCurrentFlag = FOURTH;
		mFirstChoice->setStateSelected(false);
		mSecondChoice->setStateSelected(false);
		mThirdChoice->setStateSelected(false);
	}
}

void Questions::onButtonClick(MyGUI::Widget* sender)
{
	MyGUI::Button* button = sender->castType<MyGUI::Button>();
	
	if (button == mOkButton)
	{
		this->handUpAnswer();
	}
	else
	{
		this->giveUp();
	}
}