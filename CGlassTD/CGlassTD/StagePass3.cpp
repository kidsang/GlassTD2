#include "StagePass3.h"
#include "StagePass4.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StageLoadingLevelStage.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass3::StagePass3(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui, 3)
{
	/// ��ʼ������
	initializeCannon("CannonDefine.xml", "BulletDefine.xml");
	/// ��ʼ���Թ�
	initializeMaze("MazeDefine3.xml", "CellDefine.xml");
	/// ��ʼ���ɴ�
	initializeUFO("UFODefine3.xml");

	/// ����һ��monster������
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// ��ʼ��һ��һ������Ĳ���,ÿ��Ĳ�����һ��
	mMonsterManager->setMonsterWave("monsterWave.xml");
	mMonsterManager->setUFO(mUFO);

	// Ϊ��������˵����ӻص�
	//mGui->findWidget<MyGUI::Button>("ed_replay_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass3::onEdReplayBtnClick);
	//mGui->findWidget<MyGUI::Button>("ed_next_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass3::onEdNextBtnClick);

	/// ������պ�
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");
	
	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();
}


StagePass3::~StagePass3(void)
{
}

void StagePass3::onEdReplayBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass3>(mSceneManager, mStageManager, mGui));
}

void StagePass3::onEdNextBtnClick( MyGUI::Widget* sender )
{
	this->jumpToNextStage(new StageLoadingLevelStage<StagePass4>(mSceneManager, mStageManager, mGui));
}
