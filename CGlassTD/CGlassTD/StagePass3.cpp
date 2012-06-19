#include "StagePass3.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass3::StagePass3(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui)
{
	/// 初始化大炮
	initializeCannon("CannonDefine.xml", "BulletDefine.xml");
	/// 初始化迷宫
	initializeMaze("MazeDefine.xml", "CellDefine.xml");
	/// 初始化飞船
	initializeUFO("UFODefine.xml");

	/// 新增一个monster管理器
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// 初始化一波一波怪物的参数,每层的波数不一样
	mMonsterManager->setMonsterWave("monsterWave.xml");

	/// 设置天空盒
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");
	
	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();
}


StagePass3::~StagePass3(void)
{
}
