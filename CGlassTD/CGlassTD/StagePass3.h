#ifndef StagePass3_h__
#define StagePass3_h__

#include "LevelStage.h"

/// 第三关场景
class StagePass3 : public LevelStage
{
private:

public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	StagePass3(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass3(void);

	virtual void onEdReplayBtnClick( MyGUI::Widget* sender );

	virtual void onEdNextBtnClick( MyGUI::Widget* sender );

};

#endif // StagePass3_h__

