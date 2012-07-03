#ifndef __LifeStage_h__
#define __LifeStage_h__

#include "LevelStage.h"

/// 生存模式场景
class LifeStage : public LevelStage
{
private:

public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	LifeStage(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~LifeStage(void);

	virtual void onEdReplayBtnClick( MyGUI::Widget* sender );

	virtual void onEdNextBtnClick( MyGUI::Widget* sender );

};

#endif // LifeStage_h__

