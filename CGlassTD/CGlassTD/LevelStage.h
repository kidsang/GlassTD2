#ifndef __LevelStage_h_
#define __LevelStage_h_

#include <vector>
using std::vector;
#include "Stage.h"
#include "Step.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"
#include "Animator.h"

class LevelStage : public Stage
{
public:
	/// 构造函数
	LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);

	/// 析构函数
	virtual ~LevelStage();

	/// 跳到第i个步骤
	void jumpToStep(Step* step);

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

	/// 添加一个摄像机动画
	void addCameraAnimator(Animator<Ogre::Camera>* ani)
	{
		mCameraAnimatorList.push_back(ani);
	}

	// Get/Set
public:
	Cannon* getCannon()
	{
		return mCannon;
	}

	Maze* getMaze()
	{
		return mMaze;
	}

	MonsterManager* getMonsterManager()
	{
		return mMonsterManager;
	}

	BulletManager& getBulletManager()
	{
		return mBulletManager;
	}

	const Vector3& getGravity()
	{
		return mGravity;
	}

	void setGravity(const Vector3& gravity)
	{
		mGravity = gravity;
	}

protected:
	/// 当前的分场景
	Step* mCurrentStep;
	/// 炮
	Cannon* mCannon;
	/// 迷宫
	Maze* mMaze;
	/// 怪物序列管理器
	MonsterManager* mMonsterManager;

	/// 炮弹管理类
	BulletManager mBulletManager;
	/// 摄像机动画列表
	std::deque<Animator<Ogre::Camera>*> mCameraAnimatorList;

	/// 环境重力
	Vector3 mGravity;


};


#endif