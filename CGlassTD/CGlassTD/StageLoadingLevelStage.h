#ifndef StageLoadingLevelStage_h__
#define StageLoadingLevelStage_h__

#include "Stage.h"
#include <MyGUI/MyGUI.h>

template <typename T>
class StageLoadingLevelStage : public Stage
{
	MyGUI::TextBox* mWarnText;
	int mCount;

public:
	StageLoadingLevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
		: Stage(sceneManager, stageManager, gui),
		mCount(60)
	{
		// test by kid
		mWarnText = mGui->createWidget<MyGUI::TextBox>("TextBox", 0, 0, 600, 300, MyGUI::Align::Center, "Main");
		mWarnText->setCaption("loading...");
		mWarnText->setAlign(MyGUI::Align::Center);
		mWarnText->setTextColour(MyGUI::Colour::White);
		mWarnText->setFontHeight(100);
	}
	~StageLoadingLevelStage(void)
	{
		mGui->destroyWidget(mWarnText);
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

