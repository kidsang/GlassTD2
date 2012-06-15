#ifndef __Questions_h__
#define __Questions_h__

#include <MyGUI/MyGUI.h>

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
	/// 弹出问题的框框
	void popUpQuestion();
	
	/// 提交答案
	void handUpAnswer();
	
	/// 放弃答题
	void giveUp();
	
private:
	MyGUI::Gui* mGUI;
	MyGUI::VectorWidgetPtr widgetVector;
};


#endif