
#include "StageSelect.h"
#include "StagePass1.h"
#include "StagePass2.h"
#include "StagePass3.h"
#include "StartStage.h"

StageSelect::StageSelect(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("stageSelect.layout");
	stage1Btn = this->getGUI()->findWidget<MyGUI::Button>("stage1"); 
	stage2Btn = this->getGUI()->findWidget<MyGUI::Button>("stage2"); 
	stage3Btn = this->getGUI()->findWidget<MyGUI::Button>("stage3"); 
	backBtn = this->getGUI()->findWidget<MyGUI::Button>("back"); 
	stage1Btn->eventMouseButtonClick += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonClick);
	stage2Btn->eventMouseButtonClick += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonClick);
	stage3Btn->eventMouseButtonClick += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonClick);
	backBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &StageSelect::notifyMouseButtonClick);
}


void StageSelect::notifyMouseButtonClick(MyGUI::Widget* _sender)
{
	if(_sender == stage1Btn)
	{
		Stage* nextStage = new StagePass1(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == stage2Btn)
	{

		Stage* nextStage = new StagePass2(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == stage3Btn)
	{
		Stage* nextStage = new StagePass3(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);

	}
	else if(_sender == backBtn)
	{
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

