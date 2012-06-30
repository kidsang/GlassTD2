#include "StagePass1.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include "StagePass2.h"
#include "StageLoadingLevelStage.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass1::StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui, 1)
{
	/// ��ʼ������
	initializeCannon("CannonDefine.xml", "BulletDefine1.xml");
	/// ��ʼ���Թ�
	initializeMaze("M1.xml", "CellDefine.xml");
	/// ��ʼ���ɴ�
	initializeUFO("UFODefine1.xml");

	/// ����һ��monster������
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// ��ʼ��һ��һ������Ĳ���,ÿ��Ĳ�����һ��
	mMonsterManager->setMonsterWave("monsterWave1.xml");
	mMonsterManager->setUFO(mUFO);

	/// ������պ�
	mSceneManager->setSkyBox(true, "Glass/Skybox");
	
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
