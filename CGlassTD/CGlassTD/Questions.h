#ifndef __Questions_h__
#define __Questions_h__

#include <MyGUI/MyGUI.h>
#include <string>
#include "QuestBank.h"

/// 处理答题的逻辑，单例
class Questions
{
private:
	Questions(MyGUI::Gui* gui);
public:
	static void init(MyGUI::Gui* gui);
	static Questions* getInstance();
	static void destroyInstance();
private:
	static Questions* instance;
	
	
public:
	~Questions();

	/// 弹出问题的框框
	void popUpQuestion();

	/// 是否处在答题状态
	bool isAnswering();
	
private:
	void onRadioClick(MyGUI::Widget* sender);
	void onButtonClick(MyGUI::Widget* sender);
	
	/// 提交答案
	void handUpAnswer();
	
	/// 放弃答题
	void giveUp();
	
private:
	MyGUI::Gui* mGUI;
	MyGUI::VectorWidgetPtr widgetVector;
	MyGUI::Button* mFirstChoice;
	MyGUI::Button* mSecondChoice;
	MyGUI::Button* mThirdChoice;
	MyGUI::Button* mFourthChoice;
	MyGUI::ImageBox* mOkButton;
	MyGUI::ImageBox* mGiveUpButton;
	MyGUI::TextBox* mQuesText;
	MyGUI::TextBox* mFirstText;
	MyGUI::TextBox* mSecondText;
	MyGUI::TextBox* mThirdText;
	MyGUI::TextBox* mFourthText;

	bool mAnswering;
	
	enum CheckedFlag
	{
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
	};
	CheckedFlag mCurrentFlag;

	QuestBank* mQuestBank;
	std::string mCorrectAnswer;
};


#endif