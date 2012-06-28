#include "Questions.h"
#include "Money.h"
#include <string>
#include "Sound.h"
#include "Stage.h"

Questions* Questions::instance = 0;

Questions::Questions(MyGUI::Gui* gui) :
	mGUI(gui), mAnswering(false)
{
	widgetVector = MyGUI::LayoutManager::getInstance().loadLayout("question.layout");
	
	mGUI->findWidget<MyGUI::ImageBox>("quest_bg")->setImageTexture("quest_bg.png");

	mFirstChoice = mGUI->findWidget<MyGUI::Button>("firstChoice");
	mFirstChoice->setStateSelected(true);
	mCurrentFlag = FIRST;
	mSecondChoice = mGUI->findWidget<MyGUI::Button>("secondChoice");
	mThirdChoice = mGUI->findWidget<MyGUI::Button>("thirdChoice");
	mFourthChoice = mGUI->findWidget<MyGUI::Button>("fourthChoice");
	mOkButton = mGUI->findWidget<MyGUI::ImageBox>("okButton");
	mOkButton->setImageTexture("quest_submit_up.png");
	mGiveUpButton = mGUI->findWidget<MyGUI::ImageBox>("giveUpButton");
	mGiveUpButton->setImageTexture("quest_giveup_up.png");
	
	mQuesText = mGUI->findWidget<MyGUI::TextBox>("questionText");
	mFirstText = mGUI->findWidget<MyGUI::TextBox>("firstChoiceText");
	mSecondText = mGUI->findWidget<MyGUI::TextBox>("secondChoiceText");
	mThirdText = mGUI->findWidget<MyGUI::TextBox>("thirdChoiceText");
	mFourthText = mGUI->findWidget<MyGUI::TextBox>("fourthChoiceText");
	
	mFirstChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	mSecondChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	mThirdChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	mFourthChoice->eventMouseButtonClick += MyGUI::newDelegate(this, &Questions::onRadioClick);
	
	mOkButton->eventMouseButtonPressed += MyGUI::newDelegate(this, &Questions::onOkPress);
	mOkButton->eventMouseButtonReleased += MyGUI::newDelegate(this, &Questions::onOkRelease);
	mGiveUpButton->eventMouseButtonPressed += MyGUI::newDelegate(this, &Questions::onNoPress);
	mGiveUpButton->eventMouseButtonReleased += MyGUI::newDelegate(this, &Questions::onNoRelease);
	
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

std::wstring s2ws(const std::string& s)
{
    setlocale(LC_ALL, "chs"); 
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}

void Questions::popUpQuestion()
{
	MyGUI::PointerManager::getInstance().setVisible(true);
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
	std::string caption = quest->getQuestion();
	/*
	// 每十个字插入一个回车
	std::vector<unsigned> allPos;
	//allPos.push_back(15);
	//allPos.push_back(47);
	allPos.push_back(63);
	//allPos.push_back(95);
	for (std::vector<unsigned>::iterator it = allPos.begin(); it != allPos.end(); ++it)
	{
		if (*it >= caption.size()) break;
		caption.insert(*it, "\n");
	}
	*/
	mQuesText->setCaption(s2ws(caption).c_str());
	Quest::Selections selection = quest->getSelections();
	mFirstText->setCaption(s2ws(selection["a"]).c_str());
	mSecondText->setCaption(s2ws(selection["b"]).c_str());
	mThirdText->setCaption(s2ws(selection["c"]).c_str());
	mFourthText->setCaption(s2ws(selection["d"]).c_str());
	mCorrectAnswer = quest->getAnswer();
}

bool Questions::isAnswering()
{
	return mAnswering;
}

void Questions::handUpAnswer()
{	
	Stage::playSound("../Media/Sound/click.wav", false);
	MyGUI::PointerManager::getInstance().setVisible(false);
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
	else
		answer = "d";
		
	if (answer.compare(mCorrectAnswer) == 0)
	{
		Money::getInstance()->correctAnswer();
		Stage::playSound("../Media/Sound/getMoney.wav", false);
	}
	else
	{
		Money::getInstance()->wrongAnswer();
		Stage::playSound("../Media/Sound/loseMoney.wav", false);
	}
}

void Questions::giveUp()
{
	Stage::playSound("../Media/Sound/click.wav", false);
	MyGUI::PointerManager::getInstance().setVisible(false);
	for (MyGUI::VectorWidgetPtr::iterator itr = widgetVector.begin(); itr != widgetVector.end(); ++itr)
	{
		(*itr)->setVisible(false);
	}

	mAnswering = false;
}

void Questions::onRadioClick(MyGUI::Widget* sender)
{
	Stage::playSound("../Media/Sound/switch.wav", false);
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

void Questions::onOkPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
{
	mOkButton->setImageTexture("quest_submit_down.png");
}

void Questions::onNoPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
{
	mGiveUpButton->setImageTexture("quest_giveup_down.png");
}

void Questions::onOkRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
{
	mOkButton->setImageTexture("quest_submit_up.png");
	this->handUpAnswer();
}

void Questions::onNoRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id)
{
	mGiveUpButton->setImageTexture("quest_giveup_up.png");
	this->giveUp();
}
