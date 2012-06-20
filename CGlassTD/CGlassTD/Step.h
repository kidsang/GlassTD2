#ifndef __Step_h_
#define __Step_h_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

/// 关卡LevelStage中需要的步骤，同个关卡的所有步骤共享数据，但是行为不同
/// @author: LiaoNanhao
class Step
{
public:
	virtual ~Step()
	{

	}

	/// 初始化操作，如更改摄像头位置等
	virtual void init() = 0;

	/// 场景的运行逻辑
	/// @param timeSinceLastFrame 从上一帧到现在流逝的时间
	/// @note 这个函数每一帧调用，处理的是每一帧的逻辑
	virtual bool run(float timeSinceLastFrame) = 0;

	// 对事件的响应
	/// 按下键盘触发此函数
	/// @param arg 事件的信息
	virtual bool onKeyPressed(const OIS::KeyEvent &arg) = 0;

	/// 鼠标移动触发此函数
	/// @param arg 事件的信息
	virtual bool onMouseMoved(const OIS::MouseEvent &arg) = 0;

	/// 按下鼠标触发此函数
	/// @param arg 事件的信息
	/// @param id 哪个按键
	virtual bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	/// 释放鼠标触发此函数
	/// @param arg 事件的信息
	/// @param id 哪个按键
	virtual bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
};


#endif