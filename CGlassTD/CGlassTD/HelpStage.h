#ifndef __HelpStage_h__
#define __HelpStage_h__

#include "stage.h"
#include "StartStage.h"

class HelpStage :
	public Stage
{
public:
	HelpStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~HelpStage(void);
	void notifyMouseMove(MyGUI::Widget* _sender, int _left, int _top);
	void notifyMouseButtonPress(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	void notifyMouseButtonRelease(MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id);
	/// 场景的运行逻辑
	/// @param timeSinceLastFrame 从上一帧到现在流逝的时间
	/// @note 这个函数每一帧调用，处理的是每一帧的逻辑
	/// @note 应该只由框架调用
	bool run(float timeSinceLastFrame);

	// 对事件的响应
	/// 按下键盘触发此函数
	/// @param arg 事件的信息
	/// @note 应该只由框架调用
	bool onKeyPressed(const OIS::KeyEvent &arg);

	/// 鼠标移动触发此函数
	/// @param arg 事件的信息
	/// @note 应该只由框架调用
	bool onMouseMoved(const OIS::MouseEvent &arg);

	/// 按下鼠标触发此函数
	/// @param arg 事件的信息
	/// @param id 哪个按键
	/// @note 应该只由框架调用
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	/// 释放鼠标触发此函数
	/// @param arg 事件的信息
	/// @param id 哪个按键
	/// @note 应该只由框架调用
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
private:
	MyGUI::VectorWidgetPtr mLayout;
	MyGUI::ImageBox* mBackBtn;
};

#endif
