#include "StageSelect.h"
#include "StagePass1.h"
#include "StagePass2.h"
#include "StagePass3.h"
#include "StartStage.h"
#include "StageLoadingLevelStage.h"
#include "Sound.h"

StageSelect::StageSelect(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("SelectStage.layout");
	MyGUI::ImageBox* temp = this->getGUI()->findWidget<MyGUI::ImageBox>("stageBG");
	temp->setVisible(true);
	stage1Btn = this->getGUI()->findWidget<MyGUI::ImageBox>("stage1"); 
	stage2Btn = this->getGUI()->findWidget<MyGUI::ImageBox>("stage2"); 
	stage3Btn = this->getGUI()->findWidget<MyGUI::ImageBox>("stage3"); 
	backBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("back"); 
	
	stage1Btn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonPress);
	stage1Btn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonRelease);
	
	stage2Btn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonPress);
	stage2Btn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonRelease);
	
	stage3Btn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonPress);
	stage3Btn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonRelease);
	
	backBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonPress);
	backBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonRelease);
}

void StageSelect::notifyMouseButtonPress( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	Sound::getInstance()->play("../Media/Sound/click.wav", false);
	if(_sender == stage1Btn)
	{
		stage1Btn->setImageTexture("stage1Press.png");
	}
	else if(_sender == stage2Btn)
	{
		stage2Btn->setImageTexture("stage2Press.png");
	}
	else if(_sender == stage3Btn)
	{
		stage3Btn->setImageTexture("stage3Press.png");
	}
	else if(_sender == backBtn)
	{
		backBtn->setImageTexture("backPress.png");
	}
}

void StageSelect::notifyMouseButtonRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_sender == stage1Btn)
	{
		stage1Btn->setImageTexture("stage1.png");
		//Stage* nextStage = new StagePass1(this->mSceneManager, this->mStageManager, this->mGui);
		Stage* nextStage = new StageLoadingLevelStage<StagePass1>(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == stage2Btn)
	{
		stage2Btn->setImageTexture("stage2.png");
		//Stage* nextStage = new StagePass2(this->mSceneManager, this->mStageManager, this->mGui);
		Stage* nextStage = new StageLoadingLevelStage<StagePass2>(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == stage3Btn)
	{
		stage3Btn->setImageTexture("stage3.png");
		//Stage* nextStage = new StagePass3(this->mSceneManager, this->mStageManager, this->mGui);
		Stage* nextStage = new StageLoadingLevelStage<StagePass3>(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == backBtn)
	{
		backBtn->setImageTexture("back.png");
		Stage* nextStage = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
}



StageSelect::~StageSelect(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

bool StageSelect::run(float timeSinceLastFrame)
{
	//MyGUI::LayoutManager::getInstance().loadLayout("start.layout");
	return true;
}

bool StageSelect::onKeyPressed(const OIS::KeyEvent &arg)
{
	return true;
}

bool StageSelect::onMouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool StageSelect::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool StageSelect::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}



