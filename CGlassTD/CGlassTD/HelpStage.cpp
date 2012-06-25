#include "HelpStage.h"
#include "Money.h"
#include "StartStage.h"

HelpStage::HelpStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	Money::getInstance()->unDisplay();
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("help.layout");
	mBackBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("back"); 
	mBackBtn->eventMouseMove += MyGUI::newDelegate(this, &HelpStage::notifyMouseMove);
	mBackBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &HelpStage::notifyMouseButtonPress);
	mBackBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &HelpStage::notifyMouseButtonRelease);
}

void HelpStage::notifyMouseMove( MyGUI::Widget* _sender, int _left, int _top )
{
	if(_sender == mBackBtn)
	{
		mBackBtn->setImageTexture("backMove.png");
	}
}
void HelpStage::notifyMouseButtonPress( MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	if(_sender == mBackBtn)
	{
		mBackBtn->setImageTexture("backPress.png");
	}
}
void HelpStage::notifyMouseButtonRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_sender == mBackBtn)
	{
		mBackBtn->setImageTexture("back.png");
		Stage* nextStage = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
}

HelpStage::~HelpStage(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

bool HelpStage::run( float timeSinceLastFrame )
{
	return true;
}

bool HelpStage::onKeyPressed( const OIS::KeyEvent &arg )
{
	return true;
}

bool HelpStage::onMouseMoved( const OIS::MouseEvent &arg )
{
	return true;
}

bool HelpStage::onMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

bool HelpStage::onMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}
