#include "StagePass1.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StagePass2.h"
#include "StageLoadingLevelStage.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass1::StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
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
	mMonsterManager->setUFO(mUFO);

	// 为结束画面菜单增加回调
	mGui->findWidget<MyGUI::Button>("ed_replay_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass1::onEdReplayBtnClick);
	mGui->findWidget<MyGUI::Button>("ed_next_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass1::onEdNextBtnClick);


	/// 设置天空盒
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");
	
	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();
}


StagePass1::~StagePass1(void)
{
}

void StagePass1::onEdReplayBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass1>(mSceneManager, mStageManager, mGui));
}

void StagePass1::onEdNextBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass2>(mSceneManager, mStageManager, mGui));
}
