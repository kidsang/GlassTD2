#ifndef __cutScenes_h_
#define __cutScenes_h_


#include "Stage.h"
#include "UtilsOgreDshow.h"
#include "StartStage.h"
#include "StageLoadingLevelStage.h"
#include "StagePass1.h"
#include "StagePass4.h"

class cutScenes : public Stage
{
private:
	OgreUtils::DirectShowManager* mShowManager;
	//Ogre::String name, Ogre::String filename, int VWight, int VHeight
public :
	OgreUtils::DirectShowControl* mDirectshowControl;
	int state;
	cutScenes(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui, int s);
	~cutScenes();

	bool run(float timeSinceLastFrame);

	bool onKeyPressed(const OIS::KeyEvent &arg);

	bool onMouseMoved(const OIS::MouseEvent &arg);

	bool onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	bool onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	
	void gotoNext();
};

#endif