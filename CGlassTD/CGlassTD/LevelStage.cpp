#include "LevelStage.h"
#include "StagePass1Step1.h"
#include "StagePass1Step0.h"

LevelStage::LevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
	: Stage(sceneManager, stageManager, gui),
	mCurrentStep(0), mCannon(0), mMaze(0), mMonsterManager(0),
	mGravity(Vector3(0, -200, 0))
{
}

LevelStage::~LevelStage()
{
	if (mCurrentStep)
		delete mCurrentStep;
	if (mCannon)
		delete mCannon;
	if (mMaze)
		delete mMaze;
	//TODO: monster manager�ǵ���,���ﲻdelete
	for (auto iter = mCameraAnimatorList.begin(); iter != mCameraAnimatorList.end(); ++iter)
		delete (*iter);
}

void LevelStage::jumpToStep(Step* step)
{
	delete mCurrentStep;
	mCurrentStep = step;
	step->init();
}

bool LevelStage::run(float timeSinceLastFrame)
{
	// �������������
	for (auto iter = mCameraAnimatorList.begin(); iter != mCameraAnimatorList.end(); ++iter)
	{
		if (!(*iter)->run(timeSinceLastFrame, mCamera))
		{
			// ��ª�Ĵ���by kid
			jumpToStep(new StagePass1Step1(this));
			delete (*iter);
			mCameraAnimatorList.erase(iter);
			break;
		}
	}

	return mCurrentStep->run(timeSinceLastFrame);
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