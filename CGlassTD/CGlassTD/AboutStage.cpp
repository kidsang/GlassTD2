#include "AboutStage.h"
#include "Money.h"
#include "StartStage.h"

AboutStage::AboutStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
	Money::getInstance()->unDisplay();
	mLayout = MyGUI::LayoutManager::getInstance().loadLayout("about.layout");
	mBackBtn = this->getGUI()->findWidget<MyGUI::ImageBox>("back"); 
	mBackBtn->eventMouseMove += MyGUI::newDelegate(this, &AboutStage::notifyMouseMove);
	mBackBtn->eventMouseButtonPressed += MyGUI::newDelegate(this, &AboutStage::notifyMouseButtonPress);
	mBackBtn->eventMouseButtonReleased += MyGUI::newDelegate(this, &AboutStage::notifyMouseButtonRelease);
}

void AboutStage::notifyMouseMove( MyGUI::Widget* _sender, int _left, int _top )
{
	if(_sender == mBackBtn)
	{
		mBackBtn->setImageTexture("backMove.png");
	}
}
void AboutStage::notifyMouseButtonPress( MyGUI::Widget* _sender, int _left, int _top , MyGUI::MouseButton _id)
{
	if(_sender == mBackBtn)
	{
		mBackBtn->setImageTexture("backPress.png");
	}
}
void AboutStage::notifyMouseButtonRelease( MyGUI::Widget* _sender, int _left, int _top, MyGUI::MouseButton _id )
{
	if(_sender == mBackBtn)
	{
		mBackBtn->setImageTexture("back.png");
		Stage* nextStage = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
		this->jumpToNextStage(nextStage);
	}
}

AboutStage::~AboutStage(void)
{
	MyGUI::LayoutManager::getInstance().unloadLayout(mLayout);
}

bool AboutStage::run( float timeSinceLastFrame )
{
	return true;
}

bool AboutStage::onKeyPressed( const OIS::KeyEvent &arg )
{
	return true;
}

bool AboutStage::onMouseMoved( const OIS::MouseEvent &arg )
{
	return true;
}

bool AboutStage::onMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

bool AboutStage::onMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}
