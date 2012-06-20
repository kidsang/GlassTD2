#ifndef StagePass1_h__
#define StagePass1_h__

#include "LevelStage.h"

/// 第一关场景
class StagePass1 : public LevelStage
{
private:


public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	StagePass1(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass1(void);
};

#endif // StagePass1_h__

