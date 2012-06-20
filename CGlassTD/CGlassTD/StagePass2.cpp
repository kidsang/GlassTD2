#include "StagePass2.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"
#include <OgreLogManager.h>
#include "UFO.h"
#include "ParamParser.h"

StagePass2::StagePass2(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: LevelStage(sceneManager, stageManager, gui)
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
	throw std::exception("The method or operation is not implemented.");
}

void StagePass2::onEdNextBtnClick( MyGUI::Widget* sender )
{
	throw std::exception("The method or operation is not implemented.");
}
