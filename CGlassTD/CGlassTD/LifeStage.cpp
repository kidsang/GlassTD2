#include "LifeStage.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StageLoadingLevelStage.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

LifeStage::LifeStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui, 2)
{
	/// 初始化大炮
	initializeCannon("CannonDefine.xml", "BulletDefine2.xml");
	/// 初始化迷宫
	initializeMaze("M2.xml", "CellDefine.xml");
	/// 初始化飞船
	initializeUFO("UFODefine2.xml");

	/// 新增一个monster管理器
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// 初始化一波一波怪物的参数,每层的波数不一样
	mMonsterManager->setMonsterWave("monsterWave2.xml");
	mMonsterManager->setUFO(mUFO);

	// 为结束画面菜单增加回调
	//mGui->findWidget<MyGUI::Button>("ed_replay_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass2::onEdReplayBtnClick);
	//mGui->findWidget<MyGUI::Button>("ed_next_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass2::onEdNextBtnClick);

	/// 设置天空盒
	mSceneManager->setSkyBox(true, "Glass/Skybox");

	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();
}


LifeStage::~LifeStage(void)
{
}

void LifeStage::onEdReplayBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<LifeStage>(mSceneManager, mStageManager, mGui));
}

void LifeStage::onEdNextBtnClick( MyGUI::Widget* sender )
{
}
