#include "StartStage.h"
#include "StageSelect.h"


StartStage::StartStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("start.layout");
	juqingBtn = this->getGUI()->findWidget<MyGUI::Button>("juqingmode"); 
	lifeBtn = this->getGUI()->findWidget<MyGUI::Button>("lifeMode"); 
	settingBtn = this->getGUI()->findWidget<MyGUI::Button>("setting"); 
	quitBtn = this->getGUI()->findWidget<MyGUI::Button>("quit"); 
	juqingBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonClick);
	lifeBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonClick);
	settingBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonClick);
	quitBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonClick);
}


void StartStage::notifyMouseButtonClick(MyGUI::Widget* _sender)
{
	if(_sender == juqingBtn)
	{
		//juqingBtn->setEnabled(false);
		//juqingBtn->setVisible(false);
		//lifeBtn->setEnabled(false);
		//lifeBtn->setVisible(false);
		//settingBtn->setEnabled(false);
		//settingBtn->setVisible(false);
		//quitBtn->setEnabled(false);
		//quitBtn->setVisible(false);
		Stage* nextStage = new StageSelect(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == lifeBtn)
	{

	}
	else if(_sender == settingBtn)
	{

	}
	else if(_sender == quitBtn)
	{

	}
}
StartStage::~StartStage(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

bool StartStage::run(float timeSinceLastFrame)
{
	//MyGUI::LayoutManager::getInstance().loadLayout("start.layout");
	return true;
}

bool StartStage::onKeyPressed(const OIS::KeyEvent &arg)
{
	return true;
}

bool StartStage::onMouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool StartStage::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool StartStage::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}
