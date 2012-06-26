#ifndef StageLoadingLevelStage_h__
#define StageLoadingLevelStage_h__

#include "Stage.h"
#include <MyGUI/MyGUI.h>

template <typename T>
class StageLoadingLevelStage : public Stage
{
	MyGUI::ImageBox* mImageBox;
	int mCount;

public:
	StageLoadingLevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
		: Stage(sceneManager, stageManager, gui),
		mCount(60)
	{
		mImageBox = mGui->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 1024, 768, MyGUI::Align::Center, "Main");
		mImageBox->setImageTexture("loading.gif");
	}
	~StageLoadingLevelStage(void)
	{
		mGui->destroyWidget(mImageBox);
	}

	virtual bool run( float timeSinceLastFrame )
	{
		if (--mCount > 0)
			return true;
		this->jumpToNextStage(new T(mSceneManager, mStageManager, mGui));
		return true;
	}

	virtual bool onKeyPressed( const OIS::KeyEvent &arg )
	{
		return true;
	}

	virtual bool onMouseMoved( const OIS::MouseEvent &arg )
	{
		return true;
	}

	virtual bool onMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		return true;
	}

	virtual bool onMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		return true;
	}

};

#endif // StageLoadingLevelStage_h__

