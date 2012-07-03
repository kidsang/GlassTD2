

#ifndef __StageSelect_h__
#define __StageSelect_h__

#include "Stage.h"

/// 游戏主菜单场景
class StageSelect: public Stage
{
public:
	StageSelect(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);

	~StageSelect();

	void notifyMouseButtonMove(MyGUI::Widget* _sender, int _left, int _top);

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
	MyGUI::ImageBox* stageBG;
	MyGUI::ImageBox* stage1Btn;
	MyGUI::ImageBox* stage2Btn;
	MyGUI::ImageBox* stage3Btn;
	MyGUI::ImageBox* stage4Btn;
	MyGUI::ImageBox* stage5Btn;
	MyGUI::ImageBox* stage6Btn;
	MyGUI::ImageBox* backBtn;
	MyGUI::VectorWidgetPtr mLayout;
	int preFlag;
	int flag;
};

#endif

