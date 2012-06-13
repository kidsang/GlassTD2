#include "Stage.h"

Stage::Stage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: mSceneManager(sceneManager), mStageManager(stageManager), mGui(gui)
{
	mCamera = mSceneManager->getCamera("PlayerCam");
}

Stage::~Stage(void)
{
}

Ogre::Camera* Stage::getCamera()
{
	return mCamera;
}

void Stage::jumpToNextStage(Stage* nextStage)
{
	mStageManager->setStage(nextStage);
	delete this;
}