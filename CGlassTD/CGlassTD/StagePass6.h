#ifndef StagePass6_h__
#define StagePass6_h__

#include "LevelStage.h"

/// 第六关场景
class StagePass6 : public LevelStage
{
private:

public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	StagePass6(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass6(void);

	virtual void onEdReplayBtnClick( MyGUI::Widget* sender );

	virtual void onEdNextBtnClick( MyGUI::Widget* sender );

};

#endif // StagePass6_h__

