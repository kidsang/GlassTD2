#ifndef StageLoadingLevelStage_h__
#define StageLoadingLevelStage_h__

#include "Stage.h"

template <typename T>
class StageLoadingLevelStage : public Stage
{
public:
	StageLoadingLevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui)
		: Stage(sceneManager, stageManager, gui)
	{

	}
	~StageLoadingLevelStage(void)
	{

	}

	virtual bool run( float timeSinceLastFrame )
	{
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

