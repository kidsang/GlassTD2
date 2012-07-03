#ifndef StagePass4_h__
#define StagePass4_h__

#include "LevelStage.h"

/// 第四关场景
class StagePass4 : public LevelStage
{
private:

public:
	/// 构造函数
	/// @param pSceneManager 场景管理器的指针
	/// @param pStageManager 舞台管理器的指针
	StagePass4(Ogre::SceneManager* sceneManager, StageManager* stageManager, MyGUI::Gui* gui);
	~StagePass4(void);

	virtual void onEdReplayBtnClick( MyGUI::Widget* sender );

	virtual void onEdNextBtnClick( MyGUI::Widget* sender );

};

#endif // StagePass4_h__
