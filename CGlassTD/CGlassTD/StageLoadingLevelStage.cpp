#include "StageLoadingLevelStage.h"


StageLoadingLevelStage::StageLoadingLevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui)
{
}


StageLoadingLevelStage::~StageLoadingLevelStage(void)
{
}

bool StageLoadingLevelStage::run( float timeSinceLastFrame )
{
	return true;
}

bool StageLoadingLevelStage::onKeyPressed( const OIS::KeyEvent &arg )
{
	return true;
}

bool StageLoadingLevelStage::onMouseMoved( const OIS::MouseEvent &arg )
{
	return true;
}

bool StageLoadingLevelStage::onMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}

bool StageLoadingLevelStage::onMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return true;
}
