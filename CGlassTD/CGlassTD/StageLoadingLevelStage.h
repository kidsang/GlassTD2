#ifndef StageLoadingLevelStage_h__
#define StageLoadingLevelStage_h__

#include "Stage.h"

class StageLoadingLevelStage : public Stage
{
public:
	StageLoadingLevelStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StageLoadingLevelStage(void);

	virtual bool run( float timeSinceLastFrame );

	virtual bool onKeyPressed( const OIS::KeyEvent &arg );

	virtual bool onMouseMoved( const OIS::MouseEvent &arg );

	virtual bool onMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	virtual bool onMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

};

#endif // StageLoadingLevelStage_h__

