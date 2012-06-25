#include "Stage.h"
#include "UtilsOgreDshow.h"

class cutScenes : public Stage
{
	//Ogre::String name, Ogre::String filename, int VWight, int VHeight
public :
	OgreUtils::DirectShowControl* mDirectshowControl;

	cutScenes(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui): Stage(sceneManager, stageManager, gui)
	{
		Ogre::Root::getSingleton().addFrameListener(new OgreUtils::DirectShowManager(mCamera->getViewport()));
		mDirectshowControl = OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("test","E:\Logo_800.avi",800,340);
	};
	~cutScenes(){
		Ogre::OverlayManager::getSingleton().destroyAll();
	};

	bool run(float timeSinceLastFrame){ 
		if(!mDirectshowControl->mDirectshowTexture->isPlayingMovie())
		{
			Stage* next = new StartStage(this->mSceneManager, this->mStageManager, this->mGui);
			this->jumpToNextStage(next);
		}
		
		return true;
	};

	bool onKeyPressed(const OIS::KeyEvent &arg){return true;};

	bool onMouseMoved(const OIS::MouseEvent &arg){return true;};

	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return true;};

	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){return true;};
	
};