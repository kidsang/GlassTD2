#include "LevelStage.h"

LevelStage::LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui), mCurrentStep(NULL)
{
}

LevelStage::~LevelStage()
{
	if (mCurrentStep != NULL)
	{
		delete mCurrentStep;
	}
}

void LevelStage::jumpToStep(Step* step)
{
	delete mCurrentStep;
	mCurrentStep = step;
	step->init();
}

bool LevelStage::run(float timeSinceLastFrame)
{
	return true;
}

bool LevelStage::onKeyPressed(const OIS::KeyEvent &arg)
{
	return mCurrentStep->onKeyPressed(arg);
}

bool LevelStage::onMouseMoved(const OIS::MouseEvent &arg)
{
	return mCurrentStep->onMouseMoved(arg);
}

bool LevelStage::onMousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return mCurrentStep->onMousePressed(arg, id);
}

bool LevelStage::onMouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return mCurrentStep->onMouseReleased(arg, id);
}