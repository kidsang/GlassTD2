#ifndef StagePass1_h__
#define StagePass1_h__

#include "LevelStage.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Maze.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "List.hpp"

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

	BulletManager mBulletManager;
	

	/// 环境重力
	Vector3 mGravity;

public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass1(void);

	Cannon* getCannon();
	Maze* getMaze();
	MonsterManager* getMonsterManager();
	BulletManager& getBulletManager();
	Vector3 getGravity();
};

#endif // StagePass1_h__

