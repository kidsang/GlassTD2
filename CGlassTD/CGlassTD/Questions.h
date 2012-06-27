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

	/// 放弃答题
	void giveUp();
	
private:
	void onRadioClick(MyGUI::Widget* _sender);
	void onOkPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	void onNoPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	void onOkRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	void onNoRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	
	/// 提交答案
	void handUpAnswer();
	
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