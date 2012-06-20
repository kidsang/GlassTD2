#include "StartStage.h"
#include "StageSelect.h"


StartStage::StartStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("start.layout");
	juqingBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("juqingMode"); 
	lifeBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("lifeMode"); 
	settingBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("setting"); 
	quitBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("quit"); 

	juqingBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	juqingBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);

	lifeBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	lifeBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);

	settingBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	settingBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);
	
	quitBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	quitBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);
}

void StartStage::notifyMouseButtonPress( MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	if(_sender == juqingBtn)
	{
		juqingBtn->setImageTexture("juqingPress.png");
	}
	else if(_sender == lifeBtn)
	{
		lifeBtn->setImageTexture("lifePress.png");
	}
	else if(_sender == settingBtn)
	{
		settingBtn->setImageTexture("settingPress.png");
	}
	else if(_sender == quitBtn)
	{
		quitBtn->setImageTexture("quitPress.png");
	}
}
void StartStage::notifyMouseButtonRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_sender == juqingBtn)
	{
		juqingBtn->setImageTexture("juqing.png");
		Stage* nextStage = new StageSelect(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
	else if(_sender == lifeBtn)
	{
		lifeBtn->setImageTexture("life.png");
	}
	else if(_sender == settingBtn)
	{
		settingBtn->setImageTexture("setting.png");
	}
	else if(_sender == quitBtn)
	{
		quitBtn->setImageTexture("quit.png");
	}
}

StartStage::~StartStage(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

bool StartStage::run(float timeSinceLastFrame)
{
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




