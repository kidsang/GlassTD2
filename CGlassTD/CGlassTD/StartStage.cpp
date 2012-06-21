#include "StartStage.h"
#include "StageSelect.h"
#include "Sound.h"

StartStage::StartStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	flag = 0;
	preFlag = -1;
	quitFlag = false;
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("start.layout");
	background = this->getGUI()->findWidget<MyGUI::ImageBox>("background"); 
	background->eventMouseMove += MyGUI::newDelegate(this, &StartStage::notifyMouseMove);
	juqingBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("juqingMode"); 
	lifeBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("lifeMode"); 
	settingBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("setting"); 
	quitBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("quit"); 
	juqingBtn->eventMouseMove += MyGUI::newDelegate(this, &StartStage::notifyMouseMove);
	juqingBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	juqingBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);
	lifeBtn->eventMouseMove += MyGUI::newDelegate(this, &StartStage::notifyMouseMove);
	lifeBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	lifeBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);
	settingBtn->eventMouseMove += MyGUI::newDelegate(this, &StartStage::notifyMouseMove);
	settingBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	settingBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);
	quitBtn->eventMouseMove += MyGUI::newDelegate(this, &StartStage::notifyMouseMove);
	quitBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonPress);
	quitBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &StartStage::notifyMouseButtonRelease);
}

void StartStage::notifyMouseMove( MyGUI::Widget* _sender, int _left, int _top )
{
	if(preFlag != flag)
	{
		if(preFlag == 1)
		{
			juqingBtn->setImageTexture("juqing.png");
		}
		else if(preFlag == 2)
		{
			lifeBtn->setImageTexture("life.png");
		}
		else if(preFlag == 3)
		{
			settingBtn->setImageTexture("setting.png");
		}
		else if(preFlag == 4)
		{
			quitBtn->setImageTexture("quit.png");
		}

	}
	if(_sender == juqingBtn)
	{
		juqingBtn->setImageTexture("juqingMove.png");
		preFlag = flag;
		flag = 1;
	}
	else if(_sender == lifeBtn)
	{
		lifeBtn->setImageTexture("lifeMove.png");
		preFlag = flag;
		flag = 2;
	}
	else if(_sender == settingBtn)
	{
		settingBtn->setImageTexture("settingMove.png");
		preFlag = flag;
		flag = 3;
	}
	else if(_sender == quitBtn)
	{
		quitBtn->setImageTexture("quitMove.png");
		preFlag = flag;
		flag = 4;
	}
	else 
	{
		preFlag = flag;
		flag = 0;
	}
}
void StartStage::notifyMouseButtonPress( MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	if(_id.toValue() !=  0)
		return ;
	Stage::playSound("../Media/Sound/click.wav", false);
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
	if(_id.toValue() !=  0)
		return ;
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
		quitFlag = true;
	}
}

StartStage::~StartStage(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

bool StartStage::run(float timeSinceLastFrame)
{
	return (!quitFlag);
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






