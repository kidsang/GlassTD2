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
	/// 初始化大炮
	initializeCannon("CannonDefine.xml", "BulletDefine.xml");
	/// 初始化迷宫
	initializeMaze("M1.xml", "CellDefine.xml");
	/// 初始化飞船
	initializeUFO("UFODefine1.xml");

	/// 新增一个monster管理器
	MonsterManager::initialize(mMaze, "MonsterDefine.xml");
	mMonsterManager = MonsterManager::getMonsterManager();
	/// 初始化一波一波怪物的参数,每层的波数不一样
	mMonsterManager->setMonsterWave("monsterWave.xml");
	mMonsterManager->setUFO(mUFO);

	// 为结束画面菜单增加回调
	//mGui->findWidget<MyGUI::Button>("ed_replay_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass1::onEdReplayBtnClick);
	//mGui->findWidget<MyGUI::Button>("ed_next_btn")->eventMouseButtonClick += MyGUI::newDelegate(this, &StagePass1::onEdNextBtnClick);


	/// 设置天空盒
	//mSceneManager->setSkyBox(true, "Examples/EveSpaceSkyBox");
	
	mCurrentStep = new StagePass1Step0(this);
	mCurrentStep->init();

	///GUI
	
	
	/*
	const int imageCount = 3; 
	const int imageSize = 40;
	MyGUI::ImageBox* bulletImage[imageCount];

	bulletImage[0] = this->getGUI()->findWidget<MyGUI::ImageBox>("bomb_red");
	bulletImage[1] = this->getGUI()->findWidget<MyGUI::ImageBox>("bomb_blue");
	bulletImage[2] = this->getGUI()->findWidget<MyGUI::ImageBox>("bomb_black");

	bulletImage[0]->setCoord((gui->getViewWidth()-4*imageSize),(gui->getViewHeight()-2*imageSize), imageSize*2, imageSize*2);
	bulletImage[1]->setCoord((gui->getViewWidth()-2*imageSize),(gui->getViewHeight()-1*imageSize), imageSize, imageSize);
	bulletImage[2]->setCoord((gui->getViewWidth()-1*imageSize),(gui->getViewHeight()-1*imageSize), imageSize, imageSize);

	MyGUI::TextBox* bulletCount[imageCount];
	bulletCount[0] = this->getGUI()->findWidget<MyGUI::TextBox>("b3");
	bulletCount[1] = this->getGUI()->findWidget<MyGUI::TextBox>("b2");
	bulletCount[2] = this->getGUI()->findWidget<MyGUI::TextBox>("b1");

	for(int i = 0; i < 3; i++)
	{

		std::ostringstream temp;
		temp << mCannon->getBulletFactories().at(i)->getAmmoCount();
		bulletCount[i]->setCaption(temp.str());
	}*/
	

	//MyGUI::ResourceManager::getInstance().load("Resources.xml");
	//MyGUI::ImageBox* image = MyGUI::Gui::getInstance().createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord(0, 0, 128, 128), MyGUI::Align::Default, "Main");
	//image->setItemResource("pic_Crystal_Clear_Butterfly");
	//image->setItemGroup("States");
	//image->setItemName("Normal");

	//image->setMaskPick("Crystal_Clear_Butterfly_Pick.png");
	/*image1->setItemResource("bomb_black.jpg");
	image2->setItemResource("bomb_blue.jpg");
	image3->setItemResource("bomb_red.jpg");

	image1->setMaskPick("bomb_pick.jpg");
	image2->setMaskPick("bomb_pick.jpg");
	image3->setMaskPick("bomb_pick.jpg");*/
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
