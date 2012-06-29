#include "cutScenes.h"

cutScenes::cutScenes(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui, int s): 
			Stage(sceneManager, stageManager, gui),
			mShowManager(0)
{
	state = s;
	if (!OgreUtils::DirectShowManager::getSingletonPtr())
		new OgreUtils::DirectShowManager(mCamera->getViewport());
	mShowManager = OgreUtils::DirectShowManager::getSingletonPtr();
	

	Ogre::Root::getSingleton().addFrameListener(mShowManager);
	
	switch(state){
	case 1 :
		mDirectshowControl = OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("fuck","../Media/1.avi",1024,768);
		break;
	case 2:
		mDirectshowControl = OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("fuck","../Media/2.avi",1024,768);
		break;
	case 3:
		mDirectshowControl = OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("fuck","../Media/3.avi",1024,768);
		break;
	case 4:
		mDirectshowControl = OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("fuck","../Media/4.avi",1024,768);
		break;
	}
};
cutScenes::~cutScenes(){
	if (mShowManager)
	{
		//mDirectshowControl->StopMovie();
		//Ogre::Root::getSingleton().removeFrameListener(mShowManager);
		mShowManager->DestroyAll();
		//delete mShowManager;
		//mShowManager = 0;
		//Ogre::OverlayManager::getSingleton().destroyAllOverlayElements();
		//Ogre::OverlayManager::getSingleton().destroyAll();
	}
	
	//delete mDirectshowControl;
	//Ogre::OverlayManager::getSingleton().destroyAll();
};
bool cutScenes::run(float timeSinceLastFrame){ 
	if(!mDirectshowControl->mDirectshowTexture->isPlayingMovie())
	{
		gotoNext();
	}

	return true;
};

bool cutScenes::onKeyPressed(const OIS::KeyEvent &arg)
{
	if(arg.key == OIS::KC_ESCAPE)
	{
		gotoNext();
	}
	return true;
};

bool cutScenes::onMouseMoved(const OIS::MouseEvent &arg){return true;};

bool cutScenes::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return true;};

bool cutScenes::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return true;};

void cutScenes::gotoNext()
{
	Stage* next;
	switch(state){
	case 1:
		next = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
		break;
	case 2:
		next = new StageLoadingLevelStage<StagePass1>(this->mSceneManager, this->mStageManager, this->mGui);
		break;
	case 3:
		next = new StageLoadingLevelStage<StagePass4>(this->mSceneManager, this->mStageManager, this->mGui);
		break;
	case 4:
		next = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
		break;

	}
	//mDirectshowControl->Destroy();
	this->jumpToNextStage(next);
	//Ogre::OverlayManager::getSingleton().destroyAll();

}