#include "StagePass5.h"
#include "StagePass6.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StageLoadingLevelStage.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass5::StagePass5(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui, 5)
{
	/// ��ʼ������
	initializeCannon("CannonDefine.xml", "BulletDefine.xml");
	/// ��ʼ���Թ�
	initializeMaze("M5.xml", "CellDefine.xml");
	/// ��ʼ���ɴ�
	initializeUFO("UFODefine5.xml");

	/// ����һ��monster������
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// ��ʼ��һ��һ������Ĳ���,ÿ��Ĳ�����һ��
	mMonsterManager->setMonsterWave("monsterWave5.xml");
	mMonsterManager->setUFO(mUFO);

	// Ϊ��������˵����ӻص�
	//mGui->findWidget<MyGUI::Button>("ed_replay_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass3::onEdReplayBtnClick);
	//mGui->findWidget<MyGUI::Button>("ed_next_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass3::onEdNextBtnClick);

	/// ������պ�
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");

	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();
}


StagePass5::~StagePass5(void)
{
}

void StagePass5::onEdReplayBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass5>(mSceneManager, mStageManager, mGui));
}

void StagePass5::onEdNextBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass6>(mSceneManager, mStageManager, mGui));
}
