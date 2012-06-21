#include "StagePass2.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StagePass3.h"
#include "StageLoadingLevelStage.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass2::StagePass2(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui, 2)
{
	/// ��ʼ������
	initializeCannon("CannonDefine.xml", "BulletDefine.xml");
	/// ��ʼ���Թ�
	initializeMaze("MazeDefine2.xml", "CellDefine.xml");
	/// ��ʼ���ɴ�
	initializeUFO("UFODefine.xml");

	/// ����һ��monster������
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// ��ʼ��һ��һ������Ĳ���,ÿ��Ĳ�����һ��
	mMonsterManager->setMonsterWave("monsterWave.xml");
	mMonsterManager->setUFO(mUFO);

	// Ϊ��������˵����ӻص�
	//mGui->findWidget<MyGUI::Button>("ed_replay_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass2::onEdReplayBtnClick);
	//mGui->findWidget<MyGUI::Button>("ed_next_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass2::onEdNextBtnClick);

	/// ������պ�
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");
	
	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();
}


StagePass2::~StagePass2(void)
{
}

void StagePass2::onEdReplayBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass2>(mSceneManager, mStageManager, mGui));
}

void StagePass2::onEdNextBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass3>(mSceneManager, mStageManager, mGui));
}
