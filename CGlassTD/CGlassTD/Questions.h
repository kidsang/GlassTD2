#ifndef __Questions_h__
#define __Questions_h__

#include <MyGUI/MyGUI.h>

/// ���������߼�������
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
	/// ��������Ŀ��
	void popUpQuestion();
	
	/// �ύ��
	void handUpAnswer();
	
	/// ��������
	void giveUp();
	
private:
	MyGUI::Gui* mGUI;
	MyGUI::VectorWidgetPtr widgetVector;
};


#endif