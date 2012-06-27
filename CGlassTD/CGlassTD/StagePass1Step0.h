#ifndef __StagePass1Step0_h_
#define __StagePass1Step0_h_

#include "Step.h"
#include "LevelStage.h"
#include "Maze.h"

/// 第一关的布阵阶段
class StagePass1Step0 : public Step
{
public:

	enum State
	{
		NOTHING, WITH_SWAMP/*沼泽*/, WITH_SPIKEWEED/*地刺*/, WITH_TRAP/*捕兽夹*/, 
	};

	StagePass1Step0(LevelStage* stagePass1);
	~StagePass1Step0();

	// 实现父类的函数
	void init();
	bool run(float timeSinceLastFrame);
	bool onKeyPressed(const OIS::KeyEvent &arg);
	bool onMouseMoved(const OIS::MouseEvent &arg);
	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void setNotify();
	void guiNotifyMousePressSwamp(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMousePressSpikeweed(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMousePressTrap(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMouseReleaseSwamp(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMouseReleaseSpikeweed(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
	void guiNotifyMouseReleaseTrap(MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id);
private:
	/// 将鼠标在屏幕上的坐标转换成场景中的三维坐标
	/// @return 成功返回true，output中为三维坐标，失败返回false
	bool convert(const OIS::MouseEvent& arg, Ogre::Vector3& output);
	
private:
	LevelStage* mStagePass1;
	State mCurrentState;
	Cell* mCurrentCell;
	Ogre::Vector3 mLastPos;
	Ogre::RaySceneQuery* mRaySceneQuery;

	/// 画面卷动鼠标X方向标志位
	int mRollX;
	/// 画面卷动鼠标Y方向标志位
	int mRollY;
	// debug
	//MyGUI::StaticTextPtr debugText;
};


#endif