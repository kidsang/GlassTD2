#include "Stage.h"
#include "Sound.h"

bool Stage::mSoundEnabled = true;
bool Stage::mMusicEnabled = true;

Stage::Stage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: mSceneManager(sceneManager), mStageManager(stageManager), mGui(gui)
{
	mCamera = mSceneManager->getCamera("PlayerCam");

	// ÖÕÖ¹ËùÓÐÉùÒô
	Stage::stopAllSounds();
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

void Stage::playSound(const char* fileName, bool loop)
{
	if (mSoundEnabled)
		Sound::getInstance()->play(fileName, loop);
}

void Stage::playMusic(const char* fileName, bool loop)
{
	if (mMusicEnabled)
		Sound::getInstance()->play(fileName, loop);
}

bool Stage::onKeyReleased(const OIS::KeyEvent &arg)
{
	return true;
}