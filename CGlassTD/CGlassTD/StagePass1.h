#ifndef StagePass1_h__
#define StagePass1_h__

#include "LevelStage.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"
#include "Animator.h"

/// 第一关场景
class StagePass1 : public LevelStage
{
private:
	/// 炮
	Cannon* mCannon;
	/// 场景中存在的炮弹的列表
	//MyList<Bullet*> mBulletList;
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

public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass1(void);

	/// 场景的运行逻辑
	/// @param timeSinceLastFrame 从上一帧到现在流逝的时间
	/// @note 这个函数每一帧调用，处理的是每一帧的逻辑
	/// @note 应该只由框架调用
	bool run(float timeSinceLastFrame);

	/// 添加一个摄像机动画
	void addCameraAnimator(Animator<Ogre::Camera>* ani)
	{
		mCameraAnimatorList.push_back(ani);
	}

	Cannon* getCannon();
	Maze* getMaze();
	MonsterManager* getMonsterManager();
	BulletManager& getBulletManager();
	Vector3 getGravity();
};

#endif // StagePass1_h__

