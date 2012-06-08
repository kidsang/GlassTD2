#include "Stage.h"

Stage::Stage(Ogre::SceneManager* sceneManager, StageManager* stageManager)
	: mSceneManager(sceneManager), mStageManager(stageManager)
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